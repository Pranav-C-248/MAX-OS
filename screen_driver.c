#include "screen_driver.h"

unsigned char port_byte_in(unsigned short port) {
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out(unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

void set_cursor(int offset){
    offset=offset/2;
    port_byte_out(VGA_CTRL_REGISTER,VGA_OFFSET_LOW);//select the low byte of dataReg, by putting offset_low in ctrlReg
    port_byte_out(VGA_DATA_REGISTER,((unsigned char)(offset & 0xFF))); //storing the low byte 
    port_byte_out(VGA_CTRL_REGISTER,VGA_OFFSET_LOW);//select the hhigh byte of dataReg, by putting offset_high in ctrlReg
    port_byte_out(VGA_DATA_REGISTER,((unsigned char)((offset>>8) & 0xFF))); //storing the high byte 
}

int get_cursor(){
    //select high byte
    port_byte_out(VGA_CTRL_REGISTER,VGA_OFFSET_HIGH);
    int offset=port_byte_in(VGA_DATA_REGISTER);

    //select low byte
    port_byte_out(VGA_CTRL_REGISTER,VGA_OFFSET_LOW);
    offset+=port_byte_in(VGA_DATA_REGISTER);

    return offset*2; //reason for *2 is, this offset is used as video memory offset

}

void print_char(char character,int offset){
    char* vm= (char*) VIDEO_ADDRESS;
    vm[offset]=character;
    vm[offset+1]=WHITE_ON_BLACK;
}



int get_row_from_offset(int offset){
    return (offset/(2*MAX_COLS)); 
}

int get_offset(int col, int row) {
    return 2 * (row * MAX_COLS + col);
}

void clrscr() {
    for (int i = 0; i < MAX_COLS * MAX_ROWS; ++i) {
        print_char(' ', i * 2);
    }
    set_cursor(get_offset(0, 0));
}

int  move_cursor_to_new_line(int offset){
    int row=get_row_from_offset(offset);
    row=row+1;
    return 2*(row*MAX_COLS+1); //return offset wrt to VM.
}

void print_string(char *string){
    int offset=0;

    int i =0;
    if(string[i]=='\0'){
            print_char('h',98);
            print_char('e',100);
            print_char('r',102);
            print_char('e',104);
            print_char(string[3],106);
            
    }
    while(string[i]!='\0'){

        if(string[i]=='\n'){
            offset=move_cursor_to_new_line(offset); //passing videoMemory offset
        }
        else{
            print_char(string[i],offset);
            offset+=2;
        }
        i++;
    }
    set_cursor(offset); //offset of videoMemory
}

