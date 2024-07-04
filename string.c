#include "string.h"

// Compute the length of a string
size_t strlen(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Copy a string
char *strcpy(char *dest, const char *src) {
    char *dest_ptr = dest;
    while ((*dest++ = *src++) != '\0');
    return dest_ptr;
}

// Copy a fixed number of characters from a string
char *strncpy(char *dest, const char *src, size_t n) {
    char *dest_ptr = dest;
    while (n-- && (*dest++ = *src++) != '\0');
    while (n-- > 0) {
        *dest++ = '\0';
    }
    return dest_ptr;
}

// Compare two strings
int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

// Set a block of memory
void *memset(void *s, int c, size_t n) {
    unsigned char *p = s;
    while (n--) {
        *p++ = (unsigned char)c;
    }
    return s;
}
