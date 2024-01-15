#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
int main(void)
{

    char buffer[1024] = {0};
    // create socket 
    char resp[] = "HTTP/1.0 404 OK\r\n"
                  "Server: webserver-c\r\n"
                  "Content-type: text/html\r\n\r\n"
                  "<html><div class=\"main\"><h1>Welcome To GFG</h1><h3>Choose Your Gender</h3><form><label>Male<input type=\"radio\" 'name=\"gender\" value=\"male\" /></label><label>Female<input type=\"radio\"name=\"gender\" value=\"female\" /></label></form></div></html>\r\n";

    int server_fd = socket(AF_INET, SOCK_STREAM,0);
    if(server_fd  < 0)
    {
        perror("socket failed");
        exit(1);
    }
    printf("Socket created successfully\n");

    //set Port and IP:


    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(2828);

    if (bind(server_fd,(struct sockaddr *)&address,sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(1);
    }
    
    
    socklen_t len = sizeof(address);
    // for (;;)
    // {
    //     /* code */
    // }
     int new_socket;
    while (1)
    {
        if (listen(server_fd,10) < 0)
        {
            perror("bind failed");
            exit(0);
        }
        new_socket = accept(server_fd,(struct sockaddr*)&address,&len);
        if (new_socket < 0)
        {
        perror("accept failed");
            exit(0);
        }
        int fd = read(new_socket,buffer,1023);
        int fd1 = write(new_socket,resp,strlen(resp));
        printf("%s",buffer);
        close(new_socket);
    }
    close(server_fd);
}