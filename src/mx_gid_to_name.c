#include "../inc/uls.h"

char *mx_gid_to_name(t_array *dir, int n) {
    struct group *pw_ptr;
    char *ptr = NULL;

    if ((pw_ptr = getgrgid(dir->st[n]->st_gid)) != NULL) {
        ptr = mx_strdup(pw_ptr->gr_name);
        return ptr;
    }
    ptr = mx_itoa(dir->st[n]->st_gid);
    return ptr;
}
