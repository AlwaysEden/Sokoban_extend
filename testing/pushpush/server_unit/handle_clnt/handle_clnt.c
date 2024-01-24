#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define NAME_SIZE 16

int max_user = 4;
int clnt_cnt = 5; //clnt_cnt 임의로 지정
int usr_cnt = 0;
char **user_name;

int clnt_socks[1024]; //다른 함수가 설정함이 보장되기 때문에 임의로 설정

void handle_clnt(void * arg) //원본은 void*함수이나 현재는 call하기 위해서 pointer를 제외한 상황
{
        int clnt_sock = *((int*)arg);
        int name_size = 0;

        /*recive name size*/
        //read_byte(clnt_sock, (void *)&name_size, sizeof(int));
        
	/*reciev name, send id*/
        //pthread_mutex_lock(&mutx);
        for (int i = 0; i < clnt_cnt; i++)
        {
                if (clnt_sock == clnt_socks[i])
                {
                        //name_size = read_byte(clnt_sock, (void *)user_name[i], name_size);
                       	strcpy(user_name[i], "Jeongwon"); //username을 받았다고 가정하고, 고정으로 이름 넣기
			printf("%s is enter\n",user_name[i]);
                        //write_byte(clnt_sock, (void *)&i, sizeof(int));
                        usr_cnt++;
                        break;
                }
        }
        //pthread_mutex_unlock(&mutx);

        /*send json*/
        //write_byte(clnt_sock, (void *)&json_size, sizeof(int));
        //write_byte(clnt_sock, json_serialize, json_size);

        //while(usr_cnt < max_user); //wait untill all user is connected

        //send connected user information
        for(int i=0; i< max_user; i++)
        {
                int len = strlen(user_name[i]);
                //write_byte(clnt_sock, &len,sizeof(int));
                //write_byte(clnt_sock,user_name[i], len);
        }

        //receive and echo command
	int event = 1; //event의 범위는 max_user에 따라달라진다.
        while (event > 0/*read_byte(clnt_sock, (void *)&event, sizeof(int))*/)
        {
                printf("move: %d\n", event);
                //send_msg_all((void *)&event, sizeof(int));
                //detect end flag
                if(event == max_user*4)
                {
                        printf("end game!\n");
                        //disconnected(clnt_sock);
                }
		event = 0;//임의로 설정.
        }

        return;
}



int main(){

	user_name = (char**)malloc(sizeof(char*) * max_user);
        for(int i=0; i< max_user; i++)
        {
                user_name[i] = (char*)malloc(sizeof(char) * NAME_SIZE);
        }
	int fd = open("testcases/test1.txt", O_RDONLY);
        char buf[4096];

        read(fd, buf, 4096);
        char *token = strtok(buf," ");

        int i = 0;
        while(token != NULL){
                clnt_socks[i]= atoi(token);
                token = strtok(NULL," ");
                i++;
        }
        for(int a = 0; a < i; a++){
                printf("%d\n",clnt_socks[a]);
        }
	handle_clnt(&clnt_socks[1]);
}
