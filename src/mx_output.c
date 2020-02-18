#include "../inc/uls.h"

static int winsize(void) {
    struct winsize wins;
    int err = ioctl(0, TIOCGWINSZ, &wins);

    if (err == -1)
        return 0;
    return wins.ws_col;
}

void mx_output(t_array *dir, t_var *variable, int num_of_files) {
    variable->win_width = winsize();
    if (isatty(1) == 0 && variable->flag_C == 1)
        variable->win_width = 80;
    variable->delim = mx_count_delim(dir, variable, num_of_files);
    if (variable->flag_s == 1 && variable->flag_files == 0)
        mx_print_total(dir, num_of_files);
    if (variable->flag_1 == 1)
        variable->delim = -1;
    if (isatty(1) == 0 && variable->flag_C == 0) {
        variable->delim = -1;
        for (int i = 0; i < num_of_files; i++)
            mx_print_dir(i, dir, variable, num_of_files);
    }
    else if (variable->flag_G == 1 && isatty(1) == 1)
        mx_output_loop(dir, variable, num_of_files, mx_color_print);
    else
        mx_output_loop(dir, variable,  num_of_files, mx_print_dir);
}
