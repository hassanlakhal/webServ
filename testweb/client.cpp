// server.cpp
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating server socket." << std::endl;
        return -1;
    }

    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(50512); // You can choose any available port
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == -1) {
        std::cerr << "Error binding server socket." << std::endl;
        close(serverSocket);
        return -1;
    }

    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Error listening on server socket." << std::endl;
        close(serverSocket);
        return -1;
    }

    std::cout << "Server is listening for connections..." << std::endl;

    int epollFd = epoll_create(1);
    std::cout << epollFd << std::endl;
    if (epollFd == -1) 
    {
        std::cerr << "Error creating epoll file descriptor." << std::endl;
        close(serverSocket);
        return -1;
    }
    epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = serverSocket;

    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, serverSocket, &event) == -1)
    {
        std::cerr << "Error adding server socket to epoll." << std::endl;
        close(serverSocket);
        close(epollFd);
        return -1;
    }

    while (true) 
    {
        epoll_event events[10];  // You can adjust the size based on your needs
        int numEvents = epoll_wait(epollFd, events, sizeof(events) / sizeof(events[0]), -1);
        std::cout << numEvents << std::endl;
        for (int i = 0; i < numEvents; ++i) 
        {
            if (events[i].data.fd == serverSocket) 
            {
                // New connection
                sockaddr_in clientAddr;
                socklen_t clientAddrLen = sizeof(clientAddr);
                int clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrLen);
                if (clientSocket == -1) 
                {
                    std::cerr << "Error accepting client connection." << std::endl;
                    continue;
                }
                std::cout << "Client connected." << std::endl;
                event.events = EPOLLIN | EPOLLET; // Edge-triggered mode
                event.data.fd = clientSocket;
                if (epoll_ctl(epollFd, EPOLL_CTL_ADD, clientSocket, &event) == -1) {
                    std::cerr << "Error adding client socket to epoll." << std::endl;
                    close(clientSocket);
                }
            } 
            else 
            {
                // Data from an existing client
                char buffer[1024];
                ssize_t bytesRead = recv(events[i].data.fd, buffer, sizeof(buffer), 0);

                if (bytesRead <= 0) {
                    // Client disconnected
                    std::cout << "Client disconnected." << std::endl;
                    close(events[i].data.fd);
                    epoll_ctl(epollFd, EPOLL_CTL_DEL, events[i].data.fd, 0);
                } 
                else 
                {
                    // Process the received data (you can implement your own logic here)
                    buffer[bytesRead] = '\0';
                    std::cout << "Received data from client: " << buffer << std::endl;
                    close(events[i].data.fd);
                }
            }
        }
    }

    close(serverSocket);
    close(epollFd);

    return 0;
}
