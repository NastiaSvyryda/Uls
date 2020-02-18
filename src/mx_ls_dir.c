#include "../inc/uls.h"

static char *strrchrr(char *str, int ch) {//to lib
    char *temp = NULL;
    int i = 0;
    int  index = 0;

    while (str[i]) {
        if (str[i] == ch) {
            index = i;
        }
        i++;
    }
    temp = mx_strnew(mx_strlen(str) - index - 1);
    for (int j = index + 1, k = 0; str[j]; j++, k++)
        temp[k] = str[j];
    return temp;
}

static void dir_error(char *current_position) {
    char *temp_pos = strrchrr(current_position, (unsigned char) '/');
    char *errbuf = strerror(errno);

    mx_print_error("uls: ");
    mx_print_error(temp_pos);
    mx_print_error(": ");
    mx_print_error(errbuf);
    mx_print_error("\n");
    mx_strdel(&temp_pos);
}

static void if_fill_dir(t_array *dir, t_var *var, int *num, char *curr_pos) {
    struct dirent *ep = NULL;
    DIR *dp = opendir(curr_pos);

    while ((ep = readdir(dp)) != NULL) {
        if ((var->flag_a == 1 || var->flag_f == 1))
            mx_fill_dir(dir, ep, (*num)++, curr_pos);
        else if (var->flag_A == 1
                 && (mx_isalpha(ep->d_name[1])
                 || ep->d_name[0] != '.')) {
            mx_fill_dir(dir, ep, (*num)++, curr_pos);
        }
        else if (ep->d_name[0] != '.')
            mx_fill_dir(dir, ep, (*num)++, curr_pos);
    }
    if (dp != NULL)
        closedir(dp);
}

static void if_file_fill(t_array *dir, int *num_of_files, t_var *variable) {
    char **files = NULL;

    files = mx_input_files(variable, num_of_files);
    if (variable->flag_f == 0) {
        mx_sort_ascii(*num_of_files, files);
        if (variable->flag_r == 1)
            mx_sort_reverse(*num_of_files, files);
    }
    for (int i = 0; i < *num_of_files; i++) {
        mx_fill_file_dir(files[i], dir, i);
    }
    mx_free_void_arr((void **) files, *num_of_files);
}

static void main_step(t_array *dir, int *num_files, t_var *var, char *cur_pos) {
    DIR *dp = opendir(cur_pos);

    if (var->flag_files == 0 && dp != NULL)
        if_fill_dir(dir, var, num_files, cur_pos);
    else if (var->flag_files == 1)
        if_file_fill(dir, num_files, var);
    mx_sort(dir, *num_files, var);
    if (dp != NULL)
        closedir(dp);
    if ((var->flag_l == 1 || var->flag_o == 1
         || var->flag_g == 1) && (isatty(1) == 0 || isatty(1) == 1)) {
        mx_ls_flag_l(dir, var, cur_pos, *num_files);
    }
    else
        mx_output(dir, var, *num_files);
}

void mx_ls_dir(char *cur_pos, t_array *dir, t_var *var) {
    DIR *dp = opendir(cur_pos);
    int num_of_files = 0;

    mx_malloc_dir(dir);
    if (var->flag_files == 1 || dp != NULL)
        main_step(dir, &num_of_files, var, cur_pos);
    else
        dir_error(cur_pos);
    if (var->flag_R == 1 && dp != NULL)
        mx_flag_R(num_of_files, dir, var, cur_pos);
    else
        mx_free_dir(dir, num_of_files);
    if (dp != NULL)
        closedir(dp);
}





