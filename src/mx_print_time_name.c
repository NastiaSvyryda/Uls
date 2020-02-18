#include "../inc/uls.h"

static char *first_flag(t_var *variable) {
    char *str = mx_strdup(variable->args[1]);

    for (int i = 2; i < variable->argc1; i++) {
        str = mx_realloc(str, sizeof (char) * (mx_strlen(str) + mx_strlen(variable->args[i]) + 1));
        str = mx_strcat(str, variable->args[i]);
    }
    return str;
}

static char *fill_timespec(t_array *dir, int i, t_var *var, struct timespec *a) {
    char *str = first_flag(var);

    if (var->flag_u && var->flag_c) {
        if (mx_strchr(str, 'u') > mx_strchr(str, 'c'))
            a->tv_sec = dir->st[i]->st_atimespec.tv_sec;
        else
            a->tv_sec = dir->st[i]->st_ctimespec.tv_sec;
    }
    else if (var->flag_u) {
        a->tv_sec = dir->st[i]->st_atimespec.tv_sec;
    }
    else if (var->flag_c) {
        a->tv_sec = dir->st[i]->st_ctimespec.tv_sec;
    }
    else
        a->tv_sec = dir->st[i]->st_mtimespec.tv_sec;
    mx_strdel(&str);
    return ctime(&a->tv_sec);
}

static void fill_time(char *time_out, char *temp, struct timespec *a) {
    time_t cur_time = 0;
    int y = 0;

    cur_time = time(NULL);
    if (cur_time - 15724800 <= a->tv_sec) {
        for (int i = 4; i < 16; i++, y++)
            time_out[y] = temp[i];
    }
    else {
        for (int i = 4; i < 10; i++, y++)
            time_out[y] = temp[i];
        y += 2;
        time_out[6] = ' ';
        time_out[7] = ' ';
        for (int k = 20; k < 24; k++, y++)
            time_out[y] = temp[k];
    }
    time_out[y] = '\0';
}
void mx_print_time_name(t_array *dir, int i, t_var *variable) {
    struct timespec *a = malloc(sizeof (struct timespec));
    char *time_out = malloc(sizeof (char) * 13);
    char *temp = NULL;

    variable->delim = 0;
    temp = fill_timespec(dir, i, variable, a);
    fill_time(time_out, temp, a);
    mx_printstr(time_out);
    mx_printstr(" ");
    free(a);
    a = NULL;
    mx_strdel(&time_out);
}

