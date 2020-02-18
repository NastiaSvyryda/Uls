#include "../inc/uls.h"

void mx_malloc_dir(t_array *dir) {
    dir->st = (struct stat**) malloc(sizeof (struct stat*));
    dir->type = (unsigned char*) malloc(sizeof (unsigned char));
    dir->names = (char**) malloc(sizeof (char*) * CHAR_MAX/8);
}
