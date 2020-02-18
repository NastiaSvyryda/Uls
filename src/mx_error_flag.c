#include "../inc/uls.h"

static void print_error_flag(int index, int index2, char **flags) {
    mx_print_error(MX_ERROR_FLAG);
    mx_printchar(flags[index][index2]);
    mx_printchar('\n');
    mx_print_error(MX_ERROR_USAGE);
    exit(1);
}

static void error_dir(char **flags, int index){
    mx_print_error(MX_ULS);
    mx_print_error(flags[index]);
    mx_print_error(MX_ERROR_DIR);
}

static void if_error_check_loop(int *f_s, char **flags, int i) {
    if (mx_strcmp("--",flags[i]) == 0)
        *f_s = 1;
}

static char **error_check(int argc, char **flags, int *f_s, int *count) {
    DIR *dp;
    char **err_flags = (char**) malloc(sizeof (char*));
    char *p = NULL;
    char b[1024];

    for (int i = 1; i < argc; i++) {
        p = mx_path(NULL, flags[i], 1);
        dp = opendir(flags[i]);
        if_error_check_loop(f_s, flags, i);
        if ((flags[i][0] != '-' || mx_strcmp(flags[i], "-") == 0 || *f_s == 1)
            && (dp == NULL || (mx_find_flag(argc, flags, 'l') == 1
            && readlink(p, b, 1024) != -1)) && mx_strcmp("--",flags[i]) != 0) {
            err_flags = mx_realloc(err_flags, sizeof (char*) * (*count + 1));
            err_flags[(*count)++] = mx_strdup(flags[i]);
        }
        if ((mx_flag_check(flags[i], *f_s)) >= 0)
            print_error_flag(i, (mx_flag_check(flags[i], *f_s)), flags);
        mx_close_dp(dp, flags[i], p, f_s);
    }
    return err_flags;
}

int mx_error_flag(int argc, char **flags) {
    int count = 0;
    int files = 0;
    int flag_stop = 0;
    char **error_flags = error_check(argc, flags, &flag_stop, &count);

    if (mx_find_flag(argc, flags, 'f') == 0) {
        mx_sort_ascii(count, error_flags);
        if ((mx_find_flag(argc, flags, 'r') == 1))
            mx_sort_reverse(count, error_flags);
    }
    for (int j = 0; j != count; j++) {
        if (mx_file_exist(error_flags[j]) == 0)
            error_dir(error_flags, j);
        else
            files++;
    }
    mx_free_void_arr((void**)error_flags, count);
    if (files == 0 && count != files && flag_stop == 0)
        exit(1);
    return (files > 0) ? 1 : 0;
}
