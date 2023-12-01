#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_PORT 9001

// Server workflow: socket() -> bind() -> listen() -> accept -> close()
int main() {
    char server_response[256] = "Server response!";

    // Create server socket
    int server_socket = socket(
        AF_INET,        // IPv4
        SOCK_STREAM,    // TCP (as opposed to UDP, datagrams)
        IPPROTO_IP      // use default IP for TCP
    );
    
    // Server address that clients will be connect()ing to
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;    // 0.0.0.0
    server_address.sin_port = htons(SERVER_PORT);   // 0.0.0.0:9001

    int bind_status = bind(
        server_socket, 
        (struct sockaddr *) &server_address,
        sizeof(server_address)
    );
    if (bind_status == -1) {
        printf("Unable to bind the specified address to the socket.\n");
    }

    listen(server_socket, 1);
    printf("Server listening on %hu:%i\n", server_address.sin_addr.s_addr, SERVER_PORT);

    // Those last two arguments are if you know you want to restrict incoming connections to specific client endpoints, but since this is just a localhost demo, we can leave them NULL
    int client_socket = accept(server_socket, NULL, NULL);

    // Send server response to client
    send(client_socket, server_response, sizeof(server_response), 0);

    close(server_socket);
    return 0;
};
