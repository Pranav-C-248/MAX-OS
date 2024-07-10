//we can declare the functions for each command here
// void cls() : clears screen

#pragma once

extern char *commands[10];
#define MAX_COMMANDS 10

typedef void(*cmd)();
static cmd commands_address[10];

extern void initate_shell();
extern void set_command(int n,cmd function);
extern void parse_command(char* command);
extern void cls();
extern void exit();
extern void random();
extern void echo(char *args);
extern void lay(char *args);
// extern void prove_dyna_memory();