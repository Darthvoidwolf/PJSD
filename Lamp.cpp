#include "Lamp.h"

Lamp::Lamp(int id) : Client(id)
{
    setID(id);
}


void Lamp::setID(int a) {
    ID = a;
}

int Lamp::getID() {
    return ID;
}

void Lamp::Noodsituatie(){
    BewegingSenStatus = 1;
    helderheidsNiveau = 200;
    RGBWaarde = 2;
}

void Lamp::verwerkData(const string data, bool nacht, bool noodsituatie) {
 //   cout << "lamp verwerkt data:" << data << endl;
    // Verwerk de ontvangen data specifiek voor Stoel
    sscanf(data.c_str(), "%*s %d %*s %d %*s %d %*s %d %d %d %*s %d", &ID, &bewegingSenWaarde, &brightness, &rood, &groen, &blauw, &bedSwitch);
    wanneerLevenWe = nacht;
    Nood = noodsituatie;
    //   cout << ID << "venster: "<< Venster << "ldr: "<< LDR << "pot: :"<< Pot << "brightr: "<<brightness << rood << groen << blauw << endl;


}
void Lamp::logica()
{

    if (wanneerLevenWe == true && Nood == false)
    {
          Nacht(bewegingSenWaarde);
 //       cout << "DOverdag Lamp: " << endl;
    }
    else if (wanneerLevenWe == false && Nood == false)
    {
      
        Overdag(bewegingSenWaarde);
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

void Lamp::setResponseBuffer()
{

    ostringstream oss;
    oss << "ID: " << ID
        << " BewegingsWaarde: " << BewegingSenStatus
        << " helderheidsniveau: " << helderheidsNiveau
        << " RGBWaarde: " << RGBWaarde
        << " } \n";

    response = oss.str();


    // MET BUFFER OVERFLOW CHECK
    // Server sends ID, command, and whether the druksensor is pressed back to the client
    // printf("Hij is in functie response\n");
    // sprintf(responseBuffer,"ID: %d VensterCommand: %d Helderheidsniveau: %d RGBWaarde %d ",ID, commandVenster, helderheidsniveau, RGBWaarde);
    // printf("Dit is responsebufferMuur: %s", responseBuffer);
    // Note: Do not call send here; leave it to the Server class to handle sending.


}
string Lamp::getResponseBuffer()
{
    //  cout << "getResponseBuffer Muur : " << response << endl;
    return response;
}


void Lamp::Overdag(int bewegingSenWaarde) {
    if (stopwatch.isLopend()) {
        if (stopwatch.deTijd() < 10) {
   //         cout << "Verstreken tijd van bed lamp/schemer lamp: " << stopwatch.deTijd() << " seconden" << endl;
  //          cout << "Schemerlamp & bedlamp is aan" << endl;
            BewegingSenStatus = 1;
            helderheidsNiveau = 200;
            RGBWaarde = 4;
        }
        else if (stopwatch.deTijd() >= 10) {
 //           cout << "Tijd over, schemerlamp en bedlamp uit " << endl;
            helderheidsNiveau = 0;
            RGBWaarde = 0;
            stopwatch.stop();
            stopwatch.reset();
        }
    }

    else if (((bewegingSenWaarde == 1) || (bedSwitch == 1)) && !stopwatch.isLopend()) {
    //else if ((bewegingSenWaarde == 1) || (bedSwitch == 1)) {
   //         cout << "Stopwatch gestart" << endl;
            stopwatch.begin();
    }

    else {
        BewegingSenStatus = 0;
        helderheidsNiveau = 0;
        RGBWaarde = 0;
  //      printf("Geen beweging gedetecteerd\n");
    }
}

void Lamp::Nacht(int bewegingSenWaarde) {
    if (stopwatch.isLopend()) {
        if (stopwatch.deTijd() < 10) {
  //          cout << "Schemerlamp & bedlamp is aan" << endl;
     //       cout << "Verstreken tijd van bed lamp/schemer lamp: " << stopwatch.deTijd() << " seconden" << endl;
            BewegingSenStatus = 1;
            helderheidsNiveau = 75;
            RGBWaarde = 5;
        }
        else if (stopwatch.deTijd() >= 10) {
      //      cout << "Tijd over, schemerlamp en bedlamp uit " << endl;
            helderheidsNiveau = 0;
            RGBWaarde = 0;
            stopwatch.stop();
            stopwatch.reset();
        }
    }

    else if (((bewegingSenWaarde == 1) || (bedSwitch == 1)) && !stopwatch.isLopend()) {
    //else if ((bewegingSenWaarde == 1) || (bedSwitch == 1)) {
        //    cout << "Stopwatch gestart" << endl;
            stopwatch.begin();
    } 
    
    else {
        BewegingSenStatus = 0;
        helderheidsNiveau = 0;
        RGBWaarde = 0;
   //     printf("Geen beweging gedetecteerd\n");
    }
}


    

       
        

