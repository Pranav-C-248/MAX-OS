#include "screen_driver.h"

void main(){
    clrscr();
    int a=65;
   
    
    for(int i=0;i<5;i++)
    {
        char c=(char)a;
        char sr[100]={c,'\n'};
        print_string(sr);
        a++;
    }
    
   
}