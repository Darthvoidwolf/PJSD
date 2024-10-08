
#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Zuil.h"
#include "Stoel.h"
#include "Deur.h"
#include "Bed.h"
#include <vector>
#include "Clients.h"
#include <sstream>
#include <string>
#include "Muur.h"
#include "Lamp.h"
using namespace std;


class Controller{

public:
    
  Controller(vector<Client*>& apparaten);
  ~Controller();
  
  void printVectorLijst();
  void findID(string buffer);
  void findClient();
  string getClientResponseBuffer();
  void setClientResponseBuffer(string);
  void connectieBedLamp();
  void saveValueBed(string buffer);
  void PiClient(string responseBuffer);
 
  bool getNoodStatus();
  bool getBrandDetectie();

  void zitTijd();
  void deurTijd();
private:  
  vector<Client*>& apparaten;
  int OntvangenClientID;
  int Data1,Data2,Data3,Data4,Data5,Data6,Data7;
  string recieveBuffer;
  string responseBuffer;
  bool nacht = false; //bij false dag en bij treu nacht
  bool noodsituatie = false;

  string opgeSlagenStringLamp;
  int opslagBedLamp;
  string responsePiClient;


  int deurStatus = 100;
  bool rookDetectie;
  int bedTimer = 100;
  int stoelTimer = 100;
  int lampTimer= 100;

};
#endif