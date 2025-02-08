#include <stdbool.h>
#include <stdlib.h>

bool parse_int_range(int32_t *dst, const char *src, int32_t low, int32_t high);
bool read_int_range(int32_t *out, int32_t low, int32_t high);
void print_board();