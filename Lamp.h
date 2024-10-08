#pragma once
#ifndef LAMP_H
#define LAMP_H
#include <string>
#include <iostream>
#include "Server.h"
#include <sstream>
#include "Clients.h"
#include "Stopwatch.h"

using namespace std;



class Lamp : public Client
{
public:

    Lamp(int);

    void Overdag(int);
    void Nacht(int);
    void Noodsituatie();

    void setID(int a);

    int getID();

    string getResponseBuffer() override;
    void setResponseBuffer();
    void verwerkData(const string data, bool nacht, bool noodsituatie) override;
    void logica();

private:

    int ID;
    int bewegingSenWaarde;
    int brightness;
    int rood;
    int groen;
    int blauw;

    bool wanneerLevenWe, Nood;

    int BewegingSenStatus;
    unsigned int helderheidsNiveau;
    unsigned int RGBWaarde;

    int bedSwitch;

    string response;
    Stopwatch stopwatch;

};
#endif // LAMP_H