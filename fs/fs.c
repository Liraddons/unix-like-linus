#include "fs.h"

void create_file(const char *filename) {
    int fd = open(filename, O_CREAT | O_WRONLY, 0666);
    if (fd == -1) {
        perror("create_file");
    } else {
        close(fd);
    }
}

void delete_file(const char *filename) {
    if (remove(filename) != 0) {
        perror("delete_file");
    }
}

void list_files() {
    DIR *d;
    struct dirent *dir;

    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    } else {
        perror("list_files");
    }
}

void create_directory(const char *dirname) {
    if (mkdir(dirname, 0777) != 0) {
        perror("create_directory");
    }
}

void delete_directory(const char *dirname) {
    if (rmdir(dirname) != 0) {
        perror("delete_directory");
    }
}
