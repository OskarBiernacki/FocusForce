#include "CommandServer.h"
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <cstring>

// Dodaj bibliotekę dla funkcji sieciowych

#define defaultResponce "<!DOCTYPE html><html lang='pl'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Witaj Podróżniku</title><style>body{font-family:Arial, sans-serif;display:flex;justify-content:center;align-items:center;flex-direction:column;height:100vh;margin:0;background-color:#f0f8ff;}h1{color:#333;}img{max-width:90%;height:auto;border-radius:8px;}</style></head><body><h1>Witaj Podróżniku</h1><img src='https://i.pinimg.com/originals/86/f0/7b/86f07b3af5597023a031511783402ead.gif' alt='Adventure'></body></html>";

const char* CommandServer::procedCommand(const char* command){
    std::string respondeMessage = "Hello Admin";
    const char *sicretPassword = "NinjaTurtle7122";
    for(int i=0;i<strlen(sicretPassword);i++){
        if(command[i]!=sicretPassword[i])
            return defaultResponce;
    }
    std::cout<< "Sicred password founded!\n";
    
    char *respond = new char[1024];
    for(int i=0;i<1024;i++)respond[i]=0;
    for(int i=0;i<respondeMessage.size() && i<1024;i++)
        respond[i]=respondeMessage[i];
    
    return respond;
}

void CommandServer::startTCPListener(int port) {
    WSADATA wsaData;
    SOCKET server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
        return;
    }
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return;
    }
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) == SOCKET_ERROR) {
        std::cerr << "Setsockopt failed: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR) {
        std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return;
    }
    if (listen(server_fd, 3) == SOCKET_ERROR) {
        std::cerr << "Listen failed: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return;
    }

    std::cout << "Listening " << port << "..." << std::endl;

    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) == INVALID_SOCKET) {
            std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
            continue;
        }
        std::cout << "New connection: " << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << std::endl;
        ssize_t valread = recv(new_socket, buffer, sizeof(buffer), 0);
        if (valread > 0) {
            std::cout << "recived: " << buffer << std::endl;

        } else {
            std::cerr << "Data ERROR: " << WSAGetLastError() << std::endl;
        }
        
        const char *response = procedCommand(buffer);
        send(new_socket, response, strlen(response), 0);
        std::cout << "respond: " << response <<std::endl;
        closesocket(new_socket);
        memset(buffer, 0, sizeof(buffer));
    }

    closesocket(server_fd);
    WSACleanup();
}