#pragma once

//define constants for accessing cursor, printing characters

#define VGA_CTRL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_OFFSET_LOW 0x0f  //15
#define VGA_OFFSET_HIGH 0x0e //14

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

//public functions
unsigned char port_byte_in(unsigned short port);
void port_byte_out(unsigned short port, unsigned char data);
extern void set_cursor(int offset);
extern int get_cursor();
extern int move_cursor_to_new_line(int  offset);
extern void print_char(char a, int offset);
extern void print_string(char *string);
extern void clrscr();
extern int get_row_from_offset(int offset);
int scroll(int offset);

// void print_int(int num);

