#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <errno.h>
#include <sys/stat.h>

int send_bytes(int sock_fd, void * buf, size_t len){
    char * p = (char *) buf;
    size_t acc = 0;

    while(acc < len){
        size_t sent;
        sent = write(sock_fd, p, len - acc);
	fprintf(stderr, "sent: %d\n",sent);
        if(sent == -1 || sent == 0){
            return -1;
        }

        p+= sent;
        acc += sent;
    }
    return 0;
}

int main(int argc, char *argv[]){
	struct sockaddr_in serv_addr;
        int sock = socket(PF_INET, SOCK_STREAM, 0);

        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
        serv_addr.sin_port = htons(atoi(argv[2]));

	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        {
                fprintf(stderr, "ERROR: connect() error\n");
                exit(1);
        }
        
        int game_started= 1;
        
	send_bytes(sock, (void*)&game_started, sizeof(int));
	while(1);


	return 0;
}
