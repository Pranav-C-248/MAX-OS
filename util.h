#pragma once



#ifndef NULL
#define NULL ((void*)0)
#endif

extern void print_int(int n);
extern int string_length(char* s);
extern void append(char c, char* s);
extern int compare_string(char s1[], char s2[]);
extern void srand(unsigned int seed);
extern int rand(void);
extern char* my_strchr(const char* s, int c);
char* itoa(int value);

