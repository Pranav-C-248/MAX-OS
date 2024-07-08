#include "/mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/screen_driver.h"
#include "/mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/keyboard.h"
#include "/mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/memory.h" 
#include "/mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/util.h"   

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

struct tetris_block blocks[] = {
    {{"##",
      "##"},
     2, 2},
    {{" X ",
      "XXX"},
     3, 2},
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

struct tetris_level levels[] = {
    {0, 72},
    {1500, 54},
    {8000, 42},
    {20000, 30},
    {40000, 24},
    {75000, 18},
    {100000, 12}
};

#define TETRIS_PIECES (sizeof(blocks) / sizeof(struct tetris_block))
#define TETRIS_LEVELS (sizeof(levels) / sizeof(struct tetris_level))

void tetris_init(struct tetris *t, int w, int h) {
    int x, y;
    t->level = 1;
    t->score = 0;
    t->gameover = 0;
    t->w = w;
    t->h = h;
    t->game = mallok(sizeof(char *) * w);
    for (x = 0; x < w; x++) {
        t->game[x] = mallok(sizeof(char) * h);
        for (y = 0; y < h; y++)
            t->game[x][y] = ' ';
    }
}

void tetris_clean(struct tetris *t) {
    int x;
    for (x = 0; x < t->w; x++) {
        freek(t->game[x]);
    }
    freek(t->game);
}

void tetris_print(struct tetris *t) {
    clrscr();
    print_string("[LEVEL: ");
    print_int(t->level);
    print_string(" | SCORE: ");
    print_int(t->score);
    print_string("]\n");
    for (int y = 0; y < t->h; y++) {
        print_string("!");
        for (int x = 0; x < t->w; x++) {
            char to_print = ' ';
            if (x >= t->x && y >= t->y &&
                x < (t->x + t->current.w) && y < (t->y + t->current.h) &&
                t->current.data[y - t->y][x - t->x] != ' ')
                to_print = t->current.data[y - t->y][x - t->x];
            else
                to_print = t->game[x][y];

            char *s={to_print,'\0'};
            print_string(s);
            print_string("  ");
        }
        print_string("!");
        print_string("\n");
    }
}

void tetris_game_loop(struct tetris *t) {
    uint32_t last_tick = get_system_tick();
    uint32_t current_tick = last_tick;
    while (!t->gameover) {
        current_tick = get_system_tick();
        if (current_tick - last_tick >= levels[t->level - 1].nsec) {
            tetris_gravity(t);
            tetris_check_lines(t);
            tetris_print(t);
            last_tick = current_tick;
        }
        char cmd = get_key();
        switch (cmd) {
            case 'q': t->x--; if (tetris_hittest(t)) t->x++; break;
            case 'd': t->x++; if (tetris_hittest(t)) t->x--; break;
            case 's': tetris_gravity(t); break;
            case ' ': tetris_rotate(t); break;
        }
    }
    tetris_print(t);
    print_string("*** GAME OVER ***\n");
    tetris_clean(t);
}

void tetris_run(int w, int h) {
    struct tetris t;
    tetris_init(&t, w, h);
    tetris_new_block(&t);
    tetris_game_loop(&t);
}