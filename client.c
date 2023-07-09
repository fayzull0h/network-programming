#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main () {
    char * hello = "hello from client\n";

    // Loads sockaddr_in struct onto stack and zeroes it
    //      don't have to do memset later
    struct sockaddr_in servaddr = {0};

    /* Explanation: socket object
     * AF_INET - IPv4
     * SOCK_DGRAM - UDP packet signifier
     * 0 - protocol 0 for computer to know it's UDP
     */
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Error handling
    if (sockfd == -1) {
        perror("ERROR: Failed to create socket!");
        exit(EXIT_FAILURE);
    }

    /** Setting destination
     * sin_family set to IPv4
     * htons configures the endianness properly
     * INADDR_ANY = 0.0.0.0
     * 
    */
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(12345);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Sending string to server
    int len = sendto(sockfd, (const char *)hello, strlen(hello), 
        0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    
    // Error handling
    if (len == -1) {
        perror("ERROR: Failed to send string to server");
    }
    close(sockfd);

    return 0;
}