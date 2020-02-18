#include "../inc/uls.h"

int mx_count_max_len(t_array *dir, char link_or_size, int num_of_files) {
    int max = 0;
    int flag = 0;

    for (int i = 0, counter = 0, size = 0; i < num_of_files; i++) {
        counter = 0;
        if (link_or_size == 'l')
            size = dir->st[i]->st_nlink;
        else if (link_or_size == 'b')
            size = dir->st[i]->st_blocks;
        while (size > 0) {
            flag = 1;
            counter++;
            size /= 10;
        }
        if (counter > max)
            max = counter;
    }
    if (flag == 0)
        max = 1;
    return max;
}
