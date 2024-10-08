#include "CheckDagNachtNood.h"

CheckDagNachtNood::CheckDagNachtNood() {
    // Initialize any members or perform any setup here
    isDag = true;
    isNood = false;
}
CheckDagNachtNood::CheckDagNachtNood(int id) : Client(id) {
//    std::cout << "clientPi ID:" << ID << std::endl;
    setID(id);
}

CheckDagNachtNood::~CheckDagNachtNood() {

}

int CheckDagNachtNood::getID()
{
    return ID;
}

void CheckDagNachtNood::setID(int a) {
    ID = a;
}

void CheckDagNachtNood::verwerkData(const string data, bool nacht, bool noodsituatie) {
    cout << "clientPi verwerkt data" << endl;
    sscanf(data.c_str(), "%*s %u %*s %u %*s %u", &ID, &checkisDag, &checkisNood);
    
}

void CheckDagNachtNood::setResponseBuffer() {
    cout << "clientPi: antwoord aan het samenstellen" << endl;

    bepaalDagNachtStatus();
    bepaalNoodStatus();

    ostringstream oss;
    oss << "ID: " << ID
        << " isDag: " << isDag
        << " isNood: " << isNood;

    responseBuffer = oss.str();
    cout << responseBuffer << endl;
}

string CheckDagNachtNood::getResponseBuffer() {
    cout << "clientPi: Dit is mijn ResponseBuffer: " << responseBuffer << endl;
    return responseBuffer;
}

bool CheckDagNachtNood::bepaalDagNachtStatus() {
    if (checkisDag == 1  && checkisNood == 0)
    {
        isDag = true;
        cout << "hetisdag" << endl;
        return isDag;
    }
    else if (checkisDag == 0  && checkisNood == 0)
    {
        isDag = false;
        cout << "hetisnacht" << endl;
        return isDag;
    }
    else if(checkisDag == 2)
    {
        cout << " er veranderd niks" << endl;
        return isDag;
    }
    else{
        cout << " error CheckDagNachtNood out off scope" << endl;
        return  0;
    }
}

bool CheckDagNachtNood::bepaalNoodStatus() {
    if (checkisNood == 1)
    {
        isNood = true;
        cout << "brand" << endl;
        return isNood;
    }
    else if (checkisNood == 0)
    {
        isNood = false;
        cout << "veilig" << endl;
        return isNood;
    }

     else{
        cout << " error CheckDagNachtNood out off scope" << endl;
        return 0;
     }
     
}

void CheckDagNachtNood:: logica()
{
        
        setResponseBuffer();
}
/*
void CheckDagNachtNood::responseClient(char* responseBuffer)
{
    if (isNood) {
        sprintf(responseBuffer, "ID: %d isDag: %d isNood: %d \n", ID, isDag, isNood);
        printf("Dit is responsebufferPiClient %s", responseBuffer);
    }
    else if (!isDag) {
        sprintf(responseBuffer, "ID: %d isDag: %d isNood: %d \n", ID, isDag, isNood);
        printf("Dit is responsebufferPiClient %s", responseBuffer);
    }
    else if (isDag) {
        sprintf(responseBuffer, "ID: %d isDag: %d isNood: %d \n", ID, isDag, isNood);
        printf("Dit is responsebufferPiClient %s", responseBuffer);
    }

    //Server sends ID, isDay status back
    //sprintf(responseBuffer, "ID: %d isDag: %d isNood: %d\n", ID, isDag, isNood);
    //printf("Dit is responsebufferPiClient %s", responseBuffer);
}

void CheckDagNachtNood::setDagNachtStatus(int status) {
    // Set the day/night status from the client
    //printf("functie haalllo \n");
    if (status == 1)
    {
        isDag = true;
    }
    else if (status == 0)
    {
        //printf("false ahhaha status: %d\n", status);
        isDag = false;
    }

}

bool CheckDagNachtNood::checkDayNightLogic() const {
    // Implement your specific logic here (based on isDay variable)
    return isDag;
}


void CheckDagNachtNood::setNoodStatus(int statusNood) {
    if (statusNood == 1)
    {
        isNood = true;
    }
    else if (statusNood == 0)
    {
        isNood = false;
    }
}

bool CheckDagNachtNood::checkNoodLogic() const {
    // Implement your specific logic here (based on isDay variable)
    return isNood;
}*/
