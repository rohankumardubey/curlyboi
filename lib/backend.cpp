#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "backend.h"

const int NUM_FOODS = 113;
wchar_t* FOODS[113] = {
    L"🍇",
    L"🍈",
    L"🍉",
    L"🍊",
    L"🍋",
    L"🍌",
    L"🍍",
    L"🥭",
    L"🍎",
    L"🍏",
    L"🍐",
    L"🍑",
    L"🍒",
    L"🍓",
    L"🥝",
    L"🍅",
    L"🥥",
    L"🥑",
    L"🍆",
    L"🥔",
    L"🥕",
    L"🌽",
    L"🌶",
    L"🥒",
    L"🥬",
    L"🥦",
    L"🧄",
    L"🧅",
    L"🍄",
    L"🥜",
    L"🌰",
    L"🍞",
    L"🥐",
    L"🥖",
    L"🥨",
    L"🥯",
    L"🥞",
    L"🧇",
    L"🧀",
    L"🍖",
    L"🍗",
    L"🥩",
    L"🥓",
    L"🍔",
    L"🍟",
    L"🍕",
    L"🌭",
    L"🥪",
    L"🌮",
    L"🌯",
    L"🥙",
    L"🧆",
    L"🥚",
    L"🍳",
    L"🥘",
    L"🍲",
    L"🥣",
    L"🥗",
    L"🍿",
    L"🧈",
    L"🧂",
    L"🥫",
    L"🍱",
    L"🍘",
    L"🍙",
    L"🍚",
    L"🍛",
    L"🍜",
    L"🍝",
    L"🍠",
    L"🍢",
    L"🍣",
    L"🍤",
    L"🍥",
    L"🥮",
    L"🍡",
    L"🥟",
    L"🥠",
    L"🥡",
    L"🦪",
    L"🍦",
    L"🍧",
    L"🍨",
    L"🍩",
    L"🍪",
    L"🎂",
    L"🍰",
    L"🧁",
    L"🥧",
    L"🍫",
    L"🍬",
    L"🍭",
    L"🍮",
    L"🍯",
    L"🍼",
    L"🥛",
    L"☕",
    L"🍵",
    L"🍶",
    L"🍾",
    L"🍷",
    L"🍹",
    L"🍺",
    L"🍻",
    L"🥂",
    L"🥃",
    L"🥤",
    L"🧃",
    L"🧉",
    L"🧊"
};

Point* create_cell(int x, int y, wchar_t* data) {
    Point* cell = (struct Point *) malloc(sizeof(struct Point));
    // Point* cell = malloc(sizeof(*cell));
    cell->x = x;
    cell->y = y;
    cell->data = data;
    cell->next = NULL;
    return cell;
}

Point* create_snake() {
    Point* a = create_cell(2, 6, NULL);
    Point* b = create_cell(2, 5, NULL);
    Point* c = create_cell(2, 4, NULL);
    Point* d = create_cell(2, 3, NULL);
    Point* e = create_cell(2, 2, NULL);

    a->next = b;
    b->next = c;
    c->next = d;
    d->next = e;

    return a;
}

Board* create_board(Point* snake, Point* foods, int xmax, int ymax) {
    Board* board = (struct Board *) malloc(sizeof(struct Board));
    // Board* board = malloc(sizeof(*board));
    board->foods = foods;
    board->snake = snake;
    board->xmax = xmax;
    board->ymax = ymax;
    return board;
}

bool is_same_place(Point* cell1, Point* cell2) {
    return cell1->x == cell2->x && cell1->y == cell2->y;
}

bool list_contains(Point* cell, Point* list) {
    Point* s = list;
    while (s) {
        if (is_same_place(s, cell)) {
            return true;
        }
        s = s->next;
    }
    return false;
}

Point* create_random_cell(int xmax, int ymax, wchar_t* food) {
    return create_cell(rand() % xmax, rand() % ymax, food);
}

void add_new_food(Board* board) {
    Point* new_food;
    do {
        new_food = create_random_cell(board->xmax, board->ymax, FOODS[rand() % NUM_FOODS]);
    } while (list_contains(new_food, board->foods) || list_contains(new_food, board->snake));
    new_food->next = board->foods;
    board->foods = new_food;
}

bool remove_from_list(Point* element, Point** list) {
    Point *currP, *prevP;
    prevP = NULL;

    for (currP = *list; currP != NULL; prevP = currP, currP = currP->next) {
        if (is_same_place(currP, element)) {
            if (prevP == NULL) {
                *list = currP->next;
            } else {
                prevP->next = currP->next;
            }
            free(currP);
            return true;
        }
    }
    return false;
}

Point* next_move(Board* board, enum Direction dir) {
    Point* snake = board->snake;
    int new_x = snake->x;
    int new_y = snake->y;

    switch (dir) {
        case UP:
            new_y = snake->y - 1;
            break;
        case DOWN:
            new_y = snake->y + 1;
            break;
        case LEFT:
            new_x = snake->x - 1;
            break;
        case RIGHT:
            new_x = snake->x + 1;
            break;
    }

    if (new_x < 0 || new_y < 0 || new_x >= board->xmax || new_y >= board->ymax) {
        return NULL;
    } else {
        return create_cell(new_x, new_y, NULL);
    }
}

enum Status move_snake(Board* board, enum Direction dir) {
    // Create a new beginning. Check boundaries.
    Point* begin = next_move(board, dir);
    if (begin == NULL) {
        return FAILURE;
    }

    // If we've gone backwards, don't do anything
    if (board->snake->next && is_same_place(begin, board->snake->next)) {
        begin->next = NULL;
        free(begin);
        return SUCCESS;
    }

    // Check for collisions
    if (list_contains(begin, board->snake)) {
        return FAILURE;
    }

    // Check for food
    if (list_contains(begin, board->foods)) {
        // Attach the beginning to the rest of the snake;
        begin->next = board->snake;
        board->snake = begin;
        remove_from_list(begin, &(board->foods));
        add_new_food(board);

        return SUCCESS;
    }

    // Attach the beginning to the rest of the snake
    begin->next = board->snake;
    board->snake = begin;

    // Cut off the end
    Point* end = board->snake;
    while (end->next->next) {
        end = end->next;
    }
    free(end->next);
    end->next = NULL;

    return SUCCESS;
}
