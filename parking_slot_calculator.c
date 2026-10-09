/*
 * Author: Samed Kahyaoglu
 * Github: urtuba
 *   Date: 20 April 2018
 * Restored: 2026
 *
 * Finds the parking slot that is furthest from the nearest parked car.
 */

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50
#define LINE_SIZE 64

/* Manhattan distance from slot (row, col) to the nearest parked car. */
static int distance_to_nearest_car(int row, int col, int size,
                                   int lot[][MAX_SIZE])
{
    int nearest = INT_MAX;

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            int dx = row > x ? row - x : x - row;
            int dy = col > y ? col - y : y - col;
            int distance = dx + dy;

            if (lot[x][y] == 1 && distance < nearest) {
                nearest = distance;
            }
        }
    }
    return nearest;
}

/*
 * Finds the slot with the largest distance to the nearest car.
 * The first such slot in row-major order wins ties.
 */
static void find_best_slot(int size, int lot[][MAX_SIZE],
                           int *best_row, int *best_col)
{
    int best_distance = 0;

    *best_row = 0;
    *best_col = 0;
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            int distance = distance_to_nearest_car(x, y, size, lot);

            if (distance > best_distance) {
                *best_row = x;
                *best_col = y;
                best_distance = distance;
            }
        }
    }
}

static void fail_on_end_of_input(void)
{
    fprintf(stderr, "error: unexpected end of input\n");
    exit(1);
}

/*
 * Parses exactly `count` whole numbers separated by white space.
 * Returns 1 on success, 0 for anything else (text, too few or too many).
 */
static int parse_numbers(const char *text, int count, long values[])
{
    for (int i = 0; i < count; i++) {
        char *end;

        errno = 0;
        values[i] = strtol(text, &end, 10);
        if (end == text || errno == ERANGE) {
            return 0;
        }
        if (*end != '\0' && !isspace((unsigned char)*end)) {
            return 0;
        }
        text = end;
    }
    while (isspace((unsigned char)*text)) {
        text++;
    }
    return *text == '\0';
}

/*
 * Prints the prompt and reads one line. Returns 1 if the line holds exactly
 * `count` whole numbers, 0 if not. Ends the program at end of input.
 */
static int read_numbers(const char *prompt, int count, long values[])
{
    char line[LINE_SIZE];
    int too_long = 0;

    printf("%s", prompt);
    if (fgets(line, sizeof line, stdin) == NULL) {
        fail_on_end_of_input();
    }
    if (strchr(line, '\n') == NULL && strlen(line) == sizeof line - 1) {
        /* The line does not fit: drop the rest of it. */
        int c;

        too_long = 1;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    return !too_long && parse_numbers(line, count, values);
}

static int read_size(void)
{
    long value;

    for (;;) {
        if (read_numbers("Size: ", 1, &value) && value >= 1
            && value <= MAX_SIZE) {
            return (int)value;
        }
        fprintf(stderr, "error: size must be one whole number from 1 to %d\n",
                MAX_SIZE);
    }
}

static int read_car_count(int size)
{
    long value;

    for (;;) {
        if (read_numbers("Cars: ", 1, &value) && value >= 0
            && value <= (long)size * size) {
            return (int)value;
        }
        fprintf(stderr, "error: cars must be one whole number from 0 to %d\n",
                size * size);
    }
}

/* Reads one free slot (1-based X Y) and marks it in the lot. */
static void read_car(int size, int lot[][MAX_SIZE])
{
    long xy[2];

    for (;;) {
        if (!read_numbers("Locations: ", 2, xy) || xy[0] < 1 || xy[0] > size
            || xy[1] < 1 || xy[1] > size) {
            fprintf(stderr,
                    "error: location must be two whole numbers X Y, "
                    "each from 1 to %d\n",
                    size);
        } else if (lot[xy[0] - 1][xy[1] - 1] == 1) {
            fprintf(stderr, "error: slot %ld %ld already has a car\n",
                    xy[0], xy[1]);
        } else {
            lot[xy[0] - 1][xy[1] - 1] = 1;
            return;
        }
    }
}

int main(void)
{
    int lot[MAX_SIZE][MAX_SIZE] = {{0}};
    int size = read_size();
    int cars = read_car_count(size);
    int best_row, best_col;

    if (cars == size * size) {
        printf("No slot found\n");
        return 0;
    }

    for (int i = 0; i < cars; i++) {
        read_car(size, lot);
    }
    find_best_slot(size, lot, &best_row, &best_col);
    printf("Best Slot Found In: %d %d\r\n", best_row + 1, best_col + 1);
    return 0;
}
