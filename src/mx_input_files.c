#include "../inc/uls.h"

char **mx_input_files(t_var *vr, int *num_files) {
    DIR *dp;
    char **files = (char**) malloc(sizeof (char*));
    char *p = NULL;
    char b[1024];

    for (int i = 1, stop = 0; i < vr->argc1; i++) {
        p = mx_path(NULL, vr->args[i], 1);
        dp = opendir(vr->args[i]);
        if (mx_strcmp("--", vr->args[i]) == 0)
            stop = 1;
        if (((vr->args[i][0] != '-' || mx_strcmp(vr->args[i], "-") == 0)
             || stop == 1) && (dp == NULL || (vr->flag_l == 1 &&
                                              readlink(p, b, 1024) != -1)) && mx_file_exist(vr->args[i]) == 1) {
            files = mx_realloc(files, sizeof(char*) * ((*num_files) + 1));
            files[(*num_files)++] = mx_strdup(vr->args[i]);
        }
        mx_close_dp(dp, vr->args[i], p, &stop);
    }
    return files;
}
