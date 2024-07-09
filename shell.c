#include "shell.h"
#include "util.h"
#include "screen_driver.h"
#include "/Users/manaskumar/Desktop/MAX-OS-P1/main/tetris.h"


char *commands[MAX_COMMANDS] = {
    "CLS", "EXIT", "RANDOM"
}; 
void parse_command(char *command)
{
    int i;

    for (i = 0; i < MAX_COMMANDS; i++)
    {
        if (compare_string(command, commands[i]) == 0)
        {
            cmd command_executor = commands_address[i]; // gets the function that executes the command.
            command_executor();
            break;
        }
    }
    if (i == MAX_COMMANDS){
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
     print_string(">");
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