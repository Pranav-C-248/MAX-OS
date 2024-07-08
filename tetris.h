#ifndef TETRIS_H
#define TETRIS_H

#define MAX_WIDTH 40
#define MAX_HEIGHT 20

struct tetris_level {
    int score;
    int nsec;
};

struct tetris {
    char game[MAX_WIDTH][MAX_HEIGHT];
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

void tetris_init(struct tetris *t, int w, int h);
void tetris_print(struct tetris *t);
void tetris_new_block(struct tetris *t);
void tetris_print_block(struct tetris *t);
void tetris_clear_block(struct tetris *t);
void tetris_rotate(struct tetris *t);
int tetris_hittest(struct tetris *t);
void tetris_place_block(struct tetris *t);
void tetris_gravity(struct tetris *t);
void tetris_check_lines(struct tetris *t);
int tetris_level(struct tetris *t);
void tetris_run(struct tetris *t, int w, int h);
void tetris_handle_input(struct tetris *t, char cmd);

#endif // TETRIS_H
