#include "Server.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Server::Server(Controller* control)
: control(control)
{
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket to non-blocking mode
    if (fcntl(server_fd, F_SETFL, O_NONBLOCK) < 0) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
    
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Server::~Server() {
    close(server_fd);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Server::accepteerVerbinding() {
    
    while (1)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) { 
        if(errno == EWOULDBLOCK || errno == EAGAIN){
            continue;
        }   else{
            perror("accept");
            exit(EXIT_FAILURE);
        }
    }
    while(1)
    {
        leesGegevens();
        responseClient = control->getClientResponseBuffer();
        cout<< "Server responseclient: " <<responseClient<<endl;
        send(new_socket, responseClient.c_str(), responseClient.length(), 0);
      
        //memset(responseClient.c_str(),0,sizeof(responseClient));
        break;
    }
    closeConnection();
}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Server::leesGegevens() {
    // Lees gegevens van de socket
    valread = read(new_socket, buffer, 1024 - 1);
    if (valread > 0) {
        buffer[valread] = '\0'; // Null-terminate de ontvangen 'data'
     //       printf("leesGegevens server.\n");
        printOntvangenBericht();
        recieveBuffer = convertToString(buffer);
       // cout <<" Dit is de recieveBuffer LeesgegevenServer nu:"<< recieveBuffer << endl;
        control->findID(recieveBuffer);
        control->findClient();
    } else {
        printf("Client requested to exit. Closing connection.\n");
        close(new_socket);
        // of een andere geschikte waarde in geval van een fout
    }      
    memset(buffer, 0, 1024); // reset buffer
}

 /////////////////////////////////////////////////////////////////////////////////////////////////////////////       

void Server::printOntvangenBericht(){
   printf("Received data from the client: %s\n", buffer);
}    
 
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////       

void Server::stuurAntwoord(char* verzendData){
    printf("Response naar client: %s\n", verzendData);
    send(new_socket, verzendData, strlen(verzendData), 0);
}

void Server::closeConnection(){
    // closing the connected socket
    close(new_socket);
  //  printf("Closing the connection with the client\n");
}
   
   
string Server::convertToString(char* deZin) {
    // Converteert een enkele char naar een string
    return string(deZin);
}

