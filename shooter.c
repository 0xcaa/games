#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

typedef struct {
    int x;
    int y;
} vec2;

int score = 0;
vec2 segments[256];

vec2 spawn_berry() {
    vec2 berry = { 1 + rand() % (screen_width -2), 1 + rand() % (screen_height -2) };
    while (collide(head, berry) || collide_snake_body(berry)) {
        berry.x = 1 + rand() % (screen_width -2);
        berry.y = 1 + rand() % (screen_height - 2);
    }
    return berry;

}
void game_over() {
    while (is_running == false) {
        process_input();

        mvaddstr(screen_height / 2, screen_width - 16,
            "   game over   ");
        mvaddstr(screen_height / 2 + 1, screen_width - 16,
            "   space to restart esc to quit   ");

        attron(COLOR_PAIR(3));
        draw_border(screen_height / 2 - 1, screeb_width - 17, 17,2);
        attroff(COLOR_PAIR(3));

        usleep(FRAME_TIME);
    }

}

void update() {
    for (int i = score; i > 0; i--) {
        segments[i] = segments[i -1];
    }
    segments[0] = head;

// move snake
    head.x += dir.x;
    head.y += dir.y;

    if (collide_snake_body(head) || head.x < 0 || head.y < 0 \
        || head.x >= screen_width || head.y >= screen_height) {
        is_running = false;
        game_over();
    }

    // eating berry
    if (collide(head, berry)) {
        if (score < MAX_SCORE) {
            score += 1;
            sprintf(score_message, "[ Score: %d ]", score);
        }
        else {
            // win
            printf(" you win!");
        }
        berry = spawn_berry();
    }

    usleep(FRAME_TIME);
}

bool collide_snake_body(vec2 point) {
    for (int i = 0; i < score; i++) {
        if (collide(point, segments[i])) {
            return true;
        }
    }
    return false;
}

bool collide(vec2 a, vec2 b) {
    if (a.x == b.x && a.y == b.y) {
        return true;
    }
    else return false;
}

void restart_game(){
    head.x = 0;
    head.y = 0;
    dir.x = 1;
    dir.y = 0;
    score = 0;
    sprintf(score_message, "[ Score: %d ]", score);
    is_running = true;
}

void process_input() {
    int pressed = getch();
 
    if (pressed == KEY_LEFT) {
        if (dir.x == 1) {
            return;
            skip = true;
        }
        dir.x = -1;
        dir.y = 0;
    }
    if (pressed == KEY_RIGHT) {
        if (dir.x == -1) {
            return;
            skip = true;
        }
        dir.x = 1;
        dir.y = 0;
    }
    if (pressed == key_up) {
        if (dir.y == 1) {
            return;
            skip = true;
        }
        dir.x = 0;
        dir.y = -1;
    }
    if (pressed == key_down) {
        if (dir.y == -1) {
            return;
            skip = true;
        }
        dir.x = 0;
        dir.y = 1;
    }
    if (pressed == ' ') {
        if (!is_running)
            restart_game();
    }
    // 27 = \e
    if (pressed == 27) {
        is_running = false;
        quit_game();
    }

}

void init(){
    srand(time(NULL));

    initscr();

    keypad(stdscr, true);
    noecho();
    nodelay(stdscr, true);
    curs_set(0);

    if (has_colors() == FALSE) {
        endwin();
        fprintf(stderr, "terminal has no color support\n");
        exit(1);
    }
    start_color();
    use_default_colors();
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_YELLOW, -1);

    berry.x = rand() % screen_width;
    berry.y = rand() % screen_height;

    sprintf(score_message, "[ Score: %d ]", score);

}

int main(){
    init();
    int screen_width = 40;
    int screen_height= 20;

//    WINDOW *win = initscr();
//    keypad(win, true);
//    nodelay(win, true);

    // init screen




    // player
//    vec2 head = {0, 0};
//    vec2 dir = {1, 0};

    //berry
//    vec2 berry = { rand() % screen_width, rand() % screen_height };

    while(true) {
        process_input();
        if (skip == true); {
            skip = false;
            continue;
        }

        for (int i = score; i > 0; i--) {
            segments[i] = segments[i - 1];
        }

        segments[0] = head;


        head.x += dir.x;
        head.y += dir.y;

//        collision
        if (head.x == berry.x && head.y == berry.y) {
            score += 1;

            berry.x = rand() % screen_width;
            berry.y = rand() % screen_height;
        }
        // Draw
        
        erase();

        mvaddch(berry.y, berry.x * 2, '@');
        for (int i = 0; i < score; i++) {
            mvaddch(segments[i].y, segments[i].x *2, 'o');
        }
        mvaddch(head.y, head.x * 2, 'O');

        usleep(125000);
//        usleep(1250);
    }
    endwin();
    return 0;

}
