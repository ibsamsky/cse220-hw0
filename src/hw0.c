#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hw0.h"

#define ROWS 5
#define COLS 5

int top_key[COLS] = {1, 2, 3, 4, 5};
int bottom_key[COLS] = {1, 2, 3, 4, 5};
int left_key[ROWS] = {1, 2, 3, 4, 5};
int right_key[ROWS] = {1, 2, 3, 4, 5};

char board[ROWS][COLS] = {{'1', '1', '2', '-', '3'},
                          {'3', '2', '2', '3', '3'},
                          {'2', '1', '-', '4', '4'},
                          {'2', '-', '3', '2', '-'},
                          {'4', '5', '4', '1', '3'}};

// scanf(" %c", &choice); //this command will erase whitespace in the token
// selection and read 1 char (replace the 'c' with a 'd' to read an int)

bool read_int_range(int32_t *out, int32_t low, int32_t high) {
    char buf[9];
    int len = 0;
    if (1 > scanf(" %8s%n", buf, &len)) {
        return false;
    }

    return parse_int_range(out, buf, low, high);
}

bool parse_int_range(int32_t *dst, const char *src, int32_t low, int32_t high) {
    char *end;
    int64_t parsed = strtol(src, &end, 10);

    const bool range_err = errno == ERANGE;
    if (src == end || range_err) {
        return false; // conversion failed or overflow
    }
    if (parsed > __INT32_MAX__) {
        return false; // too big
    }
    int32_t parsed_int = (int32_t)parsed;

    if (parsed_int < low || parsed_int > high) {
        return false;
    }

    *dst = parsed_int;
    return true;
}

#define print_arr(FMT, ARR, LEN)                                               \
    for (int __i = 0; __i < LEN; __i++) {                                      \
        printf(FMT, ARR[__i]);                                                 \
    }

#define print_repeat(STR, LEN)                                                 \
    for (int __i = 0; __i < LEN; __i++) {                                      \
        printf(STR);                                                           \
    }

void print_board() {
    // printf("%*s", count, "") // hack!
    printf("   ");
    print_arr(" %d", top_key, COLS);
    printf("\n   ");
    print_repeat(" v", COLS);

    for (int i = 0; i < ROWS; i++) {
        printf("\n%d >", left_key[i]);
        print_arr(" %c", board[i], COLS);
        printf(" < %d", right_key[i]);
    }

    printf("\n   ");
    print_repeat(" ^", COLS);
    printf("\n   ");
    print_arr(" %d", bottom_key, COLS);
    printf("\n");
}

int main() {
    int num_empty = 0;
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            if (board[r][c] == '-')
                num_empty++;

    int piece = -1;
    int row = -1;
    int col = -1;

    do {
        print_board();

        char buf[9];
        do {
            printf("Choose a piece (1-5) or q to quit: ");
            scanf(" %8s", buf);
            if (0 == strcmp("q", buf))
                return 0;
        } while (false == parse_int_range(&piece, buf, 1, 5) &&
                 0 < printf("Invalid choice. "));

        do
            printf("Choose a row (0-4): ");
        while (false == read_int_range(&row, 0, 4) &&
               0 < printf("Invalid choice. "));

        do
            printf("Choose a column (0-4): ");
        while (false == read_int_range(&col, 0, 4) &&
               0 < printf("Invalid choice. "));

        // check occupied
        if ('-' != board[row][col]) {
            printf("Invalid choice. That space is already occupied.\n");
            continue;
        }

        // successfully placed a piece
        board[row][col] = (char)(piece + 0x30);
        num_empty--;
    } while (0 < num_empty);

    // game over
    printf("Congratulations, you have filled the board!\n");
    print_board();
    return 0;
}