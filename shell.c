#include "shell.h"
#include "util.h"
#include "screen_driver.h"
#include "tetris.h"

 char *commands[10]={
    "CLS","EXIT","TETRIS"
}; //stores all the command keywords , to compare with input

void parse_command(char *command){
    int i;

    for (i = 0; i <MAX_COMMANDS ; i++)
    {

        if(compare_string(command,commands[i])==0){
            cmd command_executor=commands_address[i]; //gets the function that executes the command.
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
    // set_command(2,tetris_run);

}