#include "../inc/uls.h"

int mx_print_flag_F(t_var *variable, t_array *d, int i) {
    if (variable->flag_F == 1) {
        if (isatty(1) == 1)
            mx_printstr(MX_FILE);
        if ((d->st[i]->st_mode & S_IFMT) == S_IFDIR)
            mx_printchar('/');
        else if (d->type[i] == 0 && (d->st[i]->st_mode & S_IFMT) != S_IFLNK)
            mx_printchar('*');
        else if ((d->st[i]->st_mode & S_IFMT) == S_IFLNK)
            mx_printchar('@');
        else if ((d->st[i]->st_mode & S_IFMT) == S_IFIFO)
            mx_printchar('|');
        else if ((d->st[i]->st_mode & S_IFMT) == S_IFSOCK)
            mx_printchar('=');
        else
            return -1;
        return 1;
    }
    return 0;
}


