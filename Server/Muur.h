#pragma once
#ifndef MUUR_H
#define MUUR_H

#include <string>
#include <iostream>
#include "Server.h"
#include <sstream>
#include "Clients.h"
using namespace std;




class Muur : public Client
{

    public:
    Muur(int);
  
   void Overdag(int VensterCommand,int LDR, int Pot);
   void Nacht(int Pot);
   void Noodsituatie();
   void setID(int a);
   int getCommandVenster();
   int getHelderheidsniveau();
   int getLDR();
   int getID() ;

  string getResponseBuffer() override;
  void setResponseBuffer();
  void verwerkData(const string buffer, bool nacht, bool noodsituatie) override;
  void logica() override;

    private:
    int ID;
    int Venster;
    int LDR;
    int Pot;
    int brightness;
    int rood;
    int groen;
    int blauw;

    bool wanneerLevenWe, Nood;
  
    unsigned int commandVenster;
    unsigned int helderheidsniveau;
    unsigned int RGBWaarde;

    string response;
    Stopwatch stopwatch;

};
#endif // MUUR_H
