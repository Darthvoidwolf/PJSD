#include "Deur.h"
#include "Clients.h"


Deur::Deur() : Client()
{
   
}

Deur::Deur(int id) : Client(id) {
  //  std::cout << "Deur " << id << std::endl;
    setID(id);
}

Deur::~Deur()
{

}

int Deur::getID()
{
    return ID;
}

void Deur::setID(int a) {
    ID = a;
}

void Deur::verwerkData(const string data, bool nacht, bool noodsituatie) {
 //   cout << "Deur verwerkt data" << endl;
    // Verwerk de ontvangen data specifiek voor Stoel
    sscanf(data.c_str(), "%*s %u %*s %u %*s %u %*s %u %*s %u %*s %u", &ID, &KnopBuiten, &KnopBinnen, &LEDBuiten, &LEDBinnen, &DeurPositie);
    //wanneerLevenWe = nacht;
    //Nood = noodsituatie;
    logica();
}


void Deur::bepaalDeurPositieDag() {
    //commandoDeur = 3;


    //if (KnopBuiten == 1 && DeurPositie == 0) {
    if (KnopBuiten == 1){
        commandoDeur = 3; // 3 = deur open naar Binnen
    //    printf("Deur opent naar binnen -->");
    }
    //else if (KnopBinnen == 2 && DeurPositie == 0) {
    else if (KnopBinnen == 2){
        commandoDeur = 4; // 4 = deur open naar Buiten
   //     printf("Deur opent naar buiten --> ");
    }
   
    // timer om deur dicht te doen
    else if ((DeurPositie == 1 || DeurPositie == 2 && !stopwatch.isLopend()) {
        cout << "Deur moet weer dicht" << endl;
            stopwatch.begin();
    //    cout << "Verstreken tijd2: " << stopwatch.deTijd() << " seconden" << endl;
        // Controleer of de stopwatch langer dan 5 seconden loopt
        if (stopwatch.deTijd() > 5) {
           commandoDeur = 5;
            stopwatch.stop();
            stopwatch.reset();
            
        }

    }
}

void Deur::bepaalDeurPositieNacht() {
    commandoDeur = 5; // deur dicht doen
}

void Deur::bepaalDeurPositieNood() {
    commandoDeur = 3; // deur open naar buiten
}

int Deur::getCommandoDeur()
{
    return commandoDeur;
}

int Deur::getDeurPositie()
{
    return DeurPositie;
}

void Deur::logica() {

    if (wanneerLevenWe == true && Nood == false)// normale situatie overdag
    {
        bepaalDeurPositieNacht();
    }
    else if (wanneerLevenWe == false && Nood == false) // normale situate nacht
    {
        bepaalDeurPositieDag();
    }
    else if (Nood == true)// een noodsituatie
    {
        bepaalDeurPositieNood();
    }
    else {
     //   cout << "Error geen goede tijd" << endl;
    }
    setResponseBuffer();
}

void Deur::setResponseBuffer() {
//    cout << "Deur: antwoord aan het samenstellen" << endl;

    ostringstream oss;
    oss << "ID: " << ID
        << " KnopBuiten: " << KnopBuiten
        << " KnopBinnen: " << KnopBinnen
        << " LEDBuiten: " << NieuwLEDBuiten
        << " LEDBinnen: " << NieuwLEDBinnen
        << " DeurPositie: " << commandoDeur
        << " } \n";

    response = oss.str();
}


string Deur::getResponseBuffer() {

  //  cout << "Deur: Dit is mijn ResponseBuffer: " << responseBuffer << endl;
    return response;
}
