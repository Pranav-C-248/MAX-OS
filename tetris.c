// // #include <stdio.h>
// // #include <stdlib.h>
// #include "tetris.h"
// // #include <termios.h>
// // #include <signal.h>
// #include <time.h>
// // #include <fcntl.h>
// #include "screen_driver.h"


// struct tetris_level {
//     int score;
//     int nsec;
// };

// struct tetris {
//     char **game;
//     int w;
//     int h;
//     int level;
//     int gameover;
//     int score;
//     struct tetris_block {
//         char data[5][5];
//         int w;
//         int h;
//     } current;
//     int x;
//     int y;
// };

// struct tetris_block blocks[] =
// {
//     {{"##", 
//          "##"},
//     2, 2
//     },
//     {{" X ",
//          "XXX"},
//     3, 2
//     },
//     {{"@@@@"},
//         4, 1},
//     {{"OO",
//          "O ",
//          "O "},
//     2, 3},
//     {{"&&",
//          " &",
//          " &"},
//     2, 3},
//     {{"ZZ ",
//          " ZZ"},
//     3, 2}
// };

// struct tetris_level levels[]=
// {
//     {0,
//         1200000},
//     {1500,
//         900000},
//     {8000,
//         700000},
//     {20000,
//         500000},
//     {40000,
//         400000},
//     {75000,
//         300000},
//     {100000,
//         200000}
// };

// #define TETRIS_PIECES (sizeof(blocks)/sizeof(struct tetris_block))
// #define TETRIS_LEVELS (sizeof(levels)/sizeof(struct tetris_level))



// void
// tetris_cleanup_io() {
//     // tcsetattr(fileno(stdin),TCSANOW,&save);
// }

// void
// tetris_signal_quit(int s) {
//     tetris_cleanup_io();
// }

// // void
// // tetris_set_ioconfig() {
// //     struct termios custom;
// //     int fd=fileno(stdin);
// //     tcgetattr(fd, &save);
// //     custom=save;
// //     custom.c_lflag &= ~(ICANON|ECHO);
// //     tcsetattr(fd,TCSANOW,&custom);
// //     fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0)|O_NONBLOCK);
// // }

// void
// tetris_init(struct tetris *t,int w,int h) {
//     int x, y;
//     int mem=0x3000;
//     t->level = 1;
//     t->score = 0;
//     t->gameover = 0;
//     t->w = w;
//     t->h = h;
    
//     t->game = (unsigned char*)(mem);
//     mem+=sizeof(unsigned char)*w;
//     for (x=0; x<w; x++) {
//         t->game[x] = ( unsigned char*)(mem);
//         mem+=sizeof(unsigned char)*h;
//         for (y=0; y<h; y++)
//             t->game[x][y] = ' ';
//     }
// }

// void tetris_clean(struct tetris *t) {
//     // int x;
//     // for (x=0; x<t->w; x++) {
//     //     free(t->game[x]);
//     // }
//     // free(t->game);
// }

// void tetris_print(struct tetris *t) {
//     int x,y;
//     for (x=0; x<30; x++)
//         print_string("\n");
//     // print_string("[LEVEL: %d | SCORE: %d]\n", t->level, t->score);
    // print_string("Level: ");
    // print_string(t->level);
    // print_string("  |Score: ");
    // print_string(t->score);

//     for (x=0; x<2*t->w+2; x++)
//         print_string("~");
//     print_string("\n");
//     for (y=0; y<t->h; y++) {
//         print_string ("!");
//         for (x=0; x<t->w; x++) {
//             if (x>=t->x && y>=t->y 
//                     && x<(t->x+t->current.w) && y<(t->y+t->current.h) 
//                     && t->current.data[y-t->y][x-t->x]!=' ')
//                 print_string(t->current.data[y-t->y][x-t->x]);
//             else
//                 print_string(t->game[x][y]);
//         }
//         print_string ("!\n");
//     }
//     for (x=0; x<2*t->w+2; x++)
//         print_string("~");
//     print_string("\n");
// }

// int tetris_hittest(struct tetris *t) {
//     int x,y,X,Y;
//     struct tetris_block b=t->current;
//     for (x=0; x<b.w; x++)
//         for (y=0; y<b.h; y++) {
//             X=t->x+x;
//             Y=t->y+y;
//             if (X<0 || X>=t->w)
//                 return 1;
//             if (b.data[y][x]!=' ') {
//                 if ((Y>=t->h) || 
//                         (X>=0 && X<t->w && Y>=0 && t->game[X][Y]!=' ')) {
//                     return 1;
//                 }
//             }
//         }
//     return 0;
// }

// void tetris_new_block(struct tetris *t) {
//     t->current=blocks[random()%TETRIS_PIECES];
//     t->x=(t->w/2) - (t->current.w/2);
//     t->y=0;
//     if (tetris_hittest(t)) {
//         t->gameover=1;
//     }
// }

// void
// tetris_print_block(struct tetris *t) {
//     int x,y,X,Y;
//     struct tetris_block b=t->current;
//     for (x=0; x<b.w; x++)
//         for (y=0; y<b.h; y++) {
//             if (b.data[y][x]!=' ')
//                 t->game[t->x+x][t->y+y]=b.data[y][x];
//         }
// }

// void
// tetris_rotate(struct tetris *t) {
//     struct tetris_block b=t->current;
//     struct tetris_block s=b;
//     int x,y;
//     b.w=s.h;
//     b.h=s.w;
//     for (x=0; x<s.w; x++)
//         for (y=0; y<s.h; y++) {
//             b.data[x][y]=s.data[s.h-y-1][x];
//         }
//     x=t->x;
//     y=t->y;
//     t->x-=(b.w-s.w)/2;
//     t->y-=(b.h-s.h)/2;
//     t->current=b;
//     if (tetris_hittest(t)) {
//         t->current=s;
//         t->x=x;
//         t->y=y;
//     }
// }

// void
// tetris_gravity(struct tetris *t) {
//     int x,y;
//     t->y++;
//     if (tetris_hittest(t)) {
//         t->y--;
//         tetris_print_block(t);
//         tetris_new_block(t);
//     }
// }

// void tetris_fall(struct tetris *t, int l) {
//     int x,y;
//     for (y=l; y>0; y--) {
//         for (x=0; x<t->w; x++)
//             t->game[x][y]=t->game[x][y-1];
//     }
//     for (x=0; x<t->w; x++)
//         t->game[x][0]=' ';
// }

// void tetris_check_lines(struct tetris *t) {
//     int x,y,l;
//     int p=100;
//     for (y=t->h-1; y>=0; y--) {
//         l=1;
//         for (x=0; x<t->w && l; x++) {
//             if (t->game[x][y]==' ') {
//                 l=0;
//             }
//         }
//         if (l) {
//             t->score += p;
//             p*=2;
//             tetris_fall(t, y);
//             y++;
//         }
//     }
// }

// int tetris_level(struct tetris *t) {
//     int i;
//     for (i=0; i<TETRIS_LEVELS; i++) {
//         if (t->score>=levels[i].score) {
//             t->level = i+1;
//         } else break;
//     }
//     return levels[t->level-1].nsec;
// }

// void tetris_run(int w, int h) {
//     struct timespec tm;
//     struct tetris t;
//     char cmd;
//     int count=0;
//     tetris_set_ioconfig();
//     tetris_init(&t, w, h);
//     srand(time(NULL));

//     tm.tv_sec=0;
//     tm.tv_nsec=1000000;

//     tetris_new_block(&t);
//     while (!t.gameover) {
//         nanosleep(&tm, NULL);
//         count++;
//         if (count%50 == 0) {
//             tetris_print(&t);
//         }
//         if (count%350 == 0) {
//             tetris_gravity(&t);
//             tetris_check_lines(&t);
//         }
//         // while ((cmd=getchar())>0) {
//         while(1)
//             switch (cmd) {
//                 case 'q':
//                     t.x--;
//                     if (tetris_hittest(&t))
//                         t.x++;
//                     break;
//                 case 'd':
//                     t.x++;
//                     if (tetris_hittest(&t))
//                         t.x--;
//                     break;
//                 case 's':
//                     tetris_gravity(&t);
//                     break;
//                 case ' ':
//                     tetris_rotate(&t);
//                     break;
//             }
//         }
//         tm.tv_nsec=tetris_level(&t);
//     }

//     // tetris_print(&t);
//     print_string();

//     // tetris_clean(&t);
//     // tetris_cleanup_io();
// }

#include "screen_driver.h"
#include "keyboard.h"
#include "util.h"


struct tetris_level {
    int score;
    int nsec;
};

struct tetris {
    char **game;
    int w;
    int h;
    int level;
    int gameover;
    int score;
    struct tetris_block {
        char data[5][5];
        int w;
        int h;
    } current;
    int x;
    int y;
};

struct tetris_block blocks[] =
{
    {{"##", 
         "##"},
    2, 2
    },
    {{" X ",
         "XXX"},
    3, 2
    },
    {{"@@@@"},
        4, 1},
    {{"OO",
         "O ",
         "O "},
    2, 3},
    {{"&&",
         " &",
         " &"},
    2, 3},
    {{"ZZ ",
         " ZZ"},
    3, 2}
};

struct tetris_level levels[]=
{
    {0,
        1200000},
    {1500,
        900000},
    {8000,
        700000},
    {20000,
        500000},
    {40000,
        400000},
    {75000,
        300000},
    {100000,
        200000}
};

#define TETRIS_PIECES (sizeof(blocks)/sizeof(struct tetris_block))
#define TETRIS_LEVELS (sizeof(levels)/sizeof(struct tetris_level))

void tetris_init(struct tetris *t,int w,int h) {
    int x, y;
    int mem=0x3000;
    t->level = 1;
    t->score = 0;
    t->gameover = 0;
    t->w = w;
    t->h = h;
    
    t->game = (char**)(mem);
    mem+=sizeof( char)*w;
    for (x=0; x<w; x++) {
        t->game[x] = (  char*)(mem);
        mem+=sizeof( char)*h;
        for (y=0; y<h; y++)
            t->game[x][y] = ' ';
    }
}

void tetris_clean(struct tetris *t) {
    // int x;
    // for (x = 0; x < t->w; x++) {
    //     kfree(t->game[x]);
    // }
    // kfree(t->game);
    clrscr();
}

void tetris_print(struct tetris *t) {
    int x, y;
    for (x = 0; x < 30; x++)
        print_string("\n");
    print_string("Level: ");
    print_int(t->level);
    print_string("  |Score: ");
    print_int(t->score);
    print_string("\n");

    for (x = 0; x < 2 * t->w + 2; x++)
        print_string("~");
    print_string("\n");
    for (y = 0; y < t->h; y++) {
        print_string("!");
        for (x = 0; x < t->w; x++) {
            if (x >= t->x && y >= t->y && x < (t->x + t->current.w) && y < (t->y + t->current.h) && t->current.data[y - t->y][x - t->x] != ' ')
                {
                char s[10]={t->current.data[y - t->y][x - t->x],'\0'};
                print_string(s);
                }
            else
                print_int(t->game[x][y]);
        }
        print_string("!\n");
    }
    for (x = 0; x < 2 * t->w + 2; x++)
        print_string("~");
    print_string("\n");
}

int tetris_hittest(struct tetris *t) {
    int x, y, X, Y;
    struct tetris_block b = t->current;
    for (x = 0; x < b.w; x++)
        for (y = 0; y < b.h; y++) {
            X = t->x + x;
            Y = t->y + y;
            if (X < 0 || X >= t->w)
                return 1;
            if (b.data[y][x] != ' ') {
                if ((Y >= t->h) || 
                        (X >= 0 && X < t->w && Y >= 0 && t->game[X][Y] != ' ')) {
                    return 1;
                }
            }
        }
    return 0;
}

void tetris_new_block(struct tetris *t) {
    t->current = blocks[random() % TETRIS_PIECES];
    t->x = (t->w / 2) - (t->current.w / 2);
    t->y = 0;
    if (tetris_hittest(t)) {
        t->gameover = 1;
    }
}

void tetris_print_block(struct tetris *t) {
    int x, y, X, Y;
    struct tetris_block b = t->current;
    for (x = 0; x < b.w; x++)
        for (y = 0; y < b.h; y++) {
            if (b.data[y][x] != ' ')
                t->game[t->x + x][t->y + y] = b.data[y][x];
        }
}

void tetris_rotate(struct tetris *t) {
    struct tetris_block b = t->current;
    struct tetris_block s = b;
    int x, y;
    b.w = s.h;
    b.h = s.w;
    for (x = 0; x < s.w; x++)
        for (y = 0; y < s.h; y++) {
            b.data[x][y] = s.data[s.h - y - 1][x];
        }
    x = t->x;
    y = t->y;
    t->x -= (b.w - s.w) / 2;
    t->y -= (b.h - s.h) / 2;
    t->current = b;
    if (tetris_hittest(t)) {
        t->current = s;
        t->x = x;
        t->y = y;
    }
}

void tetris_gravity(struct tetris *t) {
    int x, y;
    t->y++;
    if (tetris_hittest(t)) {
        t->y--;
        tetris_print_block(t);
        tetris_new_block(t);
    }
}

void tetris_fall(struct tetris *t, int l) {
    int x, y;
    for (y = l; y > 0; y--) {
        for (x = 0; x < t->w; x++)
            t->game[x][y] = t->game[x][y - 1];
    }
    for (x = 0; x < t->w; x++)
        t->game[x][0] = ' ';
}

void tetris_check_lines(struct tetris *t) {
    int x, y, l;
    int p = 100;
    for (y = t->h - 1; y >= 0; y--) {
        l = 1;
        for (x = 0; x < t->w && l; x++) {
            if (t->game[x][y] == ' ') {
                l = 0;
            }
        }
        if (l) {
            t->score += p;
            p *= 2;
            tetris_fall(t, y);
            y++;
        }
    }
}

int tetris_level(struct tetris *t) {
    int i;
    for (i = 0; i < TETRIS_LEVELS; i++) {
        if (t->score >= levels[i].score) {
            t->level = i + 1;
        } else break;
    }
    return levels[t->level - 1].nsec;
}

void tetris_run(int w, int h) {
    struct tetris t;
    char cmd;
    int count = 0;
    tetris_init(&t, w, h);
    srand(time(NULL));

    tetris_new_block(&t);
    while (!t.gameover) {
        // Add your own delay function here if necessary
        count++;
        if (count % 50 == 0) {
            tetris_print(&t);
        }
        if (count % 350 == 0) {
            tetris_gravity(&t);
            tetris_check_lines(&t);
        }
        while ((cmd = kgetchar()) > 0) {
            switch (cmd) {
                case 'q':
                    t.x--;
                    if (tetris_hittest(&t))
                        t.x++;
                    break;
                case 'd':
                    t.x++;
                    if (tetris_hittest(&t))
                        t.x--;
                    break;
                case 's':
                    tetris_gravity(&t);
                    break;
                case ' ':
                    tetris_rotate(&t);
                    break;
            }
        }
    }

    tetris_print(&t);
    print_string("*** GAME OVER ***\n");

    tetris_clean(&t);
}
