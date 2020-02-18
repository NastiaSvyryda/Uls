#define ULS_H
#ifdef ULS_H

#define MX_ERROR_FLAG "uls: illegal option -- "
#define MX_ERROR_USAGE "usage: uls [-ACFGRSacfglorsu1] [file ...]\n"
#define MX_ERROR_DIR ": No such file or directory\n"
#define MX_ULS "uls: " 
#define MX_FILE "\033[0m"           //Regular file
#define MX_EXEC "\033[31m"           //Directory
#define MX_DIR "\033[34m"
#define MX_LINK "\033[35m"
#define MX_FIFO "\033[33m"
#define MX_SOCKET "\033[32m"
#define MX_STICKY "\033[42;30m"
#define MX_NO_STICKY "\033[43;30m"
#define MX_SET_UID "\033[41;30m"
#define MX_SET_GID "\033[46;30m"
#define MX_BLK "\033[46;34m"
#define MX_CHR "\033[43;34m"
#define MX_MAJOR(x)        ((int32_t)(((u_int32_t)(x) >> 24) & 0xff))
#define MX_MINOR(x)        ((int32_t)((x) & 0xffffff))

#include "../libmx/inc/libmx.h"
#include <sys/types.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <limits.h>
#include <pwd.h>
#include <grp.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <errno.h>

typedef struct s_array {
    char **names;
    unsigned char *type;
    struct stat **st;
} t_array;

typedef struct s_var {
    int delim;
    char **args;
    int argc1;
    int gid_delim;
    int uid_delim;
    int flag_A;
    int flag_C;
    int flag_F;
    int flag_G;
    int flag_R;
    int flag_a;
    int flag_f;
    int flag_g;
    int flag_l;
    int flag_o;
    int flag_s;
    int flag_1;
    int flag_u;
    int flag_c;
    int flag_S;
    int flag_r;
    int flag_files;
    int count;
    int win_width;
    int e_col;
    int e_line;
} t_var;

void mx_sort(t_array *dir, int num_of_files, t_var *variable);
void mx_find_all_flags(t_var *variables, int argc, char **argv);
void mx_sort_ascii(int count, char **arr);
int mx_print_flag_F(t_var *variable, t_array *d, int i);
void mx_print_total(t_array *dir, int num);
void mx_print_time_name(t_array *dir, int i, t_var *variable);
void mx_print_link_uid_gid_size(t_array *dir, int i, int num_of_files, t_var *variable);
void mx_print_mode(t_array *dir, int i, char *position, int num_of_files);
char *mx_uid_to_name(t_array *dir, int n);
void mx_ls_flag_l(t_array *dir, t_var *var, char *pos, int num);
void mx_output_loop(t_array *dir, t_var *var, int num,
                    void mx_print(int i, t_array *dir, t_var *var, int num));
void mx_free_dir(t_array *dir, int num_of_files);
void mx_ls_dir(char *cur_pos, t_array *dir, t_var *var);
int mx_find_flag(int argc, char **flags, char flag);
void mx_output(t_array *dir, t_var *variable, int num_of_files);
void mx_print_dir(int i, t_array *dir, t_var *var, int num);
int mx_error_flag(int argc, char **flags);
void mx_sort_dir(int count, t_array *dir);
int mx_count_delim(t_array *dir, t_var *var, int num_of_files);
void mx_malloc_dir(t_array *dir);
void mx_fill_dir(t_array *dir, struct dirent *ep, int count, char *pathName);
void mx_color_print(int i, t_array *dir, t_var *var, int num);
int mx_count_max_len(t_array *dir, char link_or_size, int num_of_files);
void mx_flag_R(int num_of_files, t_array *dir, t_var *variable, char *cur_p);
char **mx_input_files(t_var *vr, int *num_files);
char *mx_path(char *pathName, char *file, int flag);
void mx_fill_file_dir(char *file, t_array *dir, int count);
int mx_flag_check(char *flag_, int flag_stop);
char *mx_gid_to_name(t_array *dir, int n);
void mx_sort_reverse(int count, char **arr);
void mx_sort_dir_reverse(int count, t_array *dir);
int mx_file_exist(char *file);
void mx_close_dp(DIR *dp, char *flag, char *p, int *flag_stop);
void mx_flag_s(int i, t_array *d, t_var *v, int n);

#endif
