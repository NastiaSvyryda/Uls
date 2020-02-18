#include "../inc/uls.h"

void mx_free_dir(t_array *dir, int num_of_files) {//ls
    mx_free_void_arr((void**) dir->st, num_of_files);
    mx_free_void_arr((void**) dir->names, num_of_files);
    free(dir->type);
}
