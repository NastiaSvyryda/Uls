#include "../inc/uls.h"

char *mx_uid_to_name(t_array *dir, int n) {
    struct passwd *pw_ptr;
    char *ptr = NULL;

    if ((pw_ptr = getpwuid(dir->st[n]->st_uid)) != NULL) {
        ptr = mx_strdup(pw_ptr->pw_name);
        return ptr;
    }
    return NULL;
}
