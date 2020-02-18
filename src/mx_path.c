#include "../inc/uls.h"

char *mx_path(char *pathName, char *file, int flag) {
    char *p = NULL;

    if (flag == 1) {
        if (mx_strchr(file, '/') == NULL) {
            p = mx_strdup("./");
            p = mx_realloc(p, sizeof (char) * (mx_strlen(file) + 3));
            p = mx_strcat(p, file);
        }
        else
            p = mx_strdup(file);
    }
    else {
        p = mx_strdup(pathName);
        p = mx_realloc(p, sizeof (char) * (mx_strlen(p) + 2));
        if (mx_strcmp(pathName, "/") != 0)
            p = mx_strcat(p, "/");
        p = mx_realloc(p, sizeof (char) * (mx_strlen(p) + mx_strlen(file) + 1));
        p = mx_strcat(p, file);
    }
    return p;
}
