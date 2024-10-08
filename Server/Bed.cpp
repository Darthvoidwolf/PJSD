#include "Bed.h"

/*Bed::Bed(Led* a, Switch* b, Druksensor* c) : led1(a), switch1(b), druksensor1(c) {

}*/



Bed::Bed(int id) : Client(id)
{
    setID(id);
}



Bed::~Bed() {

}

void Bed::setID(int a) { //ID = a
    ID = a;
}

int Bed::getID() {
    return ID;
}

void Bed::Overdag(int SwitchWaarde, int LedWaarde, int DruksensorWaarde) {
    if ((SwitchWaarde == 1) && (LedWaarde == 0) && (DruksensorWaarde > 600)) {
        bepaalSchemerLEDStatus();
        DruksensorStatus = 1;
 //       cout << "Switch wordt gedrukt, led gaat aan, DRUK 1" << endl;
    }
    else if ((SwitchWaarde == 1) && (LedWaarde == 0) && (DruksensorWaarde < 600)) {
        bepaalSchemerLEDStatus();
        DruksensorStatus = 0;
 //       cout << "Switch wordt gedrukt, led gaat aan, DRUK 0" << endl;
    }
    else if ((SwitchWaarde == 1) && (LedWaarde == 1) && (DruksensorWaarde > 600)) {
        LedStatus = 0;
        SwitchStatus = 0;
        DruksensorStatus = 1;
 //       cout << "Switch wordt gedrukt, led gaat uit, DRUK 1" << endl;
    }
    else if ((SwitchWaarde == 1) && (LedWaarde == 1) && (DruksensorWaarde < 600)) {
        LedStatus = 0;
        SwitchStatus = 0;
        DruksensorStatus = 0;
  //      cout << "Switch wordt gedrukt, led gaat uit, DRUK 0" << endl;
    }
    else if ((SwitchWaarde == 0) && (LedWaarde == 0) && (DruksensorWaarde > 600)) {
        LedStatus = 0;
        SwitchStatus = 0;
        DruksensorStatus = 1;
 //       cout << "Switch wordt NIET gedrukt, led blijft uit, DRUK 1" << endl;
    }
    else if ((SwitchWaarde == 0) && (LedWaarde == 0) && (DruksensorWaarde < 600)) {
        LedStatus = 0;
        SwitchStatus = 0;
        DruksensorStatus = 0;
    //    cout << "Switch wordt NIET gedrukt, led blijft uit, DRUK 0" << endl;
    }
    else if ((SwitchWaarde == 0) && (LedWaarde == 1) && (DruksensorWaarde > 600)) {
        bepaalSchemerLEDStatus();
        DruksensorStatus = 1;
//        cout << "Switch wordt NIET gedrukt, led blijft aan, DRUK 1" << endl;
    }
    else if ((SwitchWaarde == 0) && (LedWaarde == 1) && (DruksensorWaarde < 600)) {
        bepaalSchemerLEDStatus();
        DruksensorStatus = 0;
 //       cout << "Switch wordt NIET gedrukt, led blijft aan, DRUK 0" << endl;
    }
}

void Bed::Nacht(int SwitchWaarde, int LedWaarde, int DruksensorWaarde) {
    if ((SwitchWaarde == 1) && (LedWaarde == 0) && (DruksensorWaarde > 600)) {
        bepaalSchemerLEDStatus();
        DruksensorStatus = 1;
 //       cout << "Switch wordt gedrukt, led gaat aan, DRUK 1" << endl;
    }
    else if ((SwitchWaarde == 1) && (LedWaarde == 0) && (DruksensorWaarde < 600)) {
        bepaalSchemerLEDStatus();
        DruksensorStatus = 0;
 //       cout << "Switch wordt gedrukt, led gaat aan, DRUK 0" << endl;
    }
    else if ((SwitchWaarde == 1) && (LedWaarde == 1) && (DruksensorWaarde > 600)) {
        LedStatus = 0;
        SwitchStatus = 0;
        DruksensorStatus = 1;
 //       cout << "Switch wordt gedrukt, led gaat uit, DRUK 1" << endl;
    }
    else if ((SwitchWaarde == 1) && (LedWaarde == 1) && (DruksensorWaarde < 600)) {
        LedStatus = 0;
        SwitchStatus = 0;
        DruksensorStatus = 0;
 //       cout << "Switch wordt gedrukt, led gaat uit, DRUK 0" << endl;
    }
    else if ((SwitchWaarde == 0) && (LedWaarde == 0) && (DruksensorWaarde > 600)) {
        LedStatus = 0;
        SwitchStatus = 0;
        DruksensorStatus = 1;
 //       cout << "Switch wordt NIET gedrukt, led blijft uit, DRUK 1" << endl;
    }
    else if ((SwitchWaarde == 0) && (LedWaarde == 0) && (DruksensorWaarde < 600)) {
        LedStatus = 0;
        SwitchStatus = 0;
        DruksensorStatus = 0;
  //      cout << "Switch wordt NIET gedrukt, led blijft uit, DRUK 0" << endl;
    }
    else if ((SwitchWaarde == 0) && (LedWaarde == 1) && (DruksensorWaarde > 600)) {
        bepaalSchemerLEDStatus();
        DruksensorStatus = 1;
 //       cout << "Switch wordt NIET gedrukt, led blijft aan, DRUK 1" << endl;
    }
    else if ((SwitchWaarde == 0) && (LedWaarde == 1) && (DruksensorWaarde < 600)) {
        bepaalSchemerLEDStatus();
        DruksensorStatus = 0;
  //      cout << "Switch wordt NIET gedrukt, led blijft aan, DRUK 0" << endl;
    }
}

void Bed::Noodsituatie(){
        LedWaarde = 1;
}

int Bed::getLedStatus() {
    return LedStatus;
}

int Bed::getSwitchStatus() {
    return SwitchStatus;
}

int Bed::getDruksensorStatus() {
    return DruksensorStatus;
}

void Bed::logica()
{
    if (wanneerLevenWe == true && Nood == false)
    {
        Overdag(SwitchWaarde, LedWaarde, DruksensorWaarde);
    }
    else if (wanneerLevenWe == false && Nood == false)
    {
        Nacht(SwitchWaarde, LedWaarde, DruksensorWaarde);
    }
    else if (Nood == true)
    {
        Noodsituatie();
    }
    else {
        cout << "Error geen goede tijd" << endl;
    }
    setResponseBuffer();
}

void Bed::setResponseBuffer()
{

    ostringstream oss;
    oss << "ID: " << ID
        << " Led: " << LedStatus
        << " DruksensorIngedrukt: " << DruksensorStatus
        << " } \n";

    response = oss.str();
}
string Bed::getResponseBuffer()
{
    //  cout << "getResponseBuffer Muur : " << response << endl;
    return response;
}


void Bed::verwerkData(const string data, bool nacht, bool noodsituatie) {
    //  cout<<"muur verwerkt data:"<< data <<endl;
      // Verwerk de ontvangen data specifiek voor Stoel
    sscanf(data.c_str(), "%*s %d %*s %d %*s %d %*s %d", &ID, &SwitchWaarde, &LedWaarde, &DruksensorWaarde);
    wanneerLevenWe = nacht;
    Nood = noodsituatie;
}

void Bed::bepaalSchemerLEDStatus() { //LAMP LED
    if (stopwatch.deTijd() <= 10) {
 //       cout << "Verstreken tijd van schemerlamp: " << stopwatch.deTijd() << " seconden" << endl;
    }
    
    // de knop is ingedrukt
    if (!stopwatch.isLopend()) {
        stopwatch.begin();
    }

    if (stopwatch.deTijd() < 10) {
//        cout << "Schemerlamp & bedlamp is aan" << endl;
        SwitchStatus = 1;
        LedStatus = 1;
    }
    else if (stopwatch.deTijd() >= 10) {
  //      cout << "Tijd over, schemerlamp en bedlamp uit " << endl;
        SwitchStatus = 0; // Deactiveer trilstatus
        LedStatus = 0;
        stopwatch.stop();
        stopwatch.reset();
    }
}
    
