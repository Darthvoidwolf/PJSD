#include "Muur.h"
Muur::Muur(int id) : Client(id)
{
   //     std::cout << "Muur constructor en ID: " << id << std::endl;
    setID(id);
  //  cout << "Contructor Muur: " << endl;
    // ... rest of the default constructor code ...
}

void Muur::setID(int a){
 //   printf("Muur klasse setID\n");
    ID = a;
  //  cout <<"Aangemaakt ID: " << ID << endl;
   // printf("Muur klasse setID 2\n");
}

void Muur::Overdag(int VensterCommand,int LDR, int Pot)
{
    commandVenster = 0;
    RGBWaarde = 4;
            
    if(LDR > 200 && LDR < 450 && Pot <= 200){
        helderheidsniveau =50;
       // printf("heel donker\n");
    }
    else if(LDR <= 200 && Pot <= 100){
        helderheidsniveau =100;
       // printf("beetje donker\n");
        }
    else if (LDR > 450 && LDR < 750 && Pot <= 250){
        helderheidsniveau =0;
       // printf("niet donker\n");
        }
    else if (LDR > 750 && Pot <= 250){
        commandVenster =1;
        helderheidsniveau = 75;
     //   printf("HEt is te vel HELPPPPPP\n");
        }
    else {
        helderheidsniveau = (Pot /4) -50;
       // printf("Hij is nu al in de else\n");
        }
      //  printf("OVerdagfucntie: ID:%d  commandvenster%d LDR%d helderheidsniveau%d\n", ID,commandVenster,LDR, helderheidsniveau);
}

void Muur::Nacht(int Pot)
{
       
            commandVenster =1;
            RGBWaarde = 5;
            helderheidsniveau = (Pot /4);
            // functie dat als hij weer in bed gaat liggen dat dan de lichten weer uit gaat als hij het vergeten is

}

void Muur::Noodsituatie()
{
        if(!stopwatch.isLopend())
        {
            stopwatch.begin();
            commandVenster = 0;
            helderheidsniveau = 255;
            RGBWaarde = 4;
        }
        else if(stopwatch.deTijd() % 2 != 0)
        {
            commandVenster = 0;
            helderheidsniveau = 0;
            RGBWaarde = 4;
           
        }
        else if(stopwatch.deTijd() % 2 == 0)
        {
            commandVenster = 0;
            helderheidsniveau = 255;
            RGBWaarde = 4;
        }

            
            // nog meer voor nood
}

int Muur::getCommandVenster()
{
    return commandVenster;
}

int Muur::getHelderheidsniveau()
{
    return helderheidsniveau;
}

int Muur::getLDR() 
{
    return LDR;
}

int Muur::getID()
{
    return ID;
}

void Muur :: verwerkData(const string data, bool nacht, bool noodsituatie) {
  //  cout<<"muur verwerkt data:"<< data <<endl;
    // Verwerk de ontvangen data specifiek voor Stoel
     sscanf(data.c_str(), "%*s %u %*s %u %*s %u %*s %u %*s %u %*s %u %*s %u %u %u", &ID, &Venster, &LDR, &Pot, &brightness, &rood,&groen, &blauw);
     wanneerLevenWe = nacht;
     Nood = noodsituatie;
    cout << "wanneerleven we muur: " << wanneerLevenWe << endl;
 //   cout << ID << "venster: "<< Venster << "ldr: "<< LDR << "pot: :"<< Pot << "brightr: "<<brightness << rood << groen << blauw << endl;
   
   
}



void Muur :: logica()
{
    if(wanneerLevenWe == true && Nood == false)
    {
       Nacht(Pot);
        stopwatch.stop();
        stopwatch.reset();
    }
    else if(wanneerLevenWe == false && Nood == false)
    {
        
         Overdag(Venster,LDR,Pot);
        
        stopwatch.stop();
        stopwatch.reset();
    }
    else if(Nood == true)
    {
        Noodsituatie();
    }
    else{
        cout << "Error geen goede tijd" << endl;
    }
    setResponseBuffer();
     
}

void Muur :: setResponseBuffer()
{

    ostringstream oss;
    oss << "ID: " << ID 
        << " VensterCommand: " << commandVenster
        << " helderheidsniveau: " << helderheidsniveau
        << " RGBWaarde: " << RGBWaarde
        << " } \n";

     response = oss.str();

     
 //MET BUFFER OVERFLOW CHECK
    //Server sends ID, command, and whether the druksensor is pressed back to the client
  //  printf("Hij is in functie response\n");
   //  sprintf(responseBuffer,"ID: %d VensterCommand: %d Helderheidsniveau: %d RGBWaarde %d ",ID, commandVenster, helderheidsniveau, RGBWaarde);
   //     printf("Dit is responsebufferMuur: %s", responseBuffer);
    // Note: Do not call send here; leave it to the Server class to handle sending.


}
string Muur:: getResponseBuffer()
{
  //  cout << "getResponseBuffer Muur : " << response << endl;
    return response;
}

























/*
void MuurController::responseClient(char* responseBuffer) { //MET BUFFER OVERFLOW CHECK
    //Server sends ID, command, and whether the druksensor is pressed back to the client
    sprintf(responseBuffer, "ID: %d VensterCommand: %d Helderheidsniveau: %d RGBWaarde %d \n }",ID, commandVenster, helderheidsniveau, RGBWaarde);
    // Note: Do not call send here; leave it to the Server class to handle sending.
}*/


/*
MuurController::MuurController(int id, int venster, int ldr, int pot, int bright, int r, int g, int b)
    : ID(id), Venster(venster), LDR(ldr), Pot(pot), brightness(bright), rood(r), groen(g), blauw(b),

      tijddag(false), noodsituatie(false), aanUit(false), commandVenster(0), helderheidsniveau(0), RGBWaarde(0) 
{

}
*/
/*
MuurController::~MuurController()
{

}
*/
/*
void MuurController::responseClient(char* responseBuffer ) { //MET BUFFER OVERFLOW CHECK
    //Server sends ID, command, and whether the druksensor is pressed back to the client
    sprintf(responseBuffer,"ID: %d VensterCommand: %d Helderheidsniveau: %d RGBWaarde %d }", ID, commandVenster, helderheidsniveau, RGBWaarde);
    // Note: Do not call send here; leave it to the Server class to handle sending.
}
*/
/*
void MuurController::responseClient(responseBufferMuur)
{
     sprintf(responseBufferMuur,"ID: %d VensterCommand: %d Helderheidsniveau: %d RGBWaarde %d }",ID, commandVenster, helderheidsniveau, RGBWaarde);
    return responseBufferMuur;
}
void MuurController::Dag(int ID,int Venster, int LDR, int Pot, int brightness, int rood, int groen, int blauw)
{
    commandVenster = 0;
    RGBWaarde = 4;
            
    if(LDR > 200 && LDR < 450 && Pot <= 200){
        helderheidsniveau =50;
       // printf("heel donker\n");
    }
    else if(LDR <= 200 && Pot <= 100){
        helderheidsniveau =100;
       // printf("beetje donker\n");
        }
    else if (LDR > 450 && LDR < 750 && Pot <= 250){
        helderheidsniveau =0;
       // printf("niet donker\n");
        }
    else if (LDR > 750 && Pot <= 250){
        commandVenster =1;
        helderheidsniveau = 75;
     //   printf("HEt is te vel HELPPPPPP\n");
        }
    else {
        helderheidsniveau = (Pot /4) -50;
       // printf("Hij is nu al in de else\n");
        }

    
}

string MuurController::Nacht()
{
            commandVenster =1;
            RGBWaarde = 5;
            helderheidsniveau = (Pot /4);
            // functie dat als hij weer in bed gaat liggen dat dan de lichten weer uit gaat als hij het vergeten is

            sprintf(responseMuur,"ID: %d VensterCommand: %d Helderheidsniveau: %d RGBWaarde %d \n }",ID, commandVenster, helderheidsniveau, RGBWaarde);
            return responseMuur;
}

string MuurController::Noodsituatie()
{
            commandVenster = 0;
            helderheidsniveau = 255;
            RGBWaarde = 4;
            aanUit = false;
            printf("Nood aan\n");


            commandVenster = 0;
            helderheidsniveau = 0;
            RGBWaarde = 4;
            aanUit = true;
            printf("Nood uit\n");

            sprintf(responseMuur,"ID: %d VensterCommand: %d Helderheidsniveau: %d RGBWaarde %d \n }",ID, commandVenster, helderheidsniveau, RGBWaarde);
            return responseMuur;
}
string MuurController::Muur()
{
 
        if(tijddag == true && noodsituatie == false){
            commandVenster = 0;
            RGBWaarde = 4;
            
            if(LDR > 200 && LDR < 450 && Pot <= 200){
                helderheidsniveau =50;
            }
            else if(LDR <= 200 && Pot <= 100){
                helderheidsniveau =100;
            }
            else if (LDR > 450 && Pot <= 250){
                helderheidsniveau =0;
            }
            else if (LDR > 600 && Pot <= 250){
                commandVenster =1;
                helderheidsniveau = 75;
            }
            else {
                helderheidsniveau = (Pot /4) -50;
                printf("Hij is nu al in de else\n");
            }
        }

        if(tijddag == false && noodsituatie == false){
            commandVenster =1;
            RGBWaarde = 5;
            helderheidsniveau = (Pot /4);
            // functie dat als hij weer in bed gaat liggen dat dan de lichten weer uit gaat als hij het vergeten is
        }

        if(noodsituatie == true && aanUit == true){
            commandVenster = 0;
            helderheidsniveau = 255;
            RGBWaarde = 4;
            aanUit = false;
            printf("Nood aan\n");
        }
        else if(noodsituatie == true && aanUit == false){
            commandVenster = 0;
            helderheidsniveau = 0;
            RGBWaarde = 4;
            aanUit = true;
            printf("Nood uit\n");
        }

        sprintf(responseMuur,"ID: %d VensterCommand: %d Helderheidsniveau: %d RGBWaarde %d \n }",ID, commandVenster, helderheidsniveau, RGBWaarde);
        return responseMuur;
    //    send(new_socket,"hoi", strlen("hoi"),0);
        
        
    }
*/