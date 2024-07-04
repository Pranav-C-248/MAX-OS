#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdint.h>

// Compute the length of a string
size_t strlen(const char *str);

// Copy a string
char *strcpy(char *dest, const char *src);

// Copy a fixed number of characters from a string
char *strncpy(char *dest, const char *src, size_t n);

// Compare two strings
int strcmp(const char *str1, const char *str2);

// Set a block of memory
void *memset(void *s, int c, size_t n);

#endif
