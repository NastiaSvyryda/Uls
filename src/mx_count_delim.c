#include "../inc/uls.h"

int mx_count_delim(t_array *dir, t_var *var, int num_of_files) {
    int delim = 8;

    for (int i = 0, y = 0; i < num_of_files; i++) {
        y = mx_strlen(dir->names[i]);
        if (var->flag_s == 1)
            y += mx_count_max_len(dir, 'b', num_of_files) + 1;
        if (var->flag_G == 1 && y >= delim
            && (isatty(1) != 0 || var->flag_c == 0)) {
            delim = y + 1;
        }
        else if(y >= delim)
            delim = (y / 8) * 8 + 8;
    }
    return delim;
}
