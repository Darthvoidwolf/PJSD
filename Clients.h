#ifndef CLIENT_H_
#define CLIENT_H_

#include <sys/time.h>
#include <string>
#include <iostream>
#include <vector>
#include <numeric>
#include "Stopwatch.h"
using namespace std;


class Client {
public:
    Client();
    Client(int);
    virtual ~Client(); // Maak de destructor virtueel

    
    virtual int getID() ; 
    virtual void setID(int a) ;
    void printID() const;
    virtual void verwerkData(const string buffer, bool nacht, bool noodsituatie);
    virtual void setResponseBuffer() = 0;
    virtual string getResponseBuffer();
    virtual void logica();
    bool getNoodStatus();
    
private:
    int hetID;
    string responseBuffer;
};

#endif /* CLIENT_H_ */
