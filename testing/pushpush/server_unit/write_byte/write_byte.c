#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int write_byte(int sock, void * buf, int size)
{

        int write_size = 0;
        int str_len = 0;
        while(write_size < size)
        {
                str_len = write(sock, buf + write_size, size - write_size);
                if( str_len == -1)
                {
                	return -1; //error
		}
                write_size += str_len;
        }
        return write_size;
}

int main(){
	int fd = open("test.txt", O_WRONLY | O_CREAT, 0666);
	int stdinput; //모든 입력 값이 int이기 때문.
	scanf("%d",&stdinput);

	char buf[10]; //파일에 쓰고 확인하기 위해 문자열로 변환
	sprintf(buf, "%d", stdinput);	
	int write_len = write_byte(fd,(void*)&buf, strlen(buf));	
	if(write_len == -1){
		fprintf(stderr, "disconnect\n");
		exit(1);
	}
}
