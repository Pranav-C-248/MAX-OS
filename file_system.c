#include "file_system.h"
#include "string.h"

Directory root;
Directory home;  // Define home here

void initialize_file_system() {
    // Initialize root directory
    strcpy(root.name, "C:\\");
    root.file_count = 0;

    // Initialize home directory
    strcpy(home.name, "C:\\home");
    home.file_count = 0;
}

int create_file(Directory *dir, const char *name, const char *data) {
    if (dir->file_count >= MAX_FILES) {
        return -1; // Directory full
    }

    File *file = &dir->files[dir->file_count++];
    strncpy(file->name, name, MAX_FILENAME_LENGTH);
    strncpy(file->data, data, MAX_FILE_SIZE);
    file->size = strlen(data);

    return 0; // Success
}

int read_file(Directory *dir, const char *name, char *buffer) {
    for (size_t i = 0; i < dir->file_count; ++i) {
        if (strcmp(dir->files[i].name, name) == 0) {
            strncpy(buffer, dir->files[i].data, dir->files[i].size);
            buffer[dir->files[i].size] = '\0'; // Null-terminate the buffer
            return 0; // Success
        }
    }
    return -1; // File not found
}

int write_file(Directory *dir, const char *name, const char *data) {
    for (size_t i = 0; i < dir->file_count; ++i) {
        if (strcmp(dir->files[i].name, name) == 0) {
            strncpy(dir->files[i].data, data, MAX_FILE_SIZE);
            dir->files[i].size = strlen(data);
            return 0; // Success
        }
    }
    return -1; // File not found
}

int delete_file(Directory *dir, const char *name) {
    for (size_t i = 0; i < dir->file_count; ++i) {
        if (strcmp(dir->files[i].name, name) == 0) {
            for (size_t j = i; j < dir->file_count - 1; ++j) {
                dir->files[j] = dir->files[j + 1];
            }
            --dir->file_count;
            return 0; // Success
        }
    }
    return -1; // File not found
}
