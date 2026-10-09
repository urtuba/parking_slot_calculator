CC ?= cc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror -O2

all: parking_slot_calculator

parking_slot_calculator: parking_slot_calculator.c
	$(CC) $(CFLAGS) -o $@ parking_slot_calculator.c

test: parking_slot_calculator
	sh tests/run.sh ./parking_slot_calculator

clean:
	rm -f parking_slot_calculator

.PHONY: all test clean
