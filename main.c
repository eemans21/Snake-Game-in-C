#include "snek_api.c"
#include <unistd.h>
#include "search_func.h"

int turn_around;

void play_game() {
//	FILE *final_score = fopen("scores.txt", "w");
//	FILE *final_length = fopen("length.txt", "w");

//	for (int i = 1; i<=100; i++){
//		printf("TRIAL %d", i);
		GameBoard* board = init_board();
		show_board(board);

		int axis = AXIS_INIT;
		int direction = DIR_INIT;
	
		int play_on = 1;
		int coord[2];

		struct direct* list = intialize_linked();

		while (play_on){
			coord[x] = board->snek->head->coord[x];
			coord[y] = board->snek->head->coord[y];
		

			int moogle_value = check_moogle_value(board ->cell_value);
			int moogle_y = check_moogle_y(board -> cell_value);
			int moogle_x = check_moogle_x(board -> cell_value);
			int target[2] = {moogle_y, moogle_x}; 

			unsigned short go_x = (axis == AXIS_Y && direction == DOWN && coord[y] == (BOARD_SIZE - 1)) || (axis == AXIS_Y && direction == UP && coord[y] == 0);
			unsigned short go_y = (axis == AXIS_X && direction == RIGHT && coord[x] == (BOARD_SIZE - 1)) || (axis == AXIS_X && direction == LEFT && coord[x] == 0);

			int last_dequeue = 0;
			int move_around = 0;
			int already_found = 0;

			if (sizelist(list) == 0)calculate_route(board -> snek, target, axis, direction, moogle_value, list, board->occupancy, go_x, go_y);
	
				if (sizelist(list) == 0){
					move_around = go_around(board -> snek, target, axis, direction, moogle_value, list, board->occupancy, go_x, go_y);
					already_found = 1; 
				}

				if (sizelist(list) == 1 && move_around!= 1){
					turn_around = real_turn_around(board -> snek, target, axis, direction, moogle_value, list, board->occupancy, go_x, go_y);
					move_around = go_around(board -> snek, target, axis, direction, moogle_value, list, board->occupancy, go_x, go_y);
					if (turn_around == 0 && move_around == 0) move_around = go_around(board -> snek, target, list -> next -> axis, list -> next -> direction, moogle_value, list, board->occupancy, go_x, go_y);
				}

				if (sizelist(list) == 2 && turn_around !=1 && move_around !=1){
					turn_around = real_turn_around(board -> snek, target, axis , direction, moogle_value, list, board->occupancy, go_x, go_y);
					move_around = go_around(board -> snek, target, axis, direction, moogle_value, list, board->occupancy, go_x, go_y);
					if (turn_around == 0 && move_around == 0){
						if(target[x] == coord[x] || target[y] == coord[y]){ 
							move_around = go_around(board -> snek, target, list -> next -> axis, list -> next -> direction, moogle_value, list, board->occupancy, go_x, go_y);
						} else {
						move_around = go_around(board -> snek, target, list -> next -> next -> axis, list -> next -> next -> direction, moogle_value, list, board->occupancy, go_x, go_y);	
						}
					}
				}	

			
 				if (sizelist(list) >= 3){
 					if (move_around == 1 || sizelist(list) == 4){
 						free_direct(list);
 						free_direct(list);
 					}
 		
	 				if (turn_around == 1) free_direct(list);
 				}

				if (sizelist(list) == 2){
					if((target[x] == coord[x] || target[y] == coord[y]) && turn_around == 0 && move_around == 0){
						free_direct(list);
					}	

					if((target[x] == coord[x] || target[y] == coord[y]) && turn_around == 1){
						axis = dequeue_axis(list);
						direction = dequeue_d(list);
						free_direct(list);
					}

					if(move_around == 1){
						free_direct(list);
					}
			
					if (turn_around == 0 && move_around == 0){
						axis = dequeue_axis(list);
						direction = dequeue_d(list);
					}
				}
		
				if (sizelist(list) == 1){
					if (turn_around == 1){
						turn_around++;
					}
		
					else{
					axis = dequeue_axis(list);
					direction = dequeue_d(list);
					free_direct(list);
					last_dequeue = 1;
					turn_around = 0;
					}
				}

				if (go_x && sizelist(list) == 0 && last_dequeue == 0) {
					axis = AXIS_X;
					if (coord[x] < (int)(BOARD_SIZE / 2)){ 
						direction = RIGHT;
					} else {
						direction = LEFT;
					}
				} else if (go_y && sizelist(list) == 0 && last_dequeue == 0) {
					axis = 	AXIS_Y;
					if (coord[y] < (int)(BOARD_SIZE / 2)){ 
						direction = DOWN;
					} else {
						direction = UP;
					}
				}
	
			show_board(board);
			play_on = advance_frame(axis, direction, board);
			printf("Going ");

			if (axis == AXIS_X){
				if (direction == RIGHT){
					printf("RIGHT");
				} else {
					printf("LEFT");
				}
			} else {
				if (direction == UP){
					printf("UP");
				} else {
					printf("DOWN");
				}
			} 
			printf("\n");
			usleep(155550);
		}	
//		fprintf(final_score, "%d\n", SCORE);
//		fprintf(final_length, "%d\n", board->snek->length);
		end_game(&board);
//	}
//	fclose(final_score);
//	fclose(final_length);
	free(list);	
}


int main(){
	play_game();
	return 0;
}
