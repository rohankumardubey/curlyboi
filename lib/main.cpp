#include <time.h>
#include <locale.h>
#include <ncurses.h>
#include <pybind11/pybind11.h>
#include "backend.h"
#include "frontend.h"

void game() {
    setlocale(LC_ALL, "");

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);  // make arrow keys work
    curs_set(0);           // hide cursor
    timeout(100);          // getch() timeout

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);

    int xmax;
    int ymax;
    getmaxyx(stdscr, ymax, xmax);
    enum Direction dir = RIGHT;

    time_t t;
    srand((unsigned)time(&t));

    Board* board = create_board(create_snake(), NULL, xmax, ymax);
    int i;
    for (i = 0; i < 6; i++) {
        add_new_food(board);
    }

    while (true) {
        clear();    // clear screen
        display_snake(board->snake, dir);
        display_foods(board->foods);
        refresh();  // print new things
        dir = get_next_move(dir);
        enum Status status = move_snake(board, dir);
        if (status == FAILURE) break;
    }
    endwin();
}

PYBIND11_MODULE(_curlyboi, m) {
    m.doc() = "A simple curlyboi game written in C using ncurses.";
    m.def("game", &game, "The game function");
}
