#include "Controller.h"

    Controller::Controller(vector<Client*>& apparaten):apparaten(apparaten){
       // std::cout << "Controller aangemaakt " << std::endl;
    }
  
    Controller::~Controller(){

    }

    void Controller::printVectorLijst(){
        for (Client* c : apparaten){
            cout<<"het id is:" <<c->getID()<< endl;
        }
    }

    void Controller::findID(string buffer){ 
        recieveBuffer = buffer; 
        sscanf(buffer.c_str(), "%*s %u ", &OntvangenClientID);
        
        if(OntvangenClientID == 1 )
        {
            saveValueBed(buffer);
        }
        else if(OntvangenClientID == 3)
        {
            connectieBedLamp();
        }
        else if(OntvangenClientID == 6)
        {
           //noodsituatie= getbranddetectie();
        }

        
     //   cout << "RecieveBuffer in findIDController: " << recieveBuffer << "ontvangenClientID: " << OntvangenClientID << endl << endl;
    }
    void Controller :: connectieBedLamp()
    {
        
            recieveBuffer = recieveBuffer + opgeSlagenStringLamp;
        //    cout << "Dit is recieve buffer nadat bed aanpast: " << recieveBuffer << endl;
    }

    void Controller :: saveValueBed(string buffer)
    {
        
        opgeSlagenStringLamp = buffer;
            sscanf(buffer.c_str(), "%*s %*u %*s %d", &opslagBedLamp);

            ostringstream oss;
            oss << " opslagBedLamp: " <<opslagBedLamp;
            opgeSlagenStringLamp = oss.str();
    }
    void Controller::findClient(){
        int idTeVinden = OntvangenClientID;
        
      //  for (Client* c : apparaten){
            for(int i=0; i<apparaten.size(); i++)
            {
                    if(apparaten.at(i)->getID() == idTeVinden){
                        /// is gevonden
                    //    cout<<"het id is gevonden: "<< apparaten.at(i)->getID() << endl;

                        apparaten.at(i)->verwerkData(recieveBuffer, nacht, noodsituatie);
                        cout << "nacht controll :" << nacht << endl;
                        apparaten.at(i)->logica();
                        responseBuffer = apparaten.at(i)->getResponseBuffer();
                    
                        if(apparaten.at(i)->getID() == 6)
                        {
                            
                            PiClient(responseBuffer);
                        }
                        if(apparaten.at(i)->getID() == 0)
                        {
                            //noodsituatie = getBrandDetectie();
                            
                        }
                        // hier aanroep voor piCLient
                   //     cout << "ResponseBufferFindClientCotnroller : " << responseBuffer << endl;
                }
                
            }
          
        }
  

    string Controller::getClientResponseBuffer(){
        return responseBuffer;
    }

    bool Controller :: getNoodStatus()
    {
        return noodsituatie;
    }
    void Controller:: setClientResponseBuffer(string response)
    {
        responseBuffer = response;
    }
    
    
    

    void Controller :: PiClient(string responseBuffer)
    {

      //  sscanf(responseBuffer.c_str(), "%*s %u ", &OntvangenClientID); Dit is al gebeurd

      ostringstream oss;
            oss << " zuilRookmelder: " <<rookDetectie 
         //   << " bedTimer: " <<bedTimer
            << " stoelTimer: " << stoelTimer
            << " lampTimer: " << lampTimer
            << " deurStatus: " << deurStatus
            << "}\n";

            responsePiClient = oss.str();
            responseBuffer = responseBuffer + responsePiClient;
            setClientResponseBuffer(responseBuffer);
        cout <<"Dit is aangepast responseBuffer voor piclient: " << responseBuffer << endl;
    }

bool Controller :: getBrandDetectie()
{
    bool status = false ;
    for(Client* c : apparaten)
    {
        Zuil* zuil = dynamic_cast<Zuil*>(c);
        if(zuil)
        {
            status = zuil->getNoodStatus();
        }
    
    }
    rookDetectie = status;
    return status;
}
    

void Controller :: zitTijd()
{
    int tijd =0;
    for(Client* c : apparaten)
    {
        Stoel* stoel = dynamic_cast<Stoel*>(c);
        


        if(stoel)
        {
            tijd = stoel->getZitTijd();

        }
       
    }
   stoelTimer = tijd;
}


void Controller :: deurTijd()
{
    int tijd =0;
    for(Client* c : apparaten)
    {
        Deur* deur = dynamic_cast<Deur*>(c);
        


        if(deur)
        {
           // tijd = deur->getZitTijd();

        }
       
    }
   deurStatus = tijd;
}


