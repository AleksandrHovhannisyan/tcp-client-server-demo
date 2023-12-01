#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    // Create client socket for sending requests
    int client_socket = socket(
        AF_INET,        // IPv4
        SOCK_STREAM,    // TCP (as opposed to UDP, datagrams)
        IPPROTO_IP      // use default IP for TCP
    );
    
    // Remote socket we are connecting to
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;            // IPv4
    server_address.sin_addr.s_addr = INADDR_ANY;    // 0.0.0.0
    server_address.sin_port = htons(9001);          // 0.0.0.0:9001

    // Connect to server socket
    int connection_status = connect(
        client_socket,
        (struct sockaddr *) &server_address,
        sizeof(server_address)
    );
    if (connection_status == -1) {
        printf("There was a network error connecting to the remote socket.\n");
    }

    // Send request to server and get response back in a buffer (string)
    // In this case we are limiting responses to only 256 char units
    char server_response[256];
    recv(
        client_socket, 
        &server_response, 
        sizeof(server_response), 
        0
    );
    printf("Server responded with: %s\n", server_response);

    close(client_socket);
    return 0;
};
