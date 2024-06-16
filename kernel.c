void main(){
    char *video_memory=(char*) 0xb8000;
    video_memory[0]= '\0';
    int i=0;
    for (i = 0; i < 1000; i+=2)
    {
        video_memory[i]= '\0';
    }

        video_memory[i+1000]= 'x';

    
}