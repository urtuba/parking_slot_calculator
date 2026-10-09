/*
 * Author: Samed Kahyaoglu
 * Github: urtuba
 *   Date: 20 April 2018
 * Restored: 2026
 *
 * Finds the parking slot that is furthest from the nearest parked car.
 */

#include <limits.h>
#include <stdio.h>

#define MAX_SIZE 50

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

/* Reads the lot size, asking again while it is above MAX_SIZE. */
static int read_size(void)
{
    int size = 0;

    printf("Size: ");
    scanf("%d", &size);
    while (size > MAX_SIZE) {
        printf("max size must be %d\n", MAX_SIZE);
        printf("Size: ");
        scanf("%d", &size);
    }
    return size;
}

/* Reads the car locations (1-based) and marks them in the lot. */
static void read_cars(int cars, int lot[][MAX_SIZE])
{
    for (int i = 0; i < cars; i++) {
        int x = 0, y = 0;

        printf("Locations: ");
        scanf("%d %d", &x, &y);
        lot[x - 1][y - 1] = 1;
    }
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

int main(void)
{
    int lot[MAX_SIZE][MAX_SIZE] = {{0}};
    int cars = 0;
    int size = read_size();
    int best_row, best_col;

    printf("Cars: ");
    scanf("%d", &cars);

    if (cars >= size * size) {
        printf("No slot found\n");
        return 0;
    }

    read_cars(cars, lot);
    find_best_slot(size, lot, &best_row, &best_col);
    printf("Best Slot Found In: %d %d\r\n", best_row + 1, best_col + 1);
    return 0;
}
