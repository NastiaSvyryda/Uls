#include "../inc/uls.h"

static int count_el_in_line(int count, int e_line) {
    if (count > e_line) {
        while (count % e_line != 0 && count % e_line != e_line - 1) {
            if(count % e_line != 0 || count % e_line != e_line - 1) {
                break;
            }
            e_line--;
        }
    }
    return e_line;
}

static void loop(t_var *var, t_array *dir, int num,
                 void mx_print(int i, t_array *dir, t_var *var, int num)) {
    for (int y = 0; y < var->e_col; y++) {
        for (int k = var->e_line,i = y; k != 0; k--, i += var->e_col) {
            if (i + var->e_col >= num) {
                if (dir->names[i] != NULL) {
                    var->delim = -1;
                    mx_print(i, dir, var, num);
                    var->delim = mx_count_delim(dir, var, num);
                }
                break;
            }
            mx_print(i, dir, var, num);
        }
    }
}

void mx_output_loop(t_array *dir, t_var *var, int num,
                    void mx_print(int i, t_array *dir, t_var *var, int num)) {
    var->e_line = var->win_width / var->delim;
    if (var->flag_1 == 1 || var->e_line < 1)
        var->e_line = num;
    var->e_line = count_el_in_line(num, var->e_line);
    var->e_col = (num / var->e_line);
    if (num % var->e_line != 0)
        var->e_col += 1;
    loop(var, dir, num, mx_print);
}
