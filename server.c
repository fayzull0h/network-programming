#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
    char buffer[50] = {0};
    struct sockaddr_in servaddr = {0};

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd == -1) {
        perror("ERROR: Failed to create socket");
        exit(EXIT_FAILURE);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(12345);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Binding the socket to the server address
    int rc = bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    if (rc == -1) {
        perror("ERROR: Failed to bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Receive message
    // MSG_WAITALL - wait until whole message is received before returning
    socklen_t len = 0;
    int n = recvfrom(sockfd, (char *)buffer, 50, MSG_WAITALL, 0, &len);

    printf("%s", buffer);
    close(sockfd);

    return 0;
}