#include <stdio.h>
/*
		Author: Samed Kahyaoglu
		Github: urtuba
		  Date: 20 April 2018
*/

//the function which calculates the shortest distance to nearest car.

int shortest_distance(int pos_x, int pos_y, int actual_size, int parking_area[][50])
{
	int distance = 100, manhattan = 0, x = 0, y = 0;
	int x_difference = 0, y_difference = 0;

	for(x = 0; x < actual_size; x++){
		for(y = 0; y < actual_size; y++){

			if(pos_x > x){
				x_difference = pos_x - x;
			}else{
				x_difference = x - pos_x;
			}

			if(pos_y > y){
				y_difference = pos_y - y;
			}else{
				y_difference = y - pos_y;
			}

			manhattan = x_difference + y_difference;

			if(parking_area[x][y] == 1 && distance > manhattan){distance = manhattan;}
		}
	}
	return distance;
}


int main()
{

//creation of the matrix with 0's

	int a = 0, b = 0; //for general counters or temporary variables
	const int MAXSIZE = 50;
	int parking_area[MAXSIZE][MAXSIZE];

	for(a = 0; a < MAXSIZE; a++){
		for(b = 0; b < MAXSIZE; b++){
			parking_area[a][b] = 0;
		}
	}

//arranging the matrix with size and cars.

	int actual_size = 0;
	int cars = 0;
	printf("Size: ");
	scanf("%d", &actual_size);

	while(actual_size > 50){
		printf("max size must be 50\n");
		printf("Size: ");
		scanf("%d", &actual_size);
	}

	printf("Cars: ");
	scanf("%d", &cars);

	if(cars >= actual_size*actual_size){
		printf("No slot found\n");
		return 0;
	}else{
		int i = 0;
		while(i < cars){

			printf("Locations: ");
			scanf("%d %d", &a, &b);
			a = a - 1;
			b = b - 1;
			parking_area[a][b]=1;
			i++;
		}
	}

//recording distance scores as a matrix.

	int availability_map[MAXSIZE][MAXSIZE];
	for(a = 0; a < actual_size; a++){
		for(b = 0; b < actual_size; b++){

			availability_map[a][b] = shortest_distance(a, b, actual_size, parking_area);
		}
	}

//choosing best position.

	int best_position_x = 0, best_position_y = 0, temp = 0;
	for(a = 0; a < actual_size; a++){
		for(b = 0; b < actual_size; b++){
			if(availability_map[a][b] > temp){

				best_position_x = a;
				best_position_y = b;
				temp = availability_map[a][b];
			}
		}
	}

	printf("Best Slot Found In: %d %d\r\n", best_position_x + 1, best_position_y + 1);
	return 0;
}
