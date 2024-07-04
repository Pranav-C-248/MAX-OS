#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <stddef.h>

#define MAX_FILENAME_LENGTH 32
#define MAX_FILES 128
#define MAX_FILE_SIZE 1024

typedef struct {
    char name[MAX_FILENAME_LENGTH];
    char data[MAX_FILE_SIZE];
    size_t size;
} File;

typedef struct {
    char name[MAX_FILENAME_LENGTH];
    File files[MAX_FILES];
    size_t file_count;
} Directory;

extern Directory home;  // Declare home as an extern variable

void initialize_file_system();
int create_file(Directory *dir, const char *name, const char *data);
int read_file(Directory *dir, const char *name, char *buffer);
int write_file(Directory *dir, const char *name, const char *data);
int delete_file(Directory *dir, const char *name);

#endif
