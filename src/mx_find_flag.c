#include "../inc/uls.h"

void mx_find_all_flags(t_var *variables, int argc, char **argv) {
    variables->flag_1 = mx_find_flag(argc, argv, '1');
    variables->flag_a = mx_find_flag(argc, argv, 'a');
    variables->flag_A = mx_find_flag(argc, argv, 'A');
    variables->flag_C = mx_find_flag(argc, argv, 'C');
    variables->flag_c = mx_find_flag(argc, argv, 'c');
    variables->flag_g = mx_find_flag(argc, argv, 'g');
    variables->flag_G = mx_find_flag(argc, argv, 'G');
    variables->flag_f = mx_find_flag(argc, argv, 'f');
    variables->flag_F = mx_find_flag(argc, argv, 'F');
    variables->flag_o = mx_find_flag(argc, argv, 'o');
    variables->flag_u = mx_find_flag(argc, argv, 'u');
    variables->flag_s = mx_find_flag(argc, argv, 's');
    variables->flag_R = mx_find_flag(argc, argv, 'R');
    variables->flag_l = mx_find_flag(argc, argv, 'l');
    variables->flag_S = mx_find_flag(argc, argv, 'S');
    variables->flag_r = mx_find_flag(argc, argv, 'r');
}

int mx_find_flag(int argc, char **flags, char flag) {
  int flag_f = 0;

  for (int i = 1; i < argc; i++) {
    if(mx_flag_check(flags[i], 0) == -2 || mx_strcmp("--",flags[i]) == 0)
        break;
    if (flags[i][0] == '-') {
      for (int j = 1; flags[i][j] != '\0'; j++) {
        if (flag == flags[i][j]) {
          flag_f = 1;
          break;
        }
      }
    }
  }
  return flag_f;
}
