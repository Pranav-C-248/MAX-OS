#include "screen_driver.h"

void main(){
    clrscr();
    char a='1';

    
    for(int i=0;i<25;i++)
    {
        char sr[10]={a,'\n'};
        print_string(sr);
        a++;
    }

  

}