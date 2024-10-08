
#include "Zuil.h"

Zuil::Zuil()  {

}

Zuil::Zuil(int id) : Client(id) {
 //   std::cout << "Zuil " << id << std::endl;
    setID(id);
}


Zuil::~Zuil(){}

int Zuil::getID()
{
    return ID;
}


void Zuil::setID(int a){
    ID = a;
   // printf("Muur klasse setID 2\n");
}

void Zuil::verwerkData(const string data, bool nacht, bool noodsituatie) {
    //cout<<"zuil verwerkt data"<<endl;
    // Verwerk de ontvangen data specifiek voor Zuil
     sscanf(data.c_str(), "%*s %*u %*s %u %*s %u %*s %u %*s %u",&knopStatus, &buzzerStatus, &ledStatus, &rookSensorWaarde);
    wanneerLevenWe = nacht;
     Nood = noodsituatie;
}

void Zuil::setResponseBuffer() {
    //cout << "zuil: antwoord aan het samenstellen" << endl;

    

    ostringstream oss;
    oss << "ID: " << ID
        << " KNOP: " << knopStatus
        << " BUZZER: " << nieuweBuzzerStatus
        << " LED: " << nieuweLedStatus
        << " ROOKSENSOR: " << rookSensorWaarde
        << " } \n";

    response = oss.str();
    //cout << response << endl;

}

string Zuil::getResponseBuffer(){
    return response;
}

void Zuil::logica(){
    bepaalBuzzerStatus();
    bepaalLedStatus();
    setResponseBuffer();
}

void Zuil::bepaalLedStatus(){
    switch (knopStatus) {
    case 1:
        switch (ledStatus) {
        case 1:
            nieuweLedStatus = 0;
      //      printf("1 1 Led gaat uit\n");
            break;
        case 0:
            nieuweLedStatus = 1;
      //      printf("1 0 Led gaat aan\n");
            break;
        }
        break;

    case 0:
        switch (ledStatus) {
        case 0:
            nieuweLedStatus = 0;
     //       printf("0 0 Led is uit en knop niet ingedrukt\n");
            break;
        case 1:
            nieuweLedStatus = 1;
   //         printf("0 1 Led staat aan, knop niet ingedrukt\n");
            break;
        }
        break;
    }
}


void Zuil::bepaalBuzzerStatus(){
    // logica om het buzzer aan te zetten
   if(rookSensorWaarde > 450 || Nood == true){
        nieuweBuzzerStatus = 1; //zet buzzer aan
        brandGedetecteerd = true;
   }    else if(rookSensorWaarde <= 450 && Nood != true){
        nieuweBuzzerStatus = 0; //zet buzzer uit
        brandGedetecteerd = false;
   }
}


bool Zuil::getNoodStatus(){
    return brandGedetecteerd;
}
