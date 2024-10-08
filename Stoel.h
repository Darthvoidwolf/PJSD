#ifndef STOEL_H_
#define STOEL_H_
#include <sstream>
#include <string>

#include "Clients.h"  // Zorg ervoor dat dit de juiste header is voor je Client-klasse

class Stoel : public Client {
public:
    Stoel();
    Stoel(int);  // Constructor
    virtual ~Stoel(); // Destructor

    int getID();
    void setID(int a);
    void verwerkData(const string data, bool nacht, bool noodsituatie) override; // Overschrijf de virtuele methode van Client
    void setResponseBuffer()override;
    string getResponseBuffer() override;
    void logica() override;

    int getZitTijd();
private:
    // Stoel-specifieke attributen
    void bepaalLedStatus();
    void bepaalTrilStatus();

    int ID;

    bool wanneerLevenWe, Nood;
    
    int knopStatus;
    int ledStatus;
    int trilStatus;
    int drukSensorWaarde;
    int nieuweLedStatus;
    int nieuweTrilStatus;
    int totaleZitTijd = 0;

    
    Stopwatch stopwatch;
    string response;

};

#endif /* STOEL_H_ */