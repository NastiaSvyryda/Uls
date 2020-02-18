#include "../inc/uls.h"

static char** copy_argv(char **argv, int argc) {
    char **arr = (char**) malloc(sizeof (char*) * argc);

    for (int i = 0; i < argc; i++)
        arr[i] = mx_strdup(argv[i]);
    return arr;
}

static char **loop_position(int ac, char **av, char **pos, int *count) {
    DIR *dp;
    char b[1024];
    char *p = NULL;
    for (int i = 1, flag_stop = 0; i < ac ; i++) {
        p = mx_path(NULL, av[i], 1);
        dp = opendir(av[i]);
        if (mx_strcmp("--", av[i]) == 0)
            flag_stop = 1;
        if ((dp != NULL && (av[i][0] != '-' || flag_stop == 1)) &&
            (mx_find_flag(ac, av, 'l') == 0 || readlink(p, b, 1024) == -1)) {
            pos = (char**) mx_realloc(pos, ((*count) + 1) * sizeof (char*));
            pos[(*count)++] = mx_strdup(av[i]);
            flag_stop = 1;
        }
        if (dp != NULL)
            closedir(dp);
        mx_strdel(&p);
    }
    return pos;
}

static char** if_count_flag_0(t_var *var, char **position) {
    if (var->count == 0 && var->flag_files == 0) {
        position[0] = mx_strdup(".");
        var->count = 1;
    }
    if (var->flag_f == 0) {
        mx_sort_ascii(var->count, position);
        if (var->flag_r == 1)
            mx_sort_reverse(var->count, position);
    }
    return position;
}

static void loop_dirs_if(char **position, t_var *var, t_array *dir) {
    for (int i = 0; i < var->count; i++) {
        if (mx_strcmp(position[i], ".") != 0 && var->count > 1) {
            mx_printstr(position[i]);
            mx_printstr(":\n");
        }
        mx_ls_dir(position[i], dir, var);
        var->flag_files = 0;
        if (var->count > 1 && i + 1 != var->count)
            mx_printstr("\n");
    }
    mx_free_void_arr((void **) var->args, var->argc1);
    mx_free_void_arr((void**) position, var->count);
    free(var);
    free(dir);
}

int main(int argc, char **argv) {
    t_array *dir = (t_array*) malloc(sizeof (t_array));
    t_var *var = (t_var*) malloc(sizeof (t_var));
    char **position = (char**) malloc(sizeof (char*));

    var->count = 0;
    var->flag_files = mx_error_flag(argc,argv);
    if (var->flag_files == 1) {
        position[var->count] = mx_strdup(".");
        var->count = 1;
    }
    position = loop_position(argc, argv, position, &var->count);
    mx_find_all_flags(var, argc, argv);
    position = if_count_flag_0(var, position);
    var->argc1 = argc;
    var->args = copy_argv(argv, argc);
    loop_dirs_if(position, var, dir);
    return 0;
}
