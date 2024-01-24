#include <stdio.h>
#include <stdlib.h>
#include "../../../../cJSON.h"
#include <string.h>
#include <sys/stat.h>


#define NAME_SIZE 16

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

int num_item;
int current_num_item;
int num_block;

int parseJson(char * jsonfile) {

    	cJSON* root;
        root = cJSON_Parse(jsonfile);
        if (root == NULL /*|| root->next == NULL*/) {
                printf("JSON parsing error: %s\n", cJSON_GetErrorPtr());
                return 1;
        }

        cJSON* timeout = cJSON_GetObjectItem(root, "timeout");
        Model.timeout = timeout->valueint;
        cJSON* max_user = cJSON_GetObjectItem(root, "max_user");
        Model.max_user = max_user->valueint;

        cJSON* map = cJSON_GetObjectItem(root, "map");
        cJSON* map_width = cJSON_GetObjectItem(map, "map_width");
        Model.map_width = map_width->valueint;
        cJSON* map_height = cJSON_GetObjectItem(map, "map_height");
        Model.map_height = map_height->valueint;

        cJSON* user = cJSON_GetObjectItem(root, "user");
        Model.users = (struct user *)malloc(sizeof(struct user) * Model.max_user);
        for(int i = 0; i < Model.max_user; i++){
                memset(Model.users[i].name, 0, sizeof(NAME_SIZE));
                Model.users[i].score = 0;
                cJSON* user_array = cJSON_GetArrayItem(user,i);
            cJSON* base = cJSON_GetObjectItem(user_array,"base");
                cJSON* base_x = cJSON_GetArrayItem(base, 0);
                cJSON* base_y = cJSON_GetArrayItem(base, 1);
                cJSON* user_location = cJSON_GetObjectItem(user_array,"location");
                cJSON* user_x = cJSON_GetArrayItem(user_location, 0);
                cJSON* user_y = cJSON_GetArrayItem(user_location, 1);
                Model.users[i].user_loc.x = user_x->valueint;
                Model.users[i].user_loc.y = user_y->valueint;
                Model.users[i].base_loc.x = base_x->valueint;
                Model.users[i].base_loc.y = base_y->valueint;
        #ifdef DEBUG
                printf("name: %s\n",Model.users[i].name);
                printf("base x: %d\n",Model.users[i].base_loc.x);
                printf("base y: %d\n",Model.users[i].base_loc.y);
        #endif
        }

        cJSON * item = cJSON_GetObjectItem(root, "item_location");
        num_item = cJSON_GetArraySize(item);
        current_num_item = num_item;
        Model.item_locations = (struct location *)malloc(sizeof(struct location) * num_item);
        for(int i = 0; i < num_item; i++){
                cJSON* item_array = cJSON_GetArrayItem(item,i);
                cJSON* item_x = cJSON_GetArrayItem(item_array, 0);
                cJSON* item_y = cJSON_GetArrayItem(item_array, 1);
                Model.item_locations[i].x = item_x->valueint;
                Model.item_locations[i].y = item_y->valueint;
        #ifdef DEBUG
                printf("item x: %d\n",Model.item_locations[i].x);
                printf("item y: %d\n",Model.item_locations[i].y);
                #endif
        }

        cJSON * block = cJSON_GetObjectItem(root, "block_location");
        num_block = cJSON_GetArraySize(block);
        Model.block_locations = (struct location *)malloc(sizeof(struct location) * num_block);
        for(int i = 0; i < num_block; i++){
                cJSON* block_array = cJSON_GetArrayItem(block,i);
                cJSON* block_x = cJSON_GetArrayItem(block_array, 0);
                cJSON* block_y = cJSON_GetArrayItem(block_array, 1);
                Model.block_locations[i].x = block_x->valueint;
                Model.block_locations[i].y = block_y->valueint;
        #ifdef DEBUG
                printf("block x: %d\n",Model.block_locations[i].x);
                printf("block y: %d\n",Model.block_locations[i].y);
        #endif
        }

        return 0;
}


int main(int argc, char *argv[]){
	char filepath[256];
	strcpy(filepath, argv[1]);
	FILE *file = fopen(filepath,"r");
        if(file == NULL)
        {
                fprintf(stderr,"ERROR: open file");
                return 1;
        }
        struct stat st;
        if(stat(filepath, &st) == -1)
        {
                fprintf(stderr,"ERROR: stat()\n");
                return 1;
        }
        int size = st.st_size;

        char* jsonfile = (char*)malloc(size+1);
        if(jsonfile     == NULL)
        {
                fprintf(stderr,"ERROR: memory allocation\n");
                return 1;
        }

        int read_size = fread(jsonfile, 1, size, file);
        if(read_size != size)
        {
                fprintf(stderr, "ERROR: read file\n");
                return 1;
        }

        fclose(file);
        jsonfile[size] = '\0';

	if(parseJson(jsonfile)){
		fprintf(stderr, "ERROR: parseJson()");
	}
	free(jsonfile);
}
