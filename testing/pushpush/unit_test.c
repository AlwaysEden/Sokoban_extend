#include <stdio.h>
#include "include/client.h"
#include "include/cJSON.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>


extern int ** map; // cell
extern object_data_t Model; //model

//connection()
#ifdef CONNECT
int main(int argc, char *argv[]){
	if(connection(argv) == 0){
		fprintf(stderr, "Pass");
		exit(0);
	}else{
		fprintf(stderr, "Fail");
		exit(1);
	}
}
#endif

//start_game()
#ifdef START_GAME
int main(int argc, char *argv[]){
	int fd = open("start_game.txt", O_WRONLY | O_CREAT, 0664);
	char buf = fgetc(stdin);	
	int game_started = atoi(&buf);

	send_bytes(fd, (void*)&game_started, sizeof(int));
	close(fd);
	
	int fd2 = open("start_game.txt", O_RDONLY | O_CREAT, 0664);
	if(start_game(fd2) == 0){
		fprintf(stderr, "Pass");
		exit(0);
	}else{
		fprintf(stderr, "Fail");
		exit(1);
	}
	close(fd2);
	remove("start_game.txt");
}
#endif

//recv_byte(), send_byte()
#ifdef RW
int main(int argc, char *argv[]){
	char testpath[256];
	strcpy(testpath, argv[1]);

	struct stat sb;
	if(stat(testpath, &sb) == -1){
		fprintf(stderr,"ERROR: stat\n");
		exit(1);
	}

	int file_size = sb.st_size;
	
	char *buf;
	buf = (char *)malloc(sizeof(char) * file_size);
	if(buf == NULL){
		fprintf(stderr, "ERROR: malloc\n");
		exit(1);
	}
	int fd;
	fd = open(testpath, O_RDONLY);
	read(fd, buf, file_size);
	close(fd);

	fd = open("rw.txt", O_WRONLY | O_CREAT, 0664);
	send_bytes(fd, buf, file_size);
	
	free(buf);
	
	fd = open("rw.txt", O_RDONLY);
	char *recv_data;
	recv_data = (char *)malloc(sizeof(char)*file_size);
	recv_bytes(fd, recv_data, file_size);

	for(int i = 0; i < file_size; i++){
		printf("%c",recv_data[i]);
	}
	remove("rw.txt");
}
#endif

//parseJson()
#ifdef PARSEJSON
int main(int argc, char *argv[]){
	char jsonpath[256];
	strcpy(jsonpath, argv[1]);

	struct stat sb;
	if(stat(jsonpath, &sb) == -1){
		fprintf(stderr,"ERROR: stat\n");
		exit(1);
	}

	int file_size = sb.st_size;
	
	char *buf;
	buf = (char *)malloc(sizeof(char) * file_size);
	if(buf == NULL){
		fprintf(stderr, "ERROR: malloc\n");
		exit(1);
	}
	int fd;
	fd = open(jsonpath, O_RDONLY);
	read(fd, buf, file_size);
	
	if(parseJson(buf)){
		fprintf(stderr, "ERROR: parseJson\n");
		free(buf);
		exit(1);
	}else{
		fprintf(stderr, "PASS\n");
	}
	free(buf);
	
	return 0;
}
#endif

//update_cell(), update_cell함수는 따로 input 값이 없다. parseJson()이 만든 Model을 참조해서 배열을 만드는 함수이다. 그러므로 parseJson()의 종속적이며 이 함수는 Fuzzing이 불가능할 것으로 예상된다.
#ifdef UPDATE_CELL 
int main(int argc, char *argv[]){
			
	char jsonpath[256];
	strcpy(jsonpath, argv[1]);

	struct stat sb;
	if(stat(jsonpath, &sb) == -1){
		fprintf(stderr,"ERROR: stat\n");
		exit(1);
	}

	int file_size = sb.st_size;
	
	char *buf;
	buf = (char *)malloc(sizeof(char) * file_size);
	if(buf == NULL){
		fprintf(stderr, "ERROR: malloc\n");
		exit(1);
	}
	int fd;
	fd = open(jsonpath, O_RDONLY);
	read(fd, buf, file_size);
	
	if(parseJson(buf)){
		fprintf(stderr, "ERROR: parseJson\n");
		free(buf);
		exit(1);
	}else{
		fprintf(stderr, "PASS\n");
	}

	map = (int **) malloc (sizeof(int *) * Model.map_width);
        for(int i=0;i<Model.map_width;i++){
                map[i] =(int *) malloc(sizeof(int) * Model.map_height);
        }

	update_cell();
	        
	for (int i = 0; i < Model.map_width; i++) {
      		for (int j = 0; j < Model.map_height; j++) {
                	fprintf(stderr,"%3d ",map[i][j]);
		}
		fprintf(stderr,"\n");
	}		
	free(buf);
	
	return 0;
}
#endif

//move()
#ifdef MOVE
int main(int argc, char *argv[]){	
	char jsonpath[] = "./testcases/move/map1.json";

	struct stat sb;
	if(stat(jsonpath, &sb) == -1){
		fprintf(stderr,"ERROR: stat\n");
		exit(1);
	}

	int file_size = sb.st_size;
	
	char *buf;
	buf = (char *)malloc(sizeof(char) * file_size);
	if(buf == NULL){
		fprintf(stderr, "ERROR: malloc\n");
		exit(1);
	}
	int fd;
	fd = open(jsonpath, O_RDONLY);
	read(fd, buf, file_size);
	
	if(parseJson(buf)){
		fprintf(stderr, "ERROR: parseJson\n");
		free(buf);
		exit(1);
	}else{
		fprintf(stderr, "PASS\n");
	}

	map = (int **) malloc (sizeof(int *) * Model.map_width);
        for(int i=0;i<Model.map_width;i++){
                map[i] =(int *) malloc(sizeof(int) * Model.map_height);
        }

	update_cell();
	
	int movement[] ={1, 60}; //For temporary verification. Move() can be verificated with check_validation().
	for(int i = 0; i < 2; i++){
		move(1,movement[i]);
	}	

	free(buf);
	
	return 0;
}
#endif


//check_validation()
#ifdef CHECK_VAL
int main(int argc, char *argv[]){	
	char jsonpath[] = "./testcases/check_val/map/map1.json"; //조작된 map for testing

	struct stat sb;
	if(stat(jsonpath, &sb) == -1){
		fprintf(stderr,"ERROR: stat\n");
		return 1;
	}

	int file_size = sb.st_size;
	
	char *buf;
	buf = (char *)malloc(sizeof(char) * file_size);
	if(buf == NULL){
		fprintf(stderr, "ERROR: malloc\n");
		exit(1);
	}
	int fd;
	fd = open(jsonpath, O_RDONLY);
	read(fd, buf, file_size);
	
	if(parseJson(buf)){
		fprintf(stderr, "ERROR: parseJson\n");
		free(buf);
		return 1;
	}else{
		fprintf(stderr, "PASS\n");
	}

	map = (int **) malloc (sizeof(int *) * Model.map_width);
        for(int i=0;i<Model.map_width;i++){
                map[i] =(int *) malloc(sizeof(int) * Model.map_height);
        }

	update_cell();
	
	char sequence_buf[256];
	read(STDIN_FILENO, sequence_buf, sizeof(sequence_buf));
	
	char *token = strtok(sequence_buf, " ");
	int seq[256];
	int tmp = 0;

	int i = 0;
	while(token != NULL){
		tmp = atoi(token);
		if( !(tmp >= 0 && tmp <= Model.max_user *4)){
			return 1;
		}
		seq[i] = tmp;
		fprintf(stderr, "%d ",seq[i]); 
		i++;
		token = strtok(NULL, " ");
	}
	fprintf(stderr,"\n");	

	int movement;
	for(int x = 0; x < i; x++){
		if( (movement = check_validation(seq[x])) == 0){
			fprintf(stderr,"invalid movement\n");
		}else{
			move(seq[x], movement);
		}
	}
	/*
	for (int i = 0; i < Model.map_width; i++) {
      		for (int j = 0; j < Model.map_height; j++) {
                	fprintf(stderr,"%3d ",map[i][j]);
		}
		fprintf(stderr,"\n");
	}
	*/	
	free(buf);
	
	return 0;
}
#endif


//recv_msg(), handle_cmd()
#ifdef RECV_HANDLE
extern int event_arry[20];
extern int rear ;
extern int front ;
int main(int argc, char *argv[]){
	
	char jsonpath[] = "./testcases/parseJson/map1.json";

	char stdin_input[256];
	read(STDIN_FILENO, stdin_input, sizeof(stdin_input));
	
	struct stat sb;
	if(stat(jsonpath, &sb) == -1){
		fprintf(stderr,"ERROR: stat\n");
		exit(1);
	}

	int file_size = sb.st_size;
	
	char *buf;
	buf = (char *)malloc(sizeof(char) * file_size);
	if(buf == NULL){
		fprintf(stderr, "ERROR: malloc\n");
		exit(1);
	}
	int json_fd;
	json_fd = open(jsonpath, O_RDONLY);
	read(json_fd, buf, file_size);
	
	if(parseJson(buf)){
		fprintf(stderr, "ERROR: parseJson\n");
		free(buf);
		exit(1);
	}else{
		fprintf(stderr, "PASS\n");
	}

	map = (int **) malloc (sizeof(int *) * Model.map_width);
        for(int i=0;i<Model.map_width;i++){
                map[i] =(int *) malloc(sizeof(int) * Model.map_height);
        }

	update_cell();
	

	int fd[2];
	if(pipe(fd) == -1){
		fprintf(stderr, "ERROR: pipe\n");
		return 1;
	}

        char *token = strtok(stdin_input, " ");
        int tmp = 0;
	
	int i = 0;
	while(token != NULL){
                tmp = atoi(token);
                if( !(0 <= tmp  && tmp <= Model.max_user *4)){
                        return 1;
                }
		if(send_bytes(fd[1],(void*)&tmp,sizeof(int)) == -1){
			fprintf(stderr,"ERROR: send_byte\n");
			return 1;
		}
       	        fprintf(stderr, "%d ",tmp);
       	        token = strtok(NULL, " ");
		i++;
        }
	close(fd[1]);
	
	recv_msg( (void *)&fd[0]);

	for(int a = 0; a < i; a++){
		handle_cmd(NULL);
	}
	/*
	pthread_t pid_1;
	pthread_t pid_2;
	pthread_create(&pid_1, NULL, recv_msg, (void *)&fd[0]);
	pthread_create(&pid_2, NULL, (void*)&handle_cmd, NULL);

	pthread_join(pid_1, NULL);
	pthread_join(pid_2, NULL);
	*/
}
#endif



