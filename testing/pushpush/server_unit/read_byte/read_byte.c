#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

/*
 * read_byte의 읽기 파일은 write_byte가 작성한 파일을 읽는다.왜냐하면 int가 btye로 작성되어 있기 때문.
 */

int read_byte(int sock, void * buf, int size)
{
        int read_size = 0;
        int str_len = 0;
        while(read_size < size)
        {
                str_len = read(sock, buf + read_size, size - read_size);
                if( str_len == 0 || str_len == -1)
                {
                        //Disconnect()이 있던 자리.
			return 0;
                }
                read_size += str_len;
        }
        return read_size;
}

int main(){
        int fd = open("./testcases/test1.txt", O_RDONLY);
        int buf; //모든 입력 값이 int이기 때문.
        int read_len = read_byte(fd,&buf, sizeof(buf));
        if(read_len == -1){
                fprintf(stderr, "disconnect\n");
                exit(1);
	}
	printf("read: %d\n",buf);
}
