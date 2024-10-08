#include "Clients.h"
#include <cstdio>

Client::Client(){}

Client::Client(int ID){
    //    std::cout << "Client aangemaakt"<< std::endl;
        setID(ID);
    }


Client::~Client(){}

void Client::printID() const {
    std::cout << "Client ID: " << hetID << std::endl;
}

int Client::getID(){
    return hetID;
}

void Client::setID(int a){
    hetID = a;
}

void Client::verwerkData(const string buffer, bool nacht, bool noodsituatie){
    cout<<"client verwerkt data"<<endl;
}

void Client::setResponseBuffer(){
    cout<<"client gaat fout"<<endl;
}

string Client::getResponseBuffer(){
    cout << "getResponseBuffer CLIENT" << endl;
    return responseBuffer;
}

void Client:: logica()
{
    cout << "logica CLIETN" << endl;
}
bool Client::getNoodStatus(){
    return 0;
}
