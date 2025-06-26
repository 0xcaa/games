#include <unistd.h>
#include <curses.h>

typedef struct {
    int x;
    int y;
} vec2;

int main(){
    int screen_width = 40;
    int screen_height= 20;

//    WINDOW *win = initscr();
//    keypad(win, true);
//    nodelay(win, true);

    initscr();
    keypad(stdscr, true);
    nodelay(stdscr, true);

    curs_set(0);


    vec2 head = {0, 0};
    vec2 dir = {1, 0};

    while(true) {
        int pressed = getch();

        if (pressed == KEY_LEFT) {
            dir.x = -1;
            dir.y = 0;
        }
        if (pressed == KEY_RIGHT) {
            dir.x = 1;
            dir.y = 0;
        }
        if (pressed == KEY_UP) {
            dir.x = 0;
            dir.y = -1;
        }
        if (pressed == KEY_DOWN) {
            dir.x = 0;
            dir.y = 1;
        }
        // 27 = \e
        if (pressed == 27) {
            break;
        }
        head.x += dir.x;
        head.y += dir.y;
        
        erase();
        mvaddch(head.y, head.x, 'O');
        usleep(125000);
//        usleep(1250);
    }
    endwin();
    return 0;

}
