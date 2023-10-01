#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv[]) {
    // creating the socket

    int server_sock = socket(AF_INET, SOCK_STREAM, 0);

    int port_no = atoi(argv[1]);

    struct sockaddr_in server_addr;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_no);

    // binding the socket to server's IP and port

    bind(server_sock, (struct sockaddr *) &server_addr, sizeof(server_addr));
    listen(server_sock, 1); // backlog - 1

    char conn_confir[] = "Connection is established";

    struct sockaddr_in client_addr;
    socklen_t client_len;
    client_len = sizeof(client_addr);

    int connected_sock = accept(server_sock, (struct sockaddr *) &client_addr, &client_len);

    if(connected_sock == -1) {
        printf("Error while accepting an incoming request");
        exit(1);
    }

    send(connected_sock, conn_confir, sizeof(conn_confir), 0);

    return 0;
}
