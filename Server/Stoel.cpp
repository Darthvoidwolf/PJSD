
#include "Stoel.h"

Stoel::Stoel()  {

}

Stoel::Stoel(int id) : Client(id) {
 //   std::cout << "Stoel " << id << std::endl;
    setID(id);
}


Stoel::~Stoel(){}

int Stoel::getID()
{
    return ID;
}


void Stoel::setID(int a){
    ID = a;
   // printf("Muur klasse setID 2\n");
}

void Stoel::verwerkData(const string data, bool nacht, bool noodsituatie) {
    //cout<<"stoel verwerkt data"<<endl;
    // Verwerk de ontvangen data specifiek voor Stoel
     sscanf(data.c_str(), "%*s %*u %*s %u %*s %u %*s %u %*s %u",&knopStatus, &ledStatus, &trilStatus, &drukSensorWaarde);
    wanneerLevenWe = nacht;
     Nood = noodsituatie;
}

void Stoel::setResponseBuffer() {
    //cout << "stoel: antwoord aan het samenstellen" << endl;

    bepaalLedStatus();
    bepaalTrilStatus();

    ostringstream oss;
    oss << "ID: " << ID
        << " KNOP: " << knopStatus
        << " LED: " << nieuweLedStatus
        << " TRIL: " << nieuweTrilStatus
        << " DRUKSENSOR: " << drukSensorWaarde
        << " } \n";

    response = oss.str();
    //cout << response << endl;

}

string Stoel::getResponseBuffer(){
    
    //cout << "Stoel: Dit is mijn ResponseBuffer: "<< response << endl;
    return response;
}

void Stoel::logica(){
    
    setResponseBuffer();
}

void Stoel::bepaalLedStatus(){
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


void Stoel::bepaalTrilStatus(){
    cout<< "Stoel Stand is:"<< wanneerLevenWe<<endl;
    if(wanneerLevenWe == false){
   //     cout << "Verstreken tijd1: " << stopwatch.deTijd() << " seconden" << endl;

    // logica om het trilelement aan te zetten
    // Start de stopwatch als de druksensorwaarde boven 250 komt
        if (drukSensorWaarde > 250) {
            if (!stopwatch.isLopend()) {
                stopwatch.begin();
            }
 //   cout << "Verstreken tijd2: " << stopwatch.deTijd() << " seconden" <<endl;
            // Controleer of de stopwatch langer dan 5 seconden loopt
            if (stopwatch.deTijd() > 5) {
       //         cout << "tijd op, tril aan: "<< endl;
                nieuweTrilStatus = 1; // Activeer trilstatus
            }   else if (stopwatch.deTijd() <= 5) {
        //        cout << "tijd over, tril uit: "<< endl;
                nieuweTrilStatus = 0; // Deactiveer trilstatus
            }
        } if(drukSensorWaarde <= 250) {
            // Reset de stopwatch als de druksensorwaarde onder 250 komt
            totaleZitTijd = totaleZitTijd + (stopwatch.deTijd());
    //        cout << "Hank heeft vandaag zoveel seconden gezeten: "<< totaleZitTijd <<endl;
            stopwatch.reset();
            nieuweTrilStatus = 0; // Deactiveer trilstatus
        }
    }

    if(wanneerLevenWe == true){
        if(drukSensorWaarde>250){
            nieuweTrilStatus = 1; // Activeer trilstatus
        } else if(drukSensorWaarde <= 250){
            nieuweTrilStatus = 0;
        }
    }
    
}

int Stoel::getZitTijd(){
    return totaleZitTijd;
}
