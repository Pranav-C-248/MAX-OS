#pragma once

#define MAX_SCANCODE   57 
#define BACKSPACE   0x0e
#define ENTER   0x1c


void init_keyboard();
char get_char();

static char key_buffer[256];
