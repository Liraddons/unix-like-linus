#ifndef FS_H
#define FS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>

// Функции для работы с файловой системой
void create_file(const char *filename);
void delete_file(const char *filename);
void list_files();
void create_directory(const char *dirname);
void delete_directory(const char *dirname);

#endif // FS_H
