#ifndef CHECKDAGNACHTNOOD_H
#define CHECKDAGNACHTNOOD_H
#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include "Clients.h"

using namespace std;


class CheckDagNachtNood : public Client {
public:

    CheckDagNachtNood();
    CheckDagNachtNood(int);
    virtual ~CheckDagNachtNood();


    int getID()override;
    void setID(int a)override;
    void verwerkData(string data, bool nacht, bool noodsituatie) override; // Overschrijf de virtuele methode van Client
    void setResponseBuffer();
    string getResponseBuffer()override;

    bool bepaalDagNachtStatus();
    bool bepaalNoodStatus();
    void logica() override;


    bool getbrandstatus();

private:
    string responseBuffer;
    int ID;
    bool checkNoodsituatie;
    int checkisDag;
    int checkisNood;
    bool isNood;
    bool isDag;

   

};
// CheckDagNachtNood.h
#pragma once

#endif
