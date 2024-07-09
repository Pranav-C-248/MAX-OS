#include "screen_driver.h"
#include "port.h"


void set_cursor(int offset) {
    offset /= 2;
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);                  //select high byte
    port_byte_out(VGA_DATA_REGISTER, (unsigned char) (offset >> 8));
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);                   //select low byte
    port_byte_out(VGA_DATA_REGISTER, (unsigned char) (offset & 0xff));
}



int get_cursor(){
    //select high byte
    port_byte_out(VGA_CTRL_REGISTER,VGA_OFFSET_HIGH);
    int offset=port_byte_in(VGA_DATA_REGISTER)<<8;

    //select low byte
    port_byte_out(VGA_CTRL_REGISTER,VGA_OFFSET_LOW);
    offset+=port_byte_in(VGA_DATA_REGISTER);

    return offset*2; //reason for *2 is, this offset is used as video memory offset

}

void print_char(char character,int offset)
{
    unsigned char* vm= (unsigned char*) VIDEO_ADDRESS;
    vm[offset]=character;
    vm[offset+1]=WHITE_ON_BLACK;
}

int get_row_from_offset(int offset)
{
    return (offset/(2*MAX_COLS)); 
}

int get_offset(int row, int col) 
{
    return 2 * (row * MAX_COLS + col);
}

int move_cursor_to_new_line(int offset)
{
    return get_offset(get_row_from_offset(offset)+ 1,0);
}

void memory_copy(int nbytes, char* src, char* dest)
{
    for(int i=0;i<nbytes;i++)
    {
        *(dest+i)=*(src+i);
    }
}

int scroll(int offset)
{
    memory_copy(
        (MAX_COLS*MAX_ROWS*2),
        (char*)get_offset(1,0)+VIDEO_ADDRESS,
        (char*)get_offset(0,0)+VIDEO_ADDRESS);
        
    for(int col=0;col<MAX_COLS;col++)
    {
    print_char(' ',get_offset(MAX_ROWS-1,col));
    }

    return offset-2*MAX_COLS;
}

void print_string(char *s)
{
    int offset=get_cursor();
    int i =0;
    while(s[i]!='\0')
    {
        if (offset>=MAX_COLS*2*MAX_ROWS)
        {
            offset=scroll(offset);
        }
        
        if(s[i]=='\n')
        {
            offset=move_cursor_to_new_line(offset); //passing videoMemory offset
        }
        else
        {
            print_char(s[i],offset);
            offset+=2;
        }
        i++;
        set_cursor(offset);
    }
}


void clrscr() 
{
    for (int i = 0; i < MAX_COLS * MAX_ROWS; ++i) 
    {
    print_char('\0', i * 2);
    }
    set_cursor(get_offset(0, 0));
}


void set_char(char character,int offset)
{
    unsigned char* vm= (unsigned char*) VIDEO_ADDRESS;
    vm[offset]=character;
    vm[offset+1]=WHITE_ON_BLACK;
}