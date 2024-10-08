#pragma once
#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "Clients.h"

#include <map>
#include "Controller.h"

#define PORT 8080
class Controller;

class Server {
public:
    Server(Controller* control);
    ~Server();

    void startListening();
    
    void stuurAntwoord(char* verzendData);
    void printOntvangenBericht();
    void closeConnection();
    void leesGegevens();
    void accepteerVerbinding();
    void voegClienttoe(Client *);
    
    
    
private:
    string convertToString(char* deZin);
    int clientID;
    int server_fd;
    int new_socket;
    int opt = 1;
    
    char buffer[1024] = { 0 };
    string responseClient;
    string recieveBuffer;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    ssize_t valread;  

    Controller* control;
};

#endif
