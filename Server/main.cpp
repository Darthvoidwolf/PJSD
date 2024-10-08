
#include <vector>
#include "Clients.h"
#include "Stoel.h"
#include "Zuil.h"
#include "Controller.h"
#include "Server.h"
#include "Muur.h"
#include "Lamp.h"
#include "Deur.h"
#include "CheckDagNachtNood.h"
#include "Bed.h"
//#include "Clients.h"
using namespace std;


int main(int argc, char const* argv[]){


  vector<Client* > apparaten;
  Zuil* zuil1 = new Zuil(0);
  Bed* bed1 = new Bed(1);
  Stoel* stoel1 = new Stoel(2);
  Lamp* lamp1 = new Lamp(3);
  Deur* deur1 = new Deur(4);
  Muur* muur1= new Muur(5);
  CheckDagNachtNood* checkDagNachtNood1 = new CheckDagNachtNood(6);
   
  
  
  
  apparaten.push_back(zuil1);
  apparaten.push_back(bed1);
  apparaten.push_back(stoel1);
  apparaten.push_back(lamp1);
  apparaten.push_back(deur1);
  apparaten.push_back(muur1);
  apparaten.push_back(checkDagNachtNood1);
  Controller myController(apparaten);
 

  Server myServer(&myController);
  myServer.accepteerVerbinding();     
    }

