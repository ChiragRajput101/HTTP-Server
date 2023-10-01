#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    
    int soc = socket(AF_INET, SOCK_STREAM, 0);
    if(soc == -1) error("creat socket error");

    int port_no = atoi(argv[2]);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    // server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_no);

    // conn to server 
    int Connect = connect(soc, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if(Connect == -1) {
        error("Error while connecting");
    } 

    char server_response[256];
    int REC = recv(soc, &server_response, sizeof(server_response), 0);
    if(REC == -1) error("cant rec the mssge from server");

    printf("Server: %s\n", server_response);

    return 0;
}