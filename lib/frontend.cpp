#include <stdlib.h>
#include <ncurses.h>
#include "backend.h"
#include "frontend.h"

enum Direction get_next_move(enum Direction previous) {
    int ch = getch();
    switch (ch) {
        case KEY_LEFT:
            if (previous != RIGHT) return LEFT;
        case KEY_RIGHT:
            if (previous != LEFT) return RIGHT;
        case KEY_DOWN:
            if (previous != UP) return DOWN;
        case KEY_UP:
            if (previous != DOWN) return UP;
        default:
            return previous;
    }
}

void display_snake(Point* snake, enum Direction dir) {
    int pos = 0;
    const wchar_t* symbol = L"▛";

    while (snake) {
        switch (dir) {
            case UP:
                symbol = snake->y % 2 == 0 ? L"▟" : L"▙";
                break;
            case DOWN:
                symbol = snake->y % 2 == 0 ? L"▛" : L"▜";
                break;
            case LEFT:
                symbol = snake->x % 2 == 0 ? L"▟" : L"▜";
                break;
            case RIGHT:
                symbol = snake->x % 2 == 0 ? L"▛" : L"▙";
                break;
        }
        attron(COLOR_PAIR((pos % 5) + 1));
        mvaddwstr(snake->y, snake->x, symbol);

        pos = pos + 1;
        snake = snake->next;
    }
}

void display_foods(Point* food) {
    while(food) {
        mvaddwstr(food->y, food->x, food->data);
        food = food->next;
    }
}
