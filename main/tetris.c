#include "tetris.h"
#include "/Users/manaskumar/Desktop/MAX-OS-P1/essentials/screen_driver.h"
#include "/Users/manaskumar/Desktop/MAX-OS-P1/essentials/util.h"
#include "/Users/manaskumar/Desktop/MAX-OS-P1/essentials/keyboard.h"
#include "/Users/manaskumar/Desktop/MAX-OS-P1/essentials/time.h"
#include <stddef.h>    


#define TETRIS_BLOCK_COUNT 6

struct tetris_block blocks[TETRIS_BLOCK_COUNT] = {
    {{"##", "##"}, 2, 2},
    {{" X ", "XXX"}, 3, 2},
    {{"@@@@"}, 4, 1},
    {{"OO", "O ", "O "}, 2, 3},
    {{"&&", " &", " &"}, 2, 3},
    {{"ZZ ", " ZZ"}, 3, 2}
};

struct tetris_level levels[] = {
    {0, 1200000},
    {1500, 900000},
    {8000, 700000},
    {20000, 500000},
    {40000, 400000},
    {75000, 300000},
    {100000, 200000}
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
    for (x = 0; x < w; x++) {
        for (y = 0; y < h; y++)
            t->game[x][y] = ' ';
    }
}

void tetris_print(const struct tetris *t) {
    int x, y;
    clrscr();
    for (y = 0; y < t->h; y++) {
        for (x = 0; x < t->w; x++) {
            if (t->game[x][y] == ' ') {
                print_char(' ', get_offset(y, x));
            } else {
                print_char(t->game[x][y], get_offset(y, x));
            }
        }
    }
    print_string("Level: ");
    print_string(itoa(t->level));
    print_string("\nScore: ");
    print_string(itoa(t->score));
}

void tetris_new_block(struct tetris *t) {
    t->current = blocks[rand() % TETRIS_PIECES];
    t->x = (t->w - t->current.w) / 2;
    t->y = 0;
    if (tetris_hittest(t)) {
        t->gameover = 1;
    } else {
        tetris_print_block(t);
    }
}

void tetris_print_block(struct tetris *t) {
    int x, y;
    for (y = 0; y < t->current.h; y++) {
        for (x = 0; x < t->current.w; x++) {
            if (t->current.data[y][x] != ' ' &&
                t->x + x >= 0 && t->x + x < t->w && t->y + y >= 0 && t->y + y < t->h) {
                t->game[t->x + x][t->y + y] = t->current.data[y][x];
            }
        }
    }
    tetris_print(t);
}

void tetris_clear_block(struct tetris *t) {
    int x, y;
    for (y = 0; y < t->current.h; y++) {
        for (x = 0; x < t->current.w; x++) {
            if (t->current.data[y][x] != ' ' &&
                t->x + x >= 0 && t->x + x < t->w && t->y + y >= 0 && t->y + y < t->h) {
                t->game[t->x + x][t->y + y] = ' ';
            }
        }
    }
}

void tetris_rotate(struct tetris *t) {
    struct tetris_block tmp = t->current;
    int x, y;
    for (y = 0; y < t->current.h; y++) {
        for (x = 0; x < t->current.w; x++) {
            tmp.data[x][t->current.h - y - 1] = t->current.data[y][x];
        }
    }
    t->current = tmp;
    if (tetris_hittest(t)) {
        // Handle rotation collision if needed
    }
}

int tetris_hittest(const struct tetris *t) {
    int x, y;
    for (y = 0; y < t->current.h; y++) {
        for (x = 0; x < t->current.w; x++) {
            if (t->current.data[y][x] != ' ' &&
                (t->x + x < 0 || t->x + x >= t->w || t->y + y >= t->h || t->game[t->x + x][t->y + y] != ' ')) {
                return 1;
            }
        }
    }
    return 0;
}

void tetris_place_block(struct tetris *t) {
    int x, y;
    for (y = 0; y < t->current.h; y++) {
        for (x = 0; x < t->current.w; x++) {
            if (t->current.data[y][x] != ' ' &&
                t->x + x >= 0 && t->x + x < t->w && t->y + y >= 0 && t->y + y < t->h) {
                t->game[t->x + x][t->y + y] = t->current.data[y][x];
            }
        }
    }
}

void tetris_gravity(struct tetris *t) {
    tetris_clear_block(t);
    t->y++;
    if (tetris_hittest(t)) {
        t->y--;
        tetris_place_block(t);
        tetris_check_lines(t);
        tetris_new_block(t);
    } else {
        tetris_place_block(t);
    }
}

void tetris_check_lines(struct tetris *t) {
    int x, y, l;
    for (y = t->h - 1; y >= 0; y--) {
        for (x = 0; x < t->w; x++) {
            if (t->game[x][y] == ' ')
                break;
        }
        if (x == t->w) {
            for (l = y; l > 0; l--) {
                for (x = 0; x < t->w; x++) {
                    t->game[x][l] = t->game[x][l - 1];
                }
            }
            for (x = 0; x < t->w; x++) {
                t->game[x][0] = ' ';
            }
            t->score += 100;
        }
    }
}

int tetris_level(const struct tetris *t) {
    return levels[t->level - 1].nsec;
}

void simulated_nanosleep(unsigned int ns) {
    unsigned int start = get_system_tick();
    while ((get_system_tick() - start) < ns / 1000000); // Assuming tick frequency is 100 Hz
}

void tetris_run(struct tetris *t, int w, int h) {
    tetris_new_block(t);
    while (!t->gameover) {
        simulated_nanosleep(tetris_level(t));
        tetris_gravity(t);
        tetris_print(t);
    }

    tetris_print(t);
    print_string(" *** GAME OVER ***\n");
}

void tetris_handle_input(struct tetris *t, char cmd) {
    tetris_clear_block(t);
    switch (cmd) {
        case 'q':
            t->x--;
            if (tetris_hittest(t))
                t->x++;
            break;
        case 'd':
            t->x++;
            if (tetris_hittest(t))
                t->x--;
            break;
        case 's':
            t->y++;
            if (tetris_hittest(t))
                t->y--;
            break;
        case ' ':
            tetris_rotate(t);
            break;
    }
    tetris_place_block(t);
}
