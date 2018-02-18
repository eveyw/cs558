#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <netdb.h>
#define MAX 1000
char *cmd_process(char *line);
void sendall(int fd, char const *buf)
{
        int done = 0;
        int ret;
        int n = strlen(buf);
        while (1){
                ret = write(fd, buf + done, n - done);
                if (ret < 0){
                        perror("write sockfd");
                        exit(5);
                }
                done += ret;
                if (done == n) return;
        }

}
void readall(int fd, char *recvline, int max)
{
        int n, done = 0;
        while ((n = read(fd, recvline + done, max - done)) > 0 && done < max){
                if (n < 0) {
                        perror("read");
                        exit(6);
                }
		done += n;
                if (recvline[done - 1] == '\n') {
			recvline[done - 1] = '\0';
			break;
		}
        }
}
int newlisten(int port)
{
	int listenfd;
	static struct sockaddr_in servaddr;
        /* Create a TCP socket */
        listenfd = socket(AF_INET, SOCK_STREAM, 0);

        /* Initialize server's address and well-known port */
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family      = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port        = htons(port);

        /* Bind server<92>s address and port to the socket */
        bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
        /* Convert socket to a listening socket <96> max 100 pending clients*/
 	listen(listenfd, 100);
	return listenfd;

}
void process(int);
int main(int argc, char **argv) {
        int   listenfd, connfd, clilen;
        struct sockaddr_in  cliaddr;

	listenfd = newlisten(atoi(argv[1]));

	for ( ; ; ) {
      /* Wait for client connections and accept them */
	clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
	process(connfd);

	}
}
void process(int fd)
{
	char readline[MAX];
	while(1){
		readall(fd, readline, MAX);
		if (strcmp(readline, "exit") == 0){
			close(fd);
			break;
		} else {
			sendall(fd, cmd_process(readline));
		}
	}
}

