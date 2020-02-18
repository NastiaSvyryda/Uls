#include "../inc/uls.h"

int mx_file_exist(char *file) {
    struct stat *st = (struct stat*) malloc(sizeof (struct stat));
    int flag = 0;
    char *path = mx_path(NULL, file, 1);

    if ((lstat(path, st) != -1))
        flag = 1;
    free(st);
    st = NULL;
    mx_strdel(&path);
    return flag;
}

