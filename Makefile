NAME = uls
SRC = src/main.c src/mx_error_flag.c src/mx_print_dir.c src/mx_sort_dir.c src/mx_output.c src/mx_find_flag.c src/mx_ls_dir.c src/mx_free_dir.c src/mx_output_loop.c src/mx_ls_flag_l.c src/mx_uid_to_name.c src/mx_count_delim.c src/mx_malloc_dir.c src/mx_fill_dir.c src/mx_color_print.c src/mx_print_mode.c src/mx_print_link_uid_gid_size.c src/mx_print_time_name.c src/mx_print_total.c src/mx_print_flag_F.c src/mx_gid_to_name.c src/mx_sort_reverse.c src/mx_flag_R.c src/mx_count_max_len.c src/mx_flag_check.c src/mx_path.c src/mx_input_files.c src/mx_file_exist.c src/mx_close_dp.c src/mx_flag_s.c
SRCOB = main.o mx_error_flag.o mx_print_dir.o mx_sort_dir.o mx_output.o mx_find_flag.o mx_ls_dir.o mx_free_dir.o mx_output_loop.o mx_ls_flag_l.o mx_uid_to_name.o mx_count_delim.o mx_malloc_dir.o mx_fill_dir.o mx_color_print.o mx_print_mode.o mx_print_link_uid_gid_size.o mx_print_time_name.o mx_print_total.o mx_print_flag_F.o mx_gid_to_name.o mx_sort_reverse.o mx_flag_R.o mx_count_max_len.o mx_flag_check.o mx_path.o mx_input_files.o mx_file_exist.o mx_close_dp.o mx_flag_s.o
INC = inc/uls.h
OBJ = obj/main.o obj/mx_error_flag.o obj/mx_print_dir.o obj/mx_sort_dir.o obj/mx_output.o obj/mx_find_flag.o mx_ls_dir.o obj/mx_free_dir.o obj/mx_output_loop.o obj/mx_ls_flag_l.o obj/mx_uid_to_name.o obj/mx_count_delim.o obj/mx_malloc_dir.o obj/mx_fill_dir.o obj/mx_color_print.o obj/mx_print_mode.o obj/mx_print_link_uid_gid_size.o obj/mx_print_time_name.o obj/mx_print_total.o obj/mx_print_flag_F.o obj/mx_gid_to_name.o obj/mx_sort_reverse.o obj/mx_flag_R.o obj/mx_count_max_len.o obj/mx_flag_check.o obj/mx_path.o obj/mx_input_files.o obj/mx_file_exist.o obj/mx_close_dp.o obj/mx_flag_s.o
DIR = obj/
LIBMX = libmx
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install

install:
	@make -C $(LIBMX)
	@mkdir -p obj
	@clang $(CFLAGS) -c $(SRC)
	@cp $(SRCOB) $(DIR)
	@clang $(CFLAGS) -o $(NAME) $(OBJ) -L./libmx -lmx
	@rm -rf $(SRCOB)

uninstall: clean
	@rm -rf $(NAME)
	@make uninstall -C $(LIBMX)

clean:
	@rm -rf $(SRCOB)
	@rm -rf $(DIR)
	@make clean -C $(LIBMX)

reinstall: uninstall install