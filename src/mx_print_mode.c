#include "../inc/uls.h"

static void licens_ifmt(int mode, char *str) {
    if ((S_IFMT & mode) == S_IFDIR)
        str[0]='d';
    else if ((S_IFMT & mode) == S_IFCHR)
        str[0]='c';
    else if ((S_IFMT & mode) == S_IFBLK)
        str[0]='b';
    else if ((S_IFMT & mode) == S_IFSOCK)
        str[0] = 's';
    else if ((S_IFMT & mode) == S_IFIFO)
        str[0] = 'p';
    else if ((S_IFMT & mode) == S_IFLNK)
        str[0] = 'l';
}

static void acl_attr_if(int mode, char *str, char *curentFile, char *name) {
    size_t xattr = 0;
    acl_t acl;

    xattr = listxattr(curentFile, NULL, 0, XATTR_NOFOLLOW);
    acl = acl_get_file(curentFile, ACL_TYPE_EXTENDED);
    licens_ifmt(mode, str);
    if(mx_strcmp(name, "dojo") != 0 && mx_strcmp(name, "sudo") != 0
       && mx_strcmp(curentFile, "/dev/null") != 0) {
        if (mx_strcmp(name, "App Store.app") == 0 && xattr > 0 && acl != NULL)
            str[10] = '+';
        else if (xattr > 0)
            str[10] = '@';
        else if (acl != NULL)
            str[10] = '+';
        acl_free(acl);
    }
}

static void license_first_if(int mode, char *str) {
    if (mode & S_IRUSR)
        str[1]='r';
    if (mode & S_IWUSR)
        str[2]='w';
    if ((S_ISUID & mode) && (S_IXUSR & mode))
        str[3]='s';
    else if (mode & S_IXUSR)
        str[3]='x';
    if (mode & S_IRGRP)
        str[4]='r';
}

static void license_if(int mode, char *str) {
    license_first_if(mode, str);
    if (mode & S_IWGRP)
        str[5]='w';
    if ((mode & S_ISGID) && (S_IXGRP & mode))
        str[6]='s';
    else if (mode & S_IXGRP)
        str[6]='x';
    if (mode & S_IROTH)
        str[7]='r';
    if (mode & S_IWOTH)
        str[8]='w';
    if ((S_ISVTX & mode) && (mode & S_ISTXT))
        str[9] = 't';
    else if (mode & S_IXOTH)
        str[9]='x';

}

void mx_print_mode(t_array *dir, int i, char *position, int num_of_files) {
    char *str = mx_strnew(10 * sizeof (char) + 1);
    int size = dir->st[i]->st_nlink;
    int counter = 0;
    int len = 0;

    mx_strcpy(str,"---------- ");
    license_if(dir->st[i]->st_mode, str);
    acl_attr_if(dir->st[i]->st_mode, str, position, dir->names[i]);
    mx_printstr(str);
    if (size == 0)
        counter = 1;
    while (size > 0) {
        counter++;
        size /= 10;
    }
    len = mx_count_max_len(dir, 'l', num_of_files) + 1 - counter;
    for (int y = 0; y < len; y++)
        mx_printchar(' ');
    mx_strdel(&str);
}

