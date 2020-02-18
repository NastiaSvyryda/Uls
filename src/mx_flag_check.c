#include "../inc/uls.h"

int mx_flag_check(char *flag_, int flag_stop) {
    int flag = -2;
    char *us_f = "ACFGRSacfglorsu1";

    if (flag_[0] == '-' && flag_stop == 0) {
        for (int j = 1; flag_[j] != '\0'; j++) {
            flag = 0;
            for (int count = 0; us_f[count] != '\0'; count++) {
                if (us_f[count] == flag_[j]) {
                    flag = -1;
                    break;
                }
            }
            if (flag == 0) {
                flag = j;
                break;
            }
        }
    }
    return flag;
}
