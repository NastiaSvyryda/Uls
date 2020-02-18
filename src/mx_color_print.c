#include "../inc/uls.h"

static void if_sock_blk_fifo(t_array *dir, int i, t_var *variable, int num) {
    if ((dir->st[i]->st_mode & S_IFMT) == S_IFSOCK) {
        mx_printstr(MX_SOCKET);
        mx_print_dir(i, dir, variable, num);
        mx_printstr(MX_FILE);
    }
    else if ((dir->st[i]->st_mode & S_IFMT) == S_IFBLK) {
        mx_printstr(MX_BLK);
        mx_print_dir(i, dir, variable, num);
        mx_printstr(MX_FILE);
    }
    else if ((dir->st[i]->st_mode & S_IFMT) == S_IFIFO) {
        mx_printstr(MX_FIFO);
        mx_print_dir(i, dir, variable, num);
        mx_printstr(MX_FILE);
    }
    else if ((dir->st[i]->st_mode & S_IFMT) == S_IFCHR) {
        mx_printstr(MX_CHR);
        mx_print_dir(i, dir, variable, num);
        mx_printstr(MX_FILE);
    }
}

static void if_dir(int i, t_array *dir, t_var *variable, int num) {
    if ((dir->st[i]->st_mode & S_IFMT) == S_IFDIR) {
        mx_printstr(MX_DIR);
        if ((dir->st[i]->st_mode & S_ISVTX)
            && (dir->st[i]->st_mode & S_IWOTH)) {
            mx_printstr(MX_STICKY);
        }
        else if (dir->st[i]->st_mode & S_IWOTH)
            mx_printstr(MX_NO_STICKY);
        mx_print_dir(i, dir, variable, num);
    }
    mx_printstr(MX_FILE);
}

static void if_exec(int i, t_array *dir, t_var *variable, int num) {
    if ((dir->st[i]->st_mode & S_IFMT) == S_IFREG) {
        mx_printstr(MX_FILE);
        if (dir->st[i]->st_mode & S_IXUSR) {
            mx_printstr(MX_EXEC);
            if (dir->st[i]->st_mode & S_ISUID)
                mx_printstr(MX_SET_UID);
            else if (dir->st[i]->st_mode & S_ISGID)
                mx_printstr(MX_SET_GID);
        }
        mx_print_dir(i, dir, variable, num);
    }
    mx_printstr(MX_FILE);
}

void mx_color_print(int i, t_array *dir, t_var *var, int num) {
    char *s_bl = mx_itoa(dir->st[i]->st_blocks);
    int len = mx_count_max_len(dir, 'b', num) - mx_strlen(s_bl);

    if (var->flag_s == 1) {
        for (int j = len; j > 0; j--) {
            mx_printstr(" ");
        }
        mx_printint(dir->st[i]->st_blocks);
        mx_printstr(" ");
    }
    if_dir(i, dir, var, num);
    if_exec(i, dir, var, num);
    if ((dir->st[i]->st_mode & S_IFMT) == S_IFLNK) {
        mx_printstr(MX_LINK);
        mx_print_dir(i, dir, var, num);
        mx_printstr(MX_FILE);
    }
    if_sock_blk_fifo(dir, i, var, num);
    mx_strdel(&s_bl);
}



