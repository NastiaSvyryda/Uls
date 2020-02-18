#include "../inc/uls.h"

static void print_del_size(t_array *dir, int num_of_files, t_var *variable, int i) {
    int delim = 0;
    char *size = NULL;

    for (int y = 0; y < num_of_files; y++) {
        size = mx_itoa(dir->st[y]->st_size);
        if (mx_strlen(size) > delim)
            delim = mx_strlen(size);
        mx_strdel(&size);
    }
    if (variable->flag_o == 1 && variable->flag_g == 1)
        delim += 2;
    size = mx_itoa(dir->st[i]->st_size);
    for (int y = 0; y < delim - mx_strlen(size); y++)
        mx_printstr(" ");
    mx_strdel(&size);
}

static void print_uid(t_array *dir, int i, t_var *variable) {
    char *name = mx_uid_to_name(dir, i);
    int len_name = mx_strlen(name);

    mx_printstr(name);
    write(1, "                            ", variable->uid_delim - len_name);
    mx_strdel(&name);
}

static void print_gid(t_array *dir, int i, t_var *variable) {
    char *name = mx_gid_to_name(dir, i);
    int len_name = mx_strlen(name);

    mx_printstr(name);
    write(1, "                            ", variable->gid_delim - len_name);
    mx_strdel(&name);
}

void mx_print_link_uid_gid_size(t_array *dir, int i, int num_of_files, t_var *variable) {
    mx_printint(dir->st[i]->st_nlink);
    mx_printstr(" ");
    if (variable->flag_g == 0)
        print_uid(dir, i, variable);
    if (variable->flag_o == 0)
        print_gid(dir, i, variable);
    print_del_size(dir, num_of_files, variable, i);
    if ((dir->st[i]->st_mode & S_IFMT) != S_IFCHR
        && (dir->st[i]->st_mode & S_IFMT) != S_IFBLK) {
        mx_printint(dir->st[i]->st_size);
    }
    else {
        mx_printstr("  ");
        mx_printint(MX_MAJOR(dir->st[i]->st_rdev));
        mx_printstr(",   ");
        mx_printint(MX_MINOR(dir->st[i]->st_rdev));
    }
    mx_printstr(" ");
}
