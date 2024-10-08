#ifndef ZUIL_H_
#define ZUIL_H_

#include "Clients.h"  // Zorg ervoor dat dit de juiste header is voor je Client-klasse
#include <sstream>
class Zuil : public Client {
public:
    Zuil();
    Zuil(int );  // Constructor
    virtual ~Zuil(); // Destructor
    
    int getID();
    void setID(int a);
    void verwerkData(const string data, bool nacht, bool noodsituatie) override; // Overschrijf de virtuele methode van Client
    void setResponseBuffer();
    string getResponseBuffer() override;
    void logica() override;
    bool getNoodStatus();
private:
    // Stoel-specifieke attributen
    void bepaalLedStatus();
    void bepaalBuzzerStatus();

    int ID;
    int knopStatus;
    int ledStatus;
    int buzzerStatus;
    int rookSensorWaarde;
    int nieuweLedStatus;
    int nieuweBuzzerStatus;

    string response;


    bool wanneerLevenWe;
    bool Nood;
    bool brandGedetecteerd;
};

#endif /* ZUIL_H_ */