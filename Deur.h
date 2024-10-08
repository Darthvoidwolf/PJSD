#ifndef DEUR_H
#define DEUR_H

#include <string>
#include <iostream>
#include <sstream>
#include "Clients.h"

using namespace std;

class Deur : public Client {
public:
    Deur();
    Deur(int);
    virtual ~Deur();
    int getID()override;
    void setID(int a)override;
    void verwerkData(string data, bool nacht, bool noodsituatie) override; // Overschrijf de virtuele methode van Client
    void setResponseBuffer()override;
    string getResponseBuffer()override;
    int getCommandoDeur();
    int getDeurPositie();

    void bepaalDeurPositieDag();
    void bepaalDeurPositieNacht();
    void bepaalDeurPositieNood();
    void logica();


private:
    string responseBuffer;
    bool wanneerLevenWe;
    bool Nood;

    int ID;
    int KnopBuiten;
    int KnopBinnen;
    int LEDBuiten;
    int LEDBinnen;
    //int DeurPositie;
    int NieuwLEDBuiten;
    int NieuwLEDBinnen;
    int NieuwDeurPositie;

    unsigned int commandoDeur;
    unsigned int DeurPositie;

    string response;
    Stopwatch stopwatch;

    //nsigned int commandoDeur;
    // char responseDeur[1024];


};

#endif // DEUR_H