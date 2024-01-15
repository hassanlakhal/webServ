// server.cpp
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating server socket." << std::endl;
        return -1;
    }

    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7071); // You can choose any available port
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == -1) 
    {
        std::cerr << "Error binding server socket." << std::endl;
        close(serverSocket);
        return -1;
    }

    if (listen(serverSocket, 5) == -1) 
    {
        std::cerr << "Error listening on server socket." << std::endl;
        close(serverSocket);
        return -1;
    }

    std::cout << "Server is listening for connections..." << std::endl;

    fd_set masterSet;
    FD_ZERO(&masterSet);
    FD_SET(serverSocket, &masterSet);
    int maxFd = serverSocket;

    char resp[] = "HTTP/1.0 404 OK\r\n"
                  "Server: webserver-c\r\n"
                  "Content-type: text/html\r\n\r\n"
                  "<html><div class=\"main\"><h1>Welcome To GFG</h1><h3>Choose Your Gender</h3><form><label>Male<input type=\"radio\" 'name=\"gender\" value=\"male\" /></label><label>Female<input type=\"radio\"name=\"gender\" value=\"female\" /></label></form></div></html>\r\n";
    while (true) 
    {
        fd_set readSet = masterSet;
        if (select(maxFd + 1, &readSet, nullptr, nullptr, nullptr) == -1) 
        {
            std::cerr << "Error in select." << std::endl;
            break;
        }
        for (int fd = 0; fd <= maxFd; ++fd) 
        {
            if (FD_ISSET(fd, &readSet)) 
            {
                if (fd == serverSocket) 
                {
                    // New connection
                    sockaddr_in clientAddr;
                    memset(&clientAddr, 0, sizeof(clientAddr));
                    socklen_t clientAddrLen = sizeof(clientAddr);
                    int clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrLen);
                    // create container that hold client vec_clients.push_back()
                    if (clientSocket == -1) 
                    {
                        std::cerr << "Error accepting client connection." << std::endl;
                        continue;
                    }
                    std::cout << "Client connected." << std::endl;
                    FD_SET(clientSocket, &masterSet);
                    if (clientSocket > maxFd) 
                        maxFd = clientSocket;
                    // std::cout << clientSocket << std::endl;
                } 
                else 
                {
                    // Data from an existing client
                    // std::cout << fd << std::endl;
                    char buffer[1024];
                    ssize_t bytesRead = recv(fd, buffer, sizeof(buffer), 0);
                    if (bytesRead <= 0) 
                    {
                        // Client disconnected
                        std::cout << "Client disconnected." << std::endl;
                        close(fd);
                        FD_CLR(fd, &masterSet);
                    } 
                    else 
                    {

                        //  parsing the header
                        // server client
                        // if(client(fd))) // return true or false
                        // {
                        //       std::cout << "Client is served ." << std::endl;
                        //          close(fd);
                        //          FD_CLR(fd, &masterSet);
                        //  }
                        // Process the received data (you can implement your own logic here)
                        buffer[bytesRead] = '\0';
                        std::cout << "Received data from client: " << buffer << std::endl;
                    }
                }
            }
        }
    }

    close(serverSocket);

    return 0;
}
