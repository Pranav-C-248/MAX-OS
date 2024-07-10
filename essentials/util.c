#include "util.h"
#include "screen_driver.h"
#include "keyboard.h"


static unsigned int current_seed = 1; // Default seed

// LCG constants from Numerical Recipes
#define LCG_A 1664525
#define LCG_C 1013904223
#define LCG_M 4294967296 



char* itoa(int value) {
    static char buffer[12];
    int i = 10;
    buffer[11] = '\0';
    do {
        buffer[i--] = (value % 10) + '0';
        value /= 10;
    } while (value > 0);
    return &buffer[i + 1];
}



int string_length(char *s) {
    int i = 0;
    while (s[i] != '\0') {
        ++i;
    }
    return i;
}

void append(char c, char* s) {
    int len = string_length(s);
    s[len] = c;
    s[len + 1] = '\0';
}

void print_int(int num){

    if(num==0){
        print_string("0");
        return;
    }
    char str[12];
    int i=0;
    int c=0;
    int a=num;
    while (num != 0) {
        str[i++] = (num % 10)+'0' ;
        num /= 10;
        c++;
    }
    str[c]='\0';
    for (int i = 0; i < c/2; i++)
    {
        char t=str[i];
        // print_string("%c\n",t);
        str[i]=str[c-i-1];
        str[c-1-i]=t;
    }
    str[c+1]='\0';
    print_string(str);  
}

int compare_string(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

char* my_strchr(const char* s, int c) {
    while (*s != '\0') {
        if (*s == c) {
            return (char *)s;
        }
        s++;
    }
    return NULL;
}

void srand(unsigned int seed) {
    current_seed = seed;
}

int rand() {
    
    current_seed = (LCG_A * current_seed + LCG_C) % LCG_M;
    return current_seed & 0x7FFFFFFF; // Return the positive range of int
}

