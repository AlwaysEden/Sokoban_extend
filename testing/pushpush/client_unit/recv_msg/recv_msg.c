#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define queue_size 20//본 프로그램에서 Queue size는 20으로 고정되어 있다.

int event_arry[queue_size]; 
int rear = 1;
int front = 0; //rear와 front는 현재 이렇다는 상황 가정.


void recv_msg(void * arg)   // read thread main
{
        int sock = *((int*)arg);
       	char recv_cmd; //int->char로 변경. testing을 위해서 

        //now enter new move
        while(1){
                if(read(sock, &recv_cmd, sizeof(recv_cmd)) == -1) //recv_byte()를 사용하는 곳이지만 read로 대체
                        return (void)-1;
		//recv_cmd의 값은 서버에서 받기 때문에 값이 보장되어 있음.
        	fprintf(stderr, "From Server : %c\n", recv_cmd);

                //pthread_mutex_lock(&mutx);
                while((rear+1)%queue_size == front)
                        //pthread_cond_wait(&cond, &mutx);
                rear = (rear + 1) % queue_size;
                event_arry[rear] = recv_cmd;
                //pthread_cond_signal(&cond);
                //pthread_mutex_unlock(&mutx);
		break; // 한번 돌고 break하는 이유는 다른 함수에 의해서 front가 조정되어야지 한번 더 도는게 의미가 있는데, 현 시점에서는 의미가 없기 때문이다.
        }
        return;
}

int main(int argc, char *argv[]){
	char file[256];
	strcpy(file, argv[1]);
	int fd = open(file, O_RDONLY);
	recv_msg((void*)&fd);	
}
