#include "shell.h"
#include "util.h"
#include "screen_driver.h"
#include "/Users/manaskumar/Desktop/MAX-OS-P1/main/tetris.c"
#include "keyboard.h"


#define MAX_BUFFER_SIZE 256

char *commands[MAX_COMMANDS] = {
    "CLS", "EXIT", "RANDOM", "ECHO"
}; 
void parse_command(char *command) {
    int i;

    char *space = my_strchr(command, ' ');
    if (space != NULL) {
        *space = '\0'; // Terminate the command keyword
    }

    for (i = 0; i < MAX_COMMANDS; i++) {
        if (compare_string(command, commands[i]) == 0) {
            if (space != NULL) {
                *space = ' '; // Restore the space character
            }
            cmd command_executor = commands_address[i]; // Gets the function that executes the command.
            command_executor(space != NULL ? space + 1 : NULL); // Pass the arguments to the command executor
            break;
        }
    }
    if (i == MAX_COMMANDS) {
        print_string("\nUndefined Command\n>");
    }
}

void set_command(int n, cmd function)
{
    commands_address[n] = function;
}

void cls()
{
    clrscr();
    print_string(">");
}
void exit()
{
    print_string("\nShutting down.Cya\n");
    asm volatile("hlt");
}

void random()
 {
    int x = rand();
    srand(x);
    print_string("\n>");
    print_int(x);


 }

 //void run_tetris()
/*{
    struct tetris game;
    tetris_init(&game, 20, 10);
    tetris_run(&game, 20, 10);
    print_string(">");
}*/
void initate_shell()
{
    set_command(0, cls);
    set_command(1, exit);
    set_command(2, random);
    set_command(3, echo);
}


void echo(char *args) {
    if (args != NULL) {
        print_string("\nEcho: ");
        print_string(args);
    } else {
        print_string("\nEcho: No arguments provided.");
    }
    print_string("\n>");
}


// void prove_dyna_memory(){
//     init_dynamic_memory();
//     int b=1;
//     int *a=mallok(20*sizeof(int));
//     for(int i=0;i<20;i++){
//         *(a+i)=b++;
//     }
//     for(int i=0;i<20;i++){
//         print_int(*(a+i));
//         print_string("\n");
//     }
// }