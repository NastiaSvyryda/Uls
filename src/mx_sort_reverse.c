#include "../inc/uls.h"

void mx_sort_dir_reverse(int count, t_array *dir) {
    struct stat *temp = NULL;

    for (int i = 0, j = count - 1; i < count / 2; i++, j--) {
        mx_swaps_arr(dir->names, i, j);
        temp = dir->st[i];
        dir->st[i] = dir->st[j];
        dir->st[j] = temp;
        mx_swap_char((char*) &dir->type[i], (char*) &dir->type[j]);
    }
}

void mx_sort_reverse(int count, char **arr) {
    for (int i = 0, j = count - 1; i < count / 2; i++, j--) {
        mx_swaps_arr(arr, i, j);
    }
}
