#include "screen_driver.h"

void main(){
    clrscr();
    int a=65;

    
    for(int i=0;i<25;i++)
    {
        char c=(char)a;
        char sr[10]={c,'\n'};
        print_string(sr);
        a++;
    }

  

}