#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define MAX 1000
void fun(char const *arg1, char const *arg2);
int main(int argc, char **argv) {
	if(argc!=3){
		printf("Usage : %s <IP address or domain name> <port>", argv[0]);
		exit(1);
	}
	fun(argv[1], argv[2]);
}
struct sockaddr_in makeaddr(char const *argv1, char const *argv2)
{
	struct sockaddr_in ret;
	struct hostent *hent;
	bzero(&ret, sizeof(ret));
	ret.sin_family = AF_INET;
	ret.sin_port = htons(atoi(argv2));
	if (!isdigit(argv1[0])){
		hent = gethostbyname(argv1);
		if (hent == NULL){
			perror("gethostbyname");
			exit(3);
		} else {
			memcpy(&ret.sin_addr, hent->h_addr_list[0], 4);
		}
	}
	else if (inet_pton(AF_INET, argv1, &ret.sin_addr) <= 0){
		perror("inet_pton"); 
		exit(3);
	}
	return ret;
}
int newconnect(char const *argv1, char const *argv2)
{
	int sockfd;
	static struct sockaddr_in servaddr;

        /* Create a TCP socket */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket"); 
		exit(2);
	}
	servaddr = makeaddr(argv1, argv2);
	/* Connect to the server */
	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
                 perror("connect"); exit(4); 
	}
	return sockfd;
}
void process(int);
void fun(char const *argv1, char const *argv2)
{
	int sockfd;
	sockfd = newconnect(argv1, argv2);
	process(sockfd);
}
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
void readall(int fd)
{
	int n;
	char recvline[MAX];
	while ((n = read(fd, recvline, MAX)) > 0){
		recvline[n] = '\0';
		printf("%s", recvline);
		if (n < 0) {
			perror("read");
			exit(6);
		}
		if (recvline[n - 1] == '\n') break;
	}
}
void process(int sockfd)
{
	int keepgoing = 1;
	char sendline[MAX];
	while (keepgoing){
		printf("telnet > ");
		fgets(sendline, MAX, stdin);
		sendall(sockfd, sendline);
		if (strcmp(sendline, "exit\n") == 0){
			close(sockfd);
			return;
		}
		readall(sockfd);
	}

}
