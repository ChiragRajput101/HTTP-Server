#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <netdb.h>
#include <arpa/inet.h>

// connecting to web browsers via http (port 80)

int main(int argc, char *argv[]) {

    int cli_soc = socket(AF_INET, SOCK_STREAM, 0);

    char *address;
    address = argv[1];

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80); // for conn to web browsers via http (port 80 is the default port)
    inet_aton(address, &server_addr.sin_addr.s_addr);

    char http_req[] = "GET / HTTP/1.1 \r\n\r\n";
    char response[4096];

    connect(cli_soc, (struct sockaddr *) &server_addr, sizeof(server_addr));

    send(cli_soc, http_req, sizeof(http_req), 0);
    recv(cli_soc, response, sizeof(response), 0);

    printf("%s\n", response);
    
    close(cli_soc);
    
    return 0;
}