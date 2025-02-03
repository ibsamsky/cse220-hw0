#include <stdio.h>
#include <stdlib.h>

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

#define READ(T, fmt)                                                           \
	int read_##T(T *ptr) { return scanf(fmt, ptr); }

READ(int, " %d")

typedef enum option_state { some, none } state;

typedef struct option_int {
	state state;
	union inner {
		int some;
		void *none;
	} inner;
} opt_int;

int _opt_int_unwrap(opt_int *option, int line, char const *file) {
	if (option->state == none) {
		printf("%s:%d: Called `unwrap` on a `none` value\n", file, line);
		exit(1);
	}

	return option->inner.some;
}

/**
 * Unwraps the contained value.
 *
 * # Safety
 * Unwrapping a `none` option is UB
 */
#define opt_int_unwrap(OPTION) _opt_int_unwrap(OPTION, __LINE__, __FILE__)

int main() {
	opt_int o = {.state = none, .inner = {1}};

	int v = opt_int_unwrap(&o);
	printf("val %d\n", v);
	return 0;
}