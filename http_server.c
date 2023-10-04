#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>
#include <netdb.h>

#define PORT_NO 6969
#define BACKLOG 1
#define HTTP_200_OK "HTTP/1.1 200 OK \r\n\r\n"

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    // the server sends the HTML to the client, in this case we will be only sending a dummy index.html file that only says "we are conn via http"
    FILE *html;
    html = fopen("index.html","r");

    // Reading a multi-line html file
    
    char buffer[128];
    char response_data[2048] = {'\0'}; //Initialize to '\0' so there's no garbage values since we will append to the end of this string
    while(fgets(buffer, sizeof(buffer), html)){
        strcat(response_data, buffer);
    }

    // char response_data[2048];
    // fgets(response_data, 2048, html);

    char http_header[2048] = HTTP_200_OK;
    strcat(http_header, response_data);


    // init TCP socket and conn

    int socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if(socketFD == -1) error("Couldnt create a socket\n");

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT_NO);

    int Bind = bind(socketFD, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if(Bind == -1) error("Cant bind to the port\n");


    struct sockaddr_in client_addr;
    socklen_t client_len;

    int Listen = listen(socketFD, BACKLOG);
    if(Listen == -1) error("Error while listening\n");

    while(1) {
        int clientFD = accept(socketFD, (struct sockaddr *) &client_addr, &client_len);
        if(clientFD == -1) error("Couldnt connect to client\n");
        else printf("connected!\n");

        send(clientFD, http_header, sizeof(http_header), 0);
        close(clientFD);
    }

    return 0;
}