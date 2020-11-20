struct direct{
	int axis;
	int direction;
	struct direct *next;
};

int sizelist(struct direct* linked){
	struct direct* temp = linked;
	int counter = 0;

	while (temp->next){
	temp = temp->next;
	counter++;
	}
	return counter;
}

int sizelist2(struct SnekBlock* linked){
	struct SnekBlock* temp = linked;
	int counter = 0;

	while (temp->next){
	temp = temp->next;
	counter++;
	}
	return counter;
}

struct direct* intialize_linked(){
	struct direct *linked = malloc(sizeof(struct direct));

	linked -> next = NULL;
	return linked;
}

struct direct* new_direction(struct direct* linked,int direction, int axis){
	struct direct* new = malloc(sizeof(struct direct));
	if (new){
		new -> axis = axis;
		new -> direction = direction;
	}
	return new;
	free(new);
}

void insert_direction(struct direct* linked, int direction, int axis){

	struct direct*new = new_direction(linked, direction, axis);
	new -> next = linked -> next;
	linked -> next = new;
	
	if (axis == AXIS_Y && direction == DOWN){
		new->direction!=UP;
	}	
	if (axis == AXIS_Y && direction == UP){
		new->direction!=DOWN;
	}	
	if (axis == AXIS_X && direction == RIGHT){
		new->direction!=LEFT;
	}	
	if (axis == AXIS_X && direction == LEFT){
		new->direction!=RIGHT;
	}	

}

int dequeue_d(struct direct* link){
	struct direct* temp = link;
	while (temp->next){
		temp = temp->next;
	}
	int d = temp->direction;
	return d;
}
int dequeue_axis(struct direct* link){
	struct direct* temp;
	temp = link;
	while (temp->next){
		temp = temp->next;
	}
	int axis = temp->axis;

	return axis;
}

void free_direct(struct direct*link){
	struct direct* temp;
	struct direct* prev;

	temp = link;
	while (temp->next){
		prev=temp;
		temp = temp->next;}

	prev->next = NULL;
	free(temp);

}



int check_moogle_x(int cellvalue[BOARD_SIZE][BOARD_SIZE]){
	int x_coord = BOARD_SIZE;
	int y_coord = BOARD_SIZE;
	int coordinates[2];
	for(x_coord=0; x_coord<BOARD_SIZE; x_coord++){
		for(y_coord=0; y_coord<BOARD_SIZE; y_coord++){
			if(cellvalue[x_coord][y_coord] == 20 || cellvalue[x_coord][y_coord] == 60){
				return x_coord;
			break;
			}
		}
		if(cellvalue[x_coord][y_coord] == 20 || cellvalue[x_coord][y_coord] == 60){
			break;}
	}
	return x_coord;
}

int check_moogle_y(int cellvalue[BOARD_SIZE][BOARD_SIZE]){
	int x_coord = BOARD_SIZE;
	int y_coord = BOARD_SIZE;
	int coordinates[2];
	for(x_coord=0; x_coord<BOARD_SIZE; x_coord++){
		for(y_coord=0; y_coord<BOARD_SIZE; y_coord++){
			if(cellvalue[x_coord][y_coord] == 20 || cellvalue[x_coord][y_coord] == 60){
				return y_coord;
			break;
			}
		}
		if(cellvalue[x_coord][y_coord] == 20 || cellvalue[x_coord][y_coord] == 60){
			break;}
	}
	return y_coord;
}

int check_moogle_value(int cellvalue[BOARD_SIZE][BOARD_SIZE]){
	int x_coord = 0;
	int y_coord = 0;
	int coordinates[2];
	int value = 0;
	for(x_coord=0; x_coord<BOARD_SIZE; x_coord++){
		for(y_coord=0; y_coord<BOARD_SIZE; y_coord++){
			if((cellvalue[x_coord][y_coord] == 20) || (cellvalue[x_coord][y_coord] == 60)){
				value = cellvalue[x_coord][y_coord];
			break;
			}
		}
		if((cellvalue[x_coord][y_coord] == 20) || (cellvalue[x_coord][y_coord] == 60)){
			break;}
	}
	return value;
}

int search_snek(int coord[2], int occupancy[BOARD_SIZE][BOARD_SIZE]){
	int x_coord = 0;
	int y_coord = 0;
	int value = 0;
	for(x_coord=0; x_coord<BOARD_SIZE; x_coord++){
		for(y_coord=0; y_coord<BOARD_SIZE; y_coord++){
			if(occupancy[x_coord][y_coord]>0){
				value = 1;
			break;
			}
		}
		if(occupancy[x_coord][y_coord]>0){
			break;}
	}
	return value;
}

int which_way_x(struct Snek* snek,int occupancy[BOARD_SIZE][BOARD_SIZE], int direction){
	struct SnekBlock* temp = snek->head->next;
	int value = 1;
	int same_x = -1;
	while (temp->next != NULL){
		if (temp->coord[y] == snek->head->coord[y]){
			same_x = temp->coord[x]; 
			break;
		}
		temp = temp->next;
	}

	if (same_x > snek->head->coord[x]){
		value = LEFT;
	}

	if (same_x < snek->head->coord[x]){
		value = RIGHT;
	}

	if (direction == UP && snek->head->coord[x] == 0)value = RIGHT;
	if (direction == UP && snek->head->coord[x] == BOARD_SIZE-1)value = LEFT;
	if (direction == DOWN && snek->head->coord[x] == 0)value = RIGHT;
	if (direction == DOWN && snek->head->coord[x] == BOARD_SIZE-1)value = LEFT;

	return value;
}


int which_way_y(struct Snek* snek,int occupancy[BOARD_SIZE][BOARD_SIZE], int direction){
	struct SnekBlock* temp = snek->head->next;
	int value = 1;
	int same_x = 1;
	while (temp->next != NULL){
		if (temp->coord[x] == snek->head->coord[x]){
			same_x = temp->coord[y]; 
			break;
		}
		temp = temp->next;
	}

	if (same_x > snek->head->coord[y]){
		value = UP;
	}

	if (same_x < snek->head->coord[y]){
		value = DOWN;
	}

	if (direction == RIGHT && snek->head->coord[y] == BOARD_SIZE-1)value = UP;
	if (direction == RIGHT && snek->head->coord[y] == 0)value = DOWN;
	if (direction == LEFT && snek->head->coord[y] == BOARD_SIZE-1)value = UP;
	if (direction == LEFT && snek->head->coord[y] == 0)value = DOWN;

	return value;
}

int go_around(struct Snek* snek, int target[2], int axis, int direction, int check_moogle_value, struct direct* linked, int occupancy[BOARD_SIZE][BOARD_SIZE], int go_x, int go_y){

	int move_around = 0;
	int value_x;
	int value_y;

	if (direction == UP && axis == AXIS_Y && ((((occupancy[snek->head->coord[y]-1][(snek->head->coord[x])]) == 1)) || snek->head->coord[y] == 0) && go_x == 0 && snek->head->coord[y]-1 > -1){
		value_x = which_way_x(snek, occupancy, direction);
		insert_direction(linked, value_x, AXIS_X);
		move_around = 1;
	}

	if (direction == DOWN && axis == AXIS_Y && ((((occupancy[snek->head->coord[y]+1][(snek->head->coord[x])]) == 1)) || snek->head->coord[y] == BOARD_SIZE-1) && go_x == 0 && snek->head->coord[y]+1 < BOARD_SIZE){
		value_x = which_way_x(snek, occupancy, direction);
		insert_direction(linked, value_x, AXIS_X);
		move_around = 1;
	}

	if (direction == RIGHT && axis == AXIS_X && ((((occupancy[(snek->head->coord[y])][snek->head->coord[x]+1]) == 1)) || snek->head->coord[x] == BOARD_SIZE-1) && go_y == 0 && snek->head->coord[x]+1 < BOARD_SIZE){
		value_y = which_way_y(snek, occupancy, direction);
		insert_direction(linked, value_y, AXIS_Y);
		move_around = 1;
	}

	if (direction == LEFT && axis == AXIS_X && ((((occupancy[(snek->head->coord[y])][snek->head->coord[x]-1]) == 1)) || snek->head->coord[x] == 0) && go_y == 0 && snek->head->coord[x]-1 > -1){
		value_y = which_way_y(snek, occupancy, direction);
		insert_direction(linked, value_y, AXIS_Y);
		move_around = 1;
	}

	return move_around;
}

int real_turn_around(struct Snek* snek, int target[2], int axis, int direction, int check_moogle_value, struct direct* linked, int occupancy[BOARD_SIZE][BOARD_SIZE], int go_x, int go_y){	
	int turn_around = 0;

	if (check_moogle_value > 0){
		if (direction == UP && axis == AXIS_Y &&  target[y] > snek->head->coord[y] && target[x] == snek->head->coord[x]){
			int value_x = which_way_x(snek, occupancy, direction);
			insert_direction(linked, value_x, AXIS_X);
			insert_direction(linked, DOWN, AXIS_Y);
			turn_around = 1;
		}

		if (direction == DOWN && axis == AXIS_Y && target[y] < snek-> head->coord[y] && target[x] == snek->head->coord[x]){
			int value_x = which_way_x(snek, occupancy, direction);
			insert_direction(linked, value_x, AXIS_X);
			insert_direction(linked, UP, AXIS_Y);
			turn_around = 1;
		}

		if (direction == RIGHT && axis == AXIS_X && target[x] < snek->head->coord[x] && target[y] == snek->head->coord[y]){
			int value_y = which_way_y(snek, occupancy, direction);	
			insert_direction(linked, value_y, AXIS_Y);
			insert_direction(linked, LEFT, AXIS_X);
			turn_around = 1;
		}

		if (direction == LEFT && axis == AXIS_X && target[x] > snek->head->coord[x] && target[y] == snek->head->coord[y]){
			int value_y = which_way_y(snek, occupancy, direction);
			insert_direction(linked, value_y, AXIS_Y);
			insert_direction(linked, RIGHT, AXIS_X);
			turn_around = 1;
		}
	}
	return turn_around;
}

void calculate_route(struct Snek* snek, int target[2], int axis, int direction, int check_moogle_value, struct direct* linked, int occupancy[BOARD_SIZE][BOARD_SIZE], int go_x, int go_y){

	int bruh = 0; 

	if (check_moogle_value>1 && sizelist(linked) == 0){
		if (!(target[x] == snek->head->coord[x] || target[y] == snek->head->coord[y])){

			if (snek->head->coord[x] < target[x] && axis == 1){
				insert_direction(linked, RIGHT, AXIS_X);
			}

			if (snek->head->coord[x] > target[x] && axis == 1){
				insert_direction(linked, LEFT, AXIS_X);
			}

			if (snek->head->coord[y] < target[y] && axis == -1){
				insert_direction(linked, DOWN, AXIS_Y);
			}

			if (snek->head->coord[y] > target[y] && axis == -1){
				insert_direction(linked, UP, AXIS_Y);
			}


			if (axis == -1){

				if (snek->head->coord[x] < target[x]){
					insert_direction(linked, RIGHT, AXIS_X);
					bruh = 1;
				}

				if (snek->head->coord[x] > target[x]){
					insert_direction(linked, LEFT, AXIS_X);
					bruh = 1;
				}
			}

			if (axis == 1){

				if (snek->head->coord[y] < target[y]){
						insert_direction(linked, DOWN, AXIS_Y);
						bruh = 1;
				}

				if (snek->head->coord[y] > target[y]){
					insert_direction(linked, UP, AXIS_Y);
					bruh = 1;
				}
			}
		} else {
			if (snek->head->coord[x] < target[x]){
				insert_direction(linked, RIGHT, AXIS_X);
				bruh = 1;
			}

			if (snek->head->coord[x] > target[x]){
				insert_direction(linked, LEFT, AXIS_X);
				bruh = 1;
			}

			if (snek->head->coord[y] < target[y]){
				insert_direction(linked, DOWN, AXIS_Y);
				bruh = 1;
			}

			if (snek->head->coord[y] > target[y]){
				insert_direction(linked, UP, AXIS_Y);
				bruh = 1;
			}	
		}
	}	
}
