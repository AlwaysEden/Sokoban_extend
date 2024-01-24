#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int game_start;
int usr_cnt;

int clnt_cnt = 1024;
int clnt_socks[1024]; //sock의 최대 개수는 최대 멤버 수일 것이기 때문에 여기서는 임의로 지정.

void disconnected(int sock)
{
        for (int i = 0; i < clnt_cnt; i++)   // remove disconnected client
        {
                if (sock == clnt_socks[i])
                {
                        while (i < clnt_cnt-1)
                        {
                                clnt_socks[i] = clnt_socks[i+1];
                                i++;
                        }
                        break;
                }
        }
        clnt_cnt--;

        if(clnt_cnt == 0)
        {
                game_start = 0;
                usr_cnt = 0;
		return;
        }
        printf("close(%d);\n", sock);
}

int main()
{
	int fd = open("test.txt", O_RDONLY);
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
	
	disconnected(clnt_socks[1]);
}
