#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

void print_char(char character,int offset){
    char* vm= (char*) VIDEO_ADDRESS;
    vm[offset]=character;
    vm[offset+1]=WHITE_ON_BLACK;
}

void print_string(char *string){
    int offset=get_offset();
}