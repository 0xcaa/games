#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>

#include "shooter.h"

// reverse snake
bool holding_up = false;
bool holding_down = false;
bool holding_left = false;
bool holding_right = false;

void quit_game(void) {
    // clean exit from app
    endwin();
    //clear screen, clean up cursor
    printf("\x1B[1;1H\x1B[2J");
    printf("\x1b[?25h");

    exit(0);
}

void draw_border(int y, int x, int width, int height) {
    // top row
    mvaddch(y, x, ACS_ULCORNER);
    mvaddch(y, x + width * 2 + 1, ACS_URCORNER);
    for (int i = 1;i <width * 2 + 1; i++) {
        mvaddch(y, x + i, ACS_HLINE);
    }

    // vertical lines
    for (int i = 1;i < height + 1; i++) {
        mvaddch(y + i, x, ACS_VLINE);
        mvaddch(y + i, x + width * 2 + 1, ACS_VLINE);
    }

    mvaddch(y + height + 1, x, ACS_LLCORNER);
    mvaddch(y + height + 1, x + width * 2 + 1, ACS_LRCORNER);
    for (int i = 1; i < width * 2 + 1; i++) {
        mvaddch(y + height + 1, x +i, ACS_HLINE);
    }
}

void draw(void) {
    erase();

    attron(COLOR_PAIR(1));
    mvaddch(berry.y+1, berry.x * 2+1, '@');
    attroff(COLOR_PAIR(1));


    attron(COLOR_PAIR(2));
    for (int i = 0; i < score; i++) {
        mvaddch(segments[i].y+1, segments[i].x * 2 + 1, ACS_DIAMOND);
    }
    mvaddch(head.y+1, head.x * 2+1, 'O');
    attroff(COLOR_PAIR(2));

    if (fire_on) {
        attron(COLOR_PAIR(1));
        mvaddch(bullet.y+bullet_loc, bullet.x * 2+1, 'l');
        attroff(COLOR_PAIR(1));
    }


    attroff(COLOR_PAIR(3));
    draw_border(0, 0, screen_width, screen_height);
    attroff(COLOR_PAIR(3));
    mvaddstr(0, screen_width - 5, score_message);
}

vec2 spawn_berry(void) {
    vec2 berry = { 1 + rand() % (screen_width -2), 1 + rand() % (screen_height -2) };
    while (collide(head, berry) || collide_snake_body(berry)) {
        berry.x = 1 + rand() % (screen_width -2);
        berry.y = 1 + rand() % (screen_height - 2);
    }
    return berry;

}
void game_over(void) {
    while (is_running == false) {
        process_input();

        mvaddstr(screen_height / 2, screen_width - 16,
            "   game over   ");
        mvaddstr(screen_height / 2 + 1, screen_width - 16,
            "   space to restart esc to quit   ");

        attron(COLOR_PAIR(3));
        draw_border(screen_height / 2 - 1, screen_width - 17, 17,2);
        attroff(COLOR_PAIR(3));

//        usleep(FRAME_TIME);
        napms(FRAME_TIME);
    }

}

void update(void) {
    for (int i = score; i > 0; i--) {
        segments[i] = segments[i -1];
    }
    segments[0] = head;

// move head
    head.x += dir.x;
    head.y += dir.y;

    if (collide_snake_body(head) || head.x < 0 || head.y < 0 \
        || head.x >= screen_width || head.y >= screen_height) {
        is_running = false;
        game_over();
    }

    // eating berry
    if (collide(bullet, berry)) {
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
//  bullet update
    if (bullet_loc > screen_width) {
        bullet_loc = 0;
        fire_on = false;
    }
    if (fire_on) {
        ++bullet_loc;
    }

    

    napms(FRAME_TIME);
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

void restart_game(void){ head.x = 0; head.y = 0;
    dir.x = 0;
    dir.y = 0;
    score = 0;
    sprintf(score_message, "[ Score: %d ]", score);
    is_running = true;
}

void process_input(void) {
    int pressed = getch();

    // Check all keys pressed this frame
    while (pressed != ERR) {
        switch (pressed) {
            case KEY_UP:    holding_up = true; break;
            case KEY_DOWN:  holding_down = true; break;
            case KEY_LEFT:  holding_left = true; break;
            case KEY_RIGHT: holding_right = true; break;
            case 'q':       quit_game(); exit(0);
        }
        pressed = getch(); // read next input
    }

    // Reset direction based on which keys are held
    dir.x = 0;
    dir.y = 0;
    if (holding_up)    dir.y = -1;
    if (holding_down)  dir.y = 1;
    if (holding_left)  dir.x = -1;
    if (holding_right) dir.x = 1;

/*
    switch (pressed) {
        case KEY_LEFT:
            if (dir.x != 1) {
                dir.x = -1;
         //       dir.y = 0;
            }
            break;
        case KEY_RIGHT:
            if (dir.x != -1) {
                dir.x = 1;
        //        dir.y = 0;
            }
            break;
        case KEY_UP:
            if (dir.y != 1) {
           //     dir.x = 0;
                dir.y = -1;
            }
            break;
        case KEY_DOWN:
            if (dir.y != -1) {
          //      dir.x = 0;
                dir.y = 1;
            }
            break;
        case 'q':       quit_game(); break;
        case ' ':
            if (!fire_on) {
                fire_on = true;
                bullet.x = head.x;
                bullet.y = head.y;
            }
            break;
        default:
            dir.x = 0;
            dir.y = 0;
            break;
    }
    */



/*

    if (pressed == ' ') {
        if (!is_running)
            restart_game();
    }
    // 27 = \e
    if (pressed == 27) {
        is_running = false;
        quit_game();
    }
    */

}

void init(void){
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

int main(void){
    init();
    noecho();

    cbreak();
    keypad(stdscr, TRUE);

    nodelay(stdscr, TRUE);
    curs_set(FALSE);
    while(true) {
        process_input();
        if (skip == true) {
            skip = false;
            continue;
        }
        update();
        draw();
    }
    quit_game();
    return 0;
}
