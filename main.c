#include <inttypes.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// digits from 0-9 + colon
uint32_t font_map[] = {31599, 19812, 14479, 31207, 23524, 29411, 29679, 30866, 31727, 31719, 1040};

#define FPS         4
#define FONT_ROWS   5
#define FONT_COLS   3
#define PADDING     2
#define CHAR_WIDTH  (3*FONT_COLS + 2*PADDING)
#define CHAR_HEIGHT 1
#define SQUARE "\u25A0"

void show_cursor(void) {printf("\033[?25h");}
inline void hide_cursor(void) {printf("\033[?25l");}
inline void clear_screen(void) {printf("\033[2J");}
inline void move_cursor_abs(uint32_t x, uint32_t y) {printf("\033[%d;%dH", y, x);}
inline void print_colored(const char *msg) {printf("\033[37;1m%s\033[0m", msg);}
inline void print_padding(uint32_t n) {printf("%*.s", n, "");}

void render_character(uint32_t ch, uint32_t X, uint16_t Y);
void render_time(void);

void INTHandler(int a) {(void)a; show_cursor(); exit(0);}

int main(void)
{
    signal(SIGINT, INTHandler);

    hide_cursor();
    clear_screen();

    while(1) {
        render_time();
        usleep(1000000 / FPS);
    }

    return 0;
}

void render_character(uint32_t ch, uint32_t X, uint16_t Y)
{
    move_cursor_abs(X, Y);

    uint32_t flag;
    for (int32_t y = FONT_ROWS-1; y >= 0; --y) {
        flag = ch >> (y * FONT_COLS);
        for (int32_t x = 0; x < FONT_COLS; ++x) {
            if ((flag >> x) & 1) print_colored(SQUARE);
            else printf(" ");

            print_padding(PADDING);
        }
        move_cursor_abs(X, Y + FONT_ROWS - y);
    }
}

void render_time(void)
{
    // query local time
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    // hh : mm : ss
    uint32_t clock[8];

    clock[0] = tm->tm_hour / 10;
    clock[1] = tm->tm_hour % 10;
    clock[2] = 10;  // colon
    clock[3] = tm->tm_min  / 10;
    clock[4] = tm->tm_min  % 10;
    clock[5] = 10;  // colon
    clock[6] = tm->tm_sec  / 10;
    clock[7] = tm->tm_sec  % 10;

    for (uint32_t i = 0; i < 8; ++i) {
        render_character(font_map[clock[i]], i*CHAR_WIDTH, 1);
    }
}