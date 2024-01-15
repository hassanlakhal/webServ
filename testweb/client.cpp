// server.cpp
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/event.h>

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating server socket." << std::endl;
        return -1;
    }

    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5050); // You can choose any available port
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

    int kq = kqueue();
    if (kq == -1) {
        std::cerr << "Error creating kqueue." << std::endl;
        close(serverSocket);
        return -1;
    }

    struct kevent event;
    EV_SET(&event, serverSocket, EVFILT_READ, EV_ADD, 0, 0, nullptr);

    if (kevent(kq, &event, 1, nullptr, 0, nullptr) == -1) {
        std::cerr << "Error registering server socket with kqueue." << std::endl;
        close(serverSocket);
        close(kq);
        return -1;
    }

    while (true) {
        struct kevent events[2];  // You can adjust the size based on your needs
        int numEvents = kevent(kq, nullptr, 0, events, sizeof(events) / sizeof(events[0]), nullptr);

        for (int i = 0; i < numEvents; ++i) {
            if (events[i].ident == static_cast<uintptr_t>(serverSocket)) {
                // New connection
                sockaddr_in clientAddr;
                socklen_t clientAddrLen = sizeof(clientAddr);
                int clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrLen);

                if (clientSocket == -1) {
                    std::cerr << "Error accepting client connection." << std::endl;
                    continue;
                }

                std::cout << "Client connected." << std::endl;

                struct kevent change;
                EV_SET(&change, clientSocket, EVFILT_READ, EV_ADD, 0, 0, nullptr);

                if (kevent(kq, &change, 1, nullptr, 0, nullptr) == -1) {
                    std::cerr << "Error adding client socket to kqueue." << std::endl;
                    close(clientSocket);
                }
            } else {
                // Data from an existing client
                char buffer[1024];
                ssize_t bytesRead = recv(events[i].ident, buffer, sizeof(buffer), 0);

                if (bytesRead <= 0) {
                    // Client disconnected
                    std::cout << "Client disconnected." << std::endl;
                    close(events[i].ident);
                } else {
                    // Process the received data (you can implement your own logic here)
                    buffer[bytesRead] = '\0';
                    std::cout << "Received data from client: " << buffer << std::endl;
                }
            }
        }
    }

    close(serverSocket);
    close(kq);

    return 0;
}
