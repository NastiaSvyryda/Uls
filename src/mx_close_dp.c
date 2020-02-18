#include "../inc/uls.h"

void mx_close_dp(DIR *dp, char *flag, char *p, int *flag_stop) {
    if (dp != NULL || mx_file_exist(flag) == 1) {
        if (flag[0] != '-' || mx_strcmp(flag, "-") == 0)
            *flag_stop = 1;
        if (dp != NULL)
            closedir(dp);
    }
    mx_strdel(&p);
}
