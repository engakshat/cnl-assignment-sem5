//UDP Server
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT 8080
#define MAXLINE 1024
int main()
{
int sockfd;
char buffer[MAXLINE];
const char *hello = "Hello from server!";
struct sockaddr_in servaddr, cliaddr;
// Create UDP socket
sockfd = socket(AF_INET, SOCK_DGRAM, 0);
if (sockfd < 0)
{
perror("Socket creation failed");
exit(EXIT_FAILURE);
}
// Clear address structures
memset(&servaddr, 0, sizeof(servaddr));
memset(&cliaddr, 0, sizeof(cliaddr));
// Server information
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = INADDR_ANY;
servaddr.sin_port = htons(PORT);
// Bind socket to port 8080
if (bind(sockfd,
(const struct sockaddr *)&servaddr,
sizeof(servaddr)) < 0)
{
perror("Bind failed");
close(sockfd);
exit(EXIT_FAILURE);
}
printf("UDP Server started...\n");
printf("Waiting for client message on port %d...\n", PORT);
socklen_t len = sizeof(cliaddr);
// Receive message from client
int n = recvfrom(sockfd,
buffer,
MAXLINE - 1,
0,
(struct sockaddr *)&cliaddr,
&len);
if (n < 0)
{
perror("Receive failed");
close(sockfd);
exit(EXIT_FAILURE);
}
buffer[n] = '\0';
printf("Client: %s\n", buffer);
// Send response
if (sendto(sockfd,
hello,
strlen(hello),
0,
(const struct sockaddr *)&cliaddr,
len) < 0)
{
perror("Send failed");
close(sockfd);
exit(EXIT_FAILURE);
}
printf("Response sent to client.\n");
close(sockfd);
return 0;
}
//UDP Client
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT 8080
#define MAXLINE 1024
int main()
{
int sockfd;
char buffer[MAXLINE];
const char *message = "Hello from client!";
struct sockaddr_in servaddr;
// Create UDP socket
sockfd = socket(AF_INET, SOCK_DGRAM, 0);
if (sockfd < 0)
{
perror("Socket creation failed");
exit(EXIT_FAILURE);
}
// Clear server address
memset(&servaddr, 0, sizeof(servaddr));
// Server information
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(PORT);
// Server is running on localhost
if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0)
{
perror("Invalid server address");
close(sockfd);
exit(EXIT_FAILURE);
}
// Send message to server
if (sendto(sockfd,
message,
strlen(message),
0,
(const struct sockaddr *)&servaddr,
sizeof(servaddr)) < 0)
{
perror("Send failed");
close(sockfd);
exit(EXIT_FAILURE);
}
printf("Message sent to server.\n");
// Receive response
socklen_t len = sizeof(servaddr);
int n = recvfrom(sockfd,
buffer,
MAXLINE - 1,
0,
(struct sockaddr *)&servaddr,
&len);
if (n < 0)
{
perror("Receive failed");
close(sockfd);
exit(EXIT_FAILURE);
}
buffer[n] = '\0';
printf("Server: %s\n", buffer);
close(sockfd);
return 0;
}
