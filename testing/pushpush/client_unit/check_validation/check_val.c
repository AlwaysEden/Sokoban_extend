#include <stdio.h>
#include <stdlib.h>

#define NAME_SIZE 16
enum entity {
        EMPTY = 0,
        BLOCK = -1,
        ITEM = -9, //item will be -10 ~ -110
        USER = 1, //user wil be 1 ~ 3
        BASE = 9, //base will be 10 ~ 30
};

enum spans {
        UP,
        DOWN,
        LEFT,
        RIGHT
};
typedef struct location{
    int x;
    int y;
} location_t;

typedef struct user{
    char name[NAME_SIZE];
    int score;
    location_t base_loc;
    location_t user_loc;
}user_t;

typedef struct object_data{
    int map_width;
        int map_height;
    int timeout;
    int max_user;
    struct user * users;
    location_t * item_locations;
    location_t * block_locations;
}object_data_t;

object_data_t Model;

int map[5][5] = { {0, 0, -1, 0, 0},
    		  {0, 0, -10, 0, 0},
		  {-1, -12, 0, -11, -1},
		  {0, 0, -13, 0, 0},
		  {0, 0, -1, 0, 0} }; //임의로 map 설정

int check_validation(int cmd){
        int user_idx = cmd/4;
        int span = cmd%4;
	Model.users = malloc(sizeof(struct user)); //임의로 할당
	Model.map_width = Model.map_height = 5;
        int curr_x, curr_y, target_x, target_y, item_target_x, item_target_y;
        curr_x = target_x = item_target_x = Model.users[user_idx].user_loc.x = 2;
        curr_y = target_y = item_target_y = Model.users[user_idx].user_loc.y = 2;
        switch(span){
                case UP:
                        if((target_y = (curr_y - 1)) < 0) return 0;//out of array
                        else if(map[target_y][target_x] == EMPTY) return 1; //empty
                        else if(map[target_y][target_x] > BASE) return 1; //base
                        else if(map[target_y][target_x] < ITEM){
                                if((item_target_y = (target_y - 1)) < 0) return 0; //item and non-movabel
                                if(map[item_target_y][item_target_x] == EMPTY) return map[target_y][target_x]; //item and movable
                                if((map[item_target_y][item_target_x] > BASE) && ((map[item_target_y][item_target_x]) == ((user_idx + 1) * 10))) return (0 - map[target_y][target_x]); //이 경우에는 &&때문에 최대 브랜치 달성은 하지 못함.
                                if(map[item_target_y][item_target_x] > BASE) return map[target_y][target_x]; //item and movable as other's base
                                else return 0;  //others (block, user, base)
                        }else return 0;
                        break;

                case DOWN:
                        if((target_y = (curr_y + 1)) > Model.map_height -1 ) return 0;//out of array
                        else if(map[target_y][target_x] == EMPTY) return 1; //empty
                        else if(map[target_y][target_x] > BASE) return 1; //base
                        else if(map[target_y][target_x] < ITEM){
                                if((item_target_y = (target_y + 1)) > Model.map_height - 1) return 0; //item and non-movabel
                                if(map[item_target_y][item_target_x] == EMPTY) return map[target_y][target_x]; //item and movable
                                if((map[item_target_y][item_target_x] > BASE) && ((map[item_target_y][item_target_x]) == ((user_idx + 1) * 10))) return (0 - map[target_y][target_x]);
                                if(map[item_target_y][item_target_x] > BASE) return map[target_y][target_x]; //item and movable as other's base
                                else return 0;  //others (block, user, base)
                        }else return 0;
                        break;


                case LEFT:
                        if((target_x = (curr_x - 1)) < 0) return 0;//out of array
                        else if(map[target_y][target_x] == EMPTY) return 1; //empty
                        else if(map[target_y][target_x] > BASE) return 1; //base
                        else if(map[target_y][target_x] < ITEM){
                                if((item_target_x = (target_x - 1)) < 0) return 0; //item and non-movabel
                                if(map[item_target_y][item_target_x] == EMPTY) return map[target_y][target_x]; //item and movable
                                if((map[item_target_y][item_target_x] > BASE) && ((map[item_target_y][item_target_x]) == ((user_idx + 1)  * 10))) return (0 - map[target_y][target_x]);
                                if(map[item_target_y][item_target_x] > BASE) return map[target_y][target_x]; //item and movable as other's base

                                else return 0;  //others (block, user, base)
                        }else return 0;
                        break;

                case RIGHT:
                        if((target_x = (curr_x + 1)) > Model.map_width  - 1) return 0;//out of array
                        else if(map[target_y][target_x] == EMPTY) return 1; //empty
                        else if(map[target_y][target_x] > BASE) return 1; //base
                        else if(map[target_y][target_x] < ITEM){
                                if((item_target_x = (target_x + 1)) > Model.map_width -1) return 0; //item and non-movabel
                                if(map[item_target_y][item_target_x] == EMPTY) return map[target_y][target_x]; //item and movable
                                if((map[item_target_y][item_target_x] > BASE) && ((map[item_target_y][item_target_x]) == ((user_idx + 1) * 10))) return (0 - map[target_y][target_x]);
                                if(map[item_target_y][item_target_x] > BASE) return map[target_y][target_x]; //item and movable as other's base
                                else return 0;  //others (block, user, base)
                        }else return 0;
                        break;
        }
        return 0;
}

int main(){
	int input[] = {0, 1, 2, 3};
	for(int i = 0; i < 4; i++){
		check_validation(input[i]);
	}
}
