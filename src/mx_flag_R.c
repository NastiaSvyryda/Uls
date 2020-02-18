#include "../inc/uls.h"

static char **fill_dir_files(int *i, int num_of_files, t_array *dir) {
    char **dir_files = NULL;

    for (int j = 0; j < num_of_files; j++) {
        if ((dir->st[j]->st_mode & S_IFMT) == S_IFDIR
            && mx_strcmp(dir->names[j], ".")
                != 0 && mx_strcmp(dir->names[j], "..") != 0) {
            dir_files = mx_realloc(dir_files, sizeof (char*) * (*i + 1));
            dir_files[(*i)++] = mx_strdup(dir->names[j]);
        }
    }
    mx_free_dir(dir, num_of_files);
    return dir_files;
}

void mx_flag_R(int num_of_files, t_array *dir, t_var *variable, char *cur_p) {
    int i = 0;
    char **dir_files = fill_dir_files(&i, num_of_files, dir);
    char *pos = NULL;

    for (int k = 0, len = mx_strlen(cur_p); k < i; k++) {
        pos = mx_strdup(cur_p);
        mx_printstr("\n");
        pos = mx_realloc(pos, sizeof (char) * (len + 2));
        if (mx_strcmp(cur_p, "/") != 0)
            pos = mx_strcat(pos, "/");
        len = mx_strlen(pos) + mx_strlen(dir_files[k]) + 1;
        pos = mx_realloc(pos, sizeof (char) * (len));
        pos = mx_strcat(pos, dir_files[k]);
        mx_printstr(pos);
        mx_printstr(":\n");
        variable->flag_files = 0;
        mx_ls_dir(pos, dir, variable);
        mx_strdel(&pos);
    }
    mx_free_void_arr((void**) dir_files, i);
}

