#include "shell.h"
#include "util.h"
#include "screen_driver.h"


static char *commands[10];


void parse_command(char *command){
    int i;
    for (i = 0; i <MAX_COMMANDS ; i++)
    {
        if(compare_string(command,commands[i])==0){
            // command_executor=commands_address[i];
            //make a method to get arguments of command; gcc -o asb.o etc
            cmd command_executor=commands_address[i];
            command_executor();
            break;
        }
        
    }
    if(i==MAX_COMMANDS){
        print_string("\nUndefined Command\n>");
    }
}

void set_command(int n, cmd function){
    commands_address[n]=function;
}

void cls(){
    clrscr();
    print_string(">");
    
}
void exit(){
    print_string("\nShutting down.Cya\n");
    asm volatile("hlt");
}
void initate_shell(){
    set_command(0,cls);
    set_command(1,exit);
}