#include <ESP8266WiFi.h>
#include <Wire.h>

#define I2C_SDL    D1
#define I2C_SDA    D2

void configureInputOutput();
unsigned int checkKnopIngedrukt();
unsigned int checkLEDWaarde();
unsigned int checkTrilWaarde();
unsigned int checkDrukSensor();
void zetLichtAan();
void zetLichtUit();
void zetTrilAan();
void zetTrilUit();
void sendKeyValues();

unsigned int outputs = 0;
int IDWaarde, knopWaarde, LEDWaarde, TrilWaarde, DrukWaarde;
char responsebuffer[1024];
char antwoordbuffer[1024];
/*const char *ssid = "hotspot laptop dcg";
const char *password = "dcg2002H";
const char* serverIp = "192.168.137.32"; // Vervang dit met het IP-adres van jouw server
const int serverPort = 8080;*/
const char *ssid = "Doovensmirt_access";
const char *password = "7iezbkbd";
const char* serverIp = "192.168.4.1"; // Vervang dit met het IP-adres van jouw server
const int serverPort = 8080;

WiFiClient client;

void setup() {
  zetLichtAan();
  pinMode(D5, OUTPUT);   // Configureer pin D5 als uitvoer voor het bedienen van de MOSFET
  Wire.begin();          // Initialiseer de I2C-communicatie
  Serial.begin(115200);  // Initialiseer seriële communicatie voor debugging


  configureInputOutput();

  // Maak verbinding met Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Verbinding maken met WiFi...");
  }
  Serial.println("Verbonden met WiFi");
}

void loop() {
  // Maak verbinding met de server
  if (!client.connected()) {
    Serial.println("Verbinding maken met de server...");

    if (client.connect(serverIp, serverPort)) {
      Serial.println("Verbonden met de server");
    } else {
      Serial.println("Verbindingsfout. Opnieuw proberen...");
      delay(5000);
      return;
    }
  }

  
  //zetLichtAan();
  // Verstuur de key values naar de server
  sendKeyValues();
  /*if (client.availableForWrite()) {
      char buffer[1024];
      memset(buffer, 0, sizeof(buffer));
      //sprintf(buffer,"ID: %d", IDWaarde);
      sprintf(buffer, "ID: 2 Push_Button: 0 LED: 0 Tril: 0 Druk_sensor: 0");
      client.write(buffer);
    }*/

  
  // Controleer op inkomende gegevens van de server
  String response = client.readStringUntil('}');
  
  size_t antwoordVanServer = response.length();
  response.toCharArray(antwoordbuffer, antwoordVanServer + 1);

  sscanf(antwoordbuffer, "%*s %d %*s %d %*s %d %*s %d %*s %d", &IDWaarde, &knopWaarde, &LEDWaarde, &TrilWaarde, &DrukWaarde);
  Serial.println("Ontvangen van de server: ");
  Serial.println(antwoordbuffer);
  Serial.println(LEDWaarde);
  client.stop();
  delay(100);
  
  if(LEDWaarde == 1){
    zetLichtAan();
    delay(50);
  } if(LEDWaarde == 0){
    zetLichtUit();
    delay(50);
  }

  if(TrilWaarde == 1){
    zetTrilAan();
    delay(50);
  } if(TrilWaarde == 0){
    zetTrilUit();
    delay(50);
  }
}

unsigned int checkKnopIngedrukt() {
  unsigned int stoelKnopInput;
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x00)); // Specificeer het registeradres van de uitgang die je wilt lezen
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1); // Vraag één byte op van het gespecificeerde registeradres
  Wire.endTransmission();

  if (Wire.available()) { // Controleer of er gegevens beschikbaar zijn
    stoelKnopInput = Wire.read() & 0b00000001; // Lees de waarde van de specifieke uitgang
  }

  return stoelKnopInput;
}

unsigned int checkLEDWaarde() {
  unsigned int LEDWaarde = 0;
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x00)); // Specificeer het registeradres van de uitgang die je wilt lezen
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1); // Vraag één byte op van het gespecificeerde registeradres

  if (Wire.available()) { // Controleer of er gegevens beschikbaar zijn
    LEDWaarde = Wire.read() & 0b00010000; // Lees de waarde van de specifieke uitgang
  }
  if (LEDWaarde == 16) {
    return 1;
  } else {
    return 0;
  }
}

unsigned int checkTrilWaarde() {
  unsigned int TrilWaarde = 0;
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x00)); // Specificeer het registeradres van de uitgang die je wilt lezen
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1); // Vraag één byte op van het gespecificeerde registeradres

  if (Wire.available()) { // Controleer of er gegevens beschikbaar zijn
    TrilWaarde = Wire.read() & 0b00100000; // Lees de waarde van de specifieke uitgang
  }
  if (TrilWaarde == 32) {
    return 1;
  } else {
    return 0;
  }
}

unsigned int checkDrukSensor() {
  unsigned int AnalogeWaarde = 0;

  Wire.requestFrom(0x36, 4);
  unsigned int anin0 = Wire.read() & 0x03;
  anin0 = anin0 << 8;
  anin0 = anin0 | Wire.read();
  
  AnalogeWaarde = anin0;
  return AnalogeWaarde;
}

void zetLichtAan() {
  Wire.beginTransmission(0x38);
  Wire.write(0x01); // Registeradres voor PCA9554-uitgangsregisters
  Wire.endTransmission();

  Wire.requestFrom(0x38, 1); // Vraag één byte op van het gespecificeerde registeradres

  if (Wire.available()) {
    unsigned int output = Wire.read() & 0b11110000;
    output |= 0x10; // Zet het 5e bit (bit 4) op 1 om het licht aan te zetten

    Wire.beginTransmission(0x38);
    Wire.write(0x01); // Registeradres voor PCA9554-uitgangsregisters
    Wire.write(output);
    Wire.endTransmission();

    Serial.println("Licht staat aan");
  } else {
    Serial.println("Fout bij het lezen van de uitgangswaarde");
  }
}


void zetLichtUit() {
  Wire.beginTransmission(0x38);
  Wire.write(0x01); // Registeradres voor PCA9554-uitgangsregisters
  Wire.endTransmission();

  Wire.requestFrom(0x38, 1); // Vraag één byte op van het gespecificeerde registeradres

  if (Wire.available()) {
    unsigned int output = Wire.read();
    output &= 0xEF; // Zet het 5e bit (bit 4) op 0 om het licht uit te zetten

    Wire.beginTransmission(0x38);
    Wire.write(0x01); // Registeradres voor PCA9554-uitgangsregisters
    Wire.write(output);
    Wire.endTransmission();

    Serial.println("Licht staat uit");
  } else {
    Serial.println("Fout bij het lezen van de uitgangswaarde");
  }
}


void zetTrilAan() {
  Wire.beginTransmission(0x38);
  Wire.write(0x01); // Registeradres voor PCA9554-uitgangsregisters
  Wire.endTransmission();

  Wire.requestFrom(0x38, 1); // Vraag één byte op van het gespecificeerde registeradres

  if (Wire.available()) {
    unsigned int output = Wire.read();
    output |= 0x20; // Zet het 6e bit op 1 om de tril aan te zetten

    Wire.beginTransmission(0x38);
    Wire.write(0x01); // Registeradres voor PCA9554-uitgangsregisters
    Wire.write(output);
    Wire.endTransmission();

    Serial.println("Tril staat aan");
  } else {
    Serial.println("Fout bij het lezen van de uitgangswaarde");
  }
}


void zetTrilUit() {
  Wire.beginTransmission(0x38);
  Wire.write(0x01); // Registeradres voor PCA9554-uitgangsregisters
  Wire.endTransmission();

  Wire.requestFrom(0x38, 1); // Vraag één byte op van het gespecificeerde registeradres

  if (Wire.available()) {
    unsigned int output = Wire.read();
    output &= 0xDF; // Zet het 5e bit (bit 4) op 0 om de tril uit te zetten

    Wire.beginTransmission(0x38);
    Wire.write(0x01); // Registeradres voor PCA9554-uitgangsregisters
    Wire.write(output);
    Wire.endTransmission();

    Serial.println("Tril staat uit");
  } else {
    Serial.println("Fout bij het lezen van de uitgangswaarde");
  }
}

void sendKeyValues() {
  unsigned int IDWaarde = 2;
  unsigned int knopWaarde = checkKnopIngedrukt();
  unsigned int LEDWaarde = checkLEDWaarde();
  unsigned int TrilWaarde = checkTrilWaarde();
  unsigned int DrukWaarde = checkDrukSensor();

  if (client.availableForWrite()) {
    char buffer[1024];
    memset(buffer, 0, strlen(buffer));
    //sprintf(buffer,"ID: %d", IDWaarde);
    sprintf(buffer, "ID: %u Push_Button: %u LED: %u Tril: %u Druk_sensor: %u", IDWaarde, knopWaarde, LEDWaarde, TrilWaarde, DrukWaarde);
    client.write(buffer);
  }
}

void configureInputOutput() {
  // Configure PCA9554: Set IO0-IO3 as input, IO4-IO7 as output
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x03));
  Wire.write(byte(0x0F));
  Wire.endTransmission();

  // Set PCA9554 outputs (IO4-IO7)
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x01));
  Wire.write(byte(outputs << 4));
  Wire.endTransmission();
  Serial.print("Digitale uitgang: ");
  Serial.println(outputs & 0x0F);

  // Configure MAX11647: Set configuration byte for analog inputs
  Wire.beginTransmission(0x36);
  Wire.write(byte(0xA2));
  Wire.write(byte(0x03));
  Wire.endTransmission();
}
