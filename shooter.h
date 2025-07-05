#ifndef SHOOTER_H
#define SHOOTER_H

#define MAX_SCORE 256
#define FRAME_TIME 11

typedef struct {
    int x;
    int y;
} vec2;

int score = 0;
int bullet_loc = 0;
bool skip = false;
bool is_running = true;
bool fire_on = false;
int screen_width = 45;
int screen_height = 35;
char score_message[16];

vec2 segments[256];
vec2 dir = { 0, 0 };
vec2 head = { 0, 0 };
vec2 bullet;

vec2 berry;

void fire_bullet();
void quit_game(void);
void draw_border(int y, int x, int width, int height);
void draw(void);
void game_over(void);
void update(void);
bool collide_snake_body(vec2 point);
bool collide(vec2 a, vec2 b);
void restart_game(void);
void process_input(void);
void init(void);


#endif
