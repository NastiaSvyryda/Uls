#include "../inc/uls.h"

void mx_flag_s(int i, t_array *d, t_var *v, int n) {
    char *bl = mx_itoa(d->st[i]->st_blocks);

    if (v->flag_s == 1 && (v->flag_G == 0 || (isatty(1) == 0))){
        for (int j = mx_count_max_len(d, 'b', n) - mx_strlen(bl); j > 0; j--) {
            mx_printstr(" ");
        }
        mx_printint(d->st[i]->st_blocks);
        mx_printstr(" ");
    }
    mx_strdel(&bl);
}

