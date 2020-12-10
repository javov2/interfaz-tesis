#include <TinyGPS.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>
#include <RTClib.h>
#include <SPI.h>    
#include <SdFat.h>     

#define SSpin 53    

void iPrincipalMenu();
int GetSystemParameters(int currentInterface, int sampleRate, int numberOfSensors);
String dateTime;

const int NUMBERS_OF_SENSORS_ALLOWED = 5;

LiquidCrystal_I2C lcd(0x3F, 16, 2);
RTC_DS1307 RTC;
TinyGPS GPS;
File fileObject;
SdFat SD;

const byte rowsCount = 4;
const byte columsCount = 4;

char keys[4][4] = {
   { '1','2','3', 'A' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '*','0','#', 'D' }
};
 
const byte rowPins[4] = { 29, 31, 33, 35 };
const byte columnPins[4] = { 37, 39, 41, 43 };

Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);

const int pinMapArray[NUMBERS_OF_SENSORS_ALLOWED] = {A5,A4,A0,A1,A2};
int availableSensors[NUMBERS_OF_SENSORS_ALLOWED];

bool Screen = true; 
int samplingRate = 0;
int numberOfSensors = 0;
bool SDStatus = true;
float latitude, longitude;
unsigned long age = 0;
String txtString=".txt";
String newFile;


void setup() {

  RTC.begin();
  Serial.begin(9600);
  Serial3.begin(9600);

  Serial.println("TESTING...");
  lcd.init();
  lcd.backlight();
  
  String dateTime = GetTime(1); 
  newFile = dateTime + txtString;
  Serial.println(newFile);

}

void loop() {

int currentInterface = 0;

while(Screen){

  while (currentInterface == 0 && Screen == true){
    iSDDiagnostic(); 
    currentInterface = currentInterface + 10;
  }
  
  while (currentInterface == 10 && Screen == true) { 
  String dateTime = GetTime(0);  iPrincipalMenu(dateTime); char KeyP = keypad.getKey(); 
  if (KeyP){currentInterface=ChangeInterface(currentInterface,KeyP);}
  }
  
  while (currentInterface == 20 && Screen == true) { 
  int aux = GetSystemParameters(currentInterface, samplingRate, numberOfSensors);
  Serial.print("Frecuencia de muestreo: "); Serial.print(aux); Serial.println(" minutos");
  samplingRate = aux*1000;
  currentInterface = currentInterface + 10;}

  while (currentInterface == 30 && Screen == true) { 
  int aux = GetSystemParameters(currentInterface, samplingRate, numberOfSensors);
  Serial.print("Numero de sensores: "); Serial.println(aux);
  numberOfSensors = aux;
  for (int i=0; i<numberOfSensors; i++){
    availableSensors[i]=pinMapArray[i];
  }
  currentInterface = currentInterface + 10;}

  while (currentInterface == 40 && Screen == true) {
  getGPS(); iGPSDiagnostic(latitude,longitude); char KeyP = keypad.getKey();
  if (KeyP){currentInterface=ChangeInterface(currentInterface,KeyP);}}

  while (currentInterface == 50 && Screen == true) {
  iSensorsDiagnostic(numberOfSensors); char KeyP = keypad.getKey();
  currentInterface = 60;
  }

  while (currentInterface == 60 && Screen == true) {
  iCredits(); char KeyP = keypad.getKey();
  if (KeyP){currentInterface=ChangeInterface(currentInterface,KeyP);}
  }

  while (currentInterface == 70 && Screen == true) {
  iSystemReady(); char KeyP = keypad.getKey();
  if (KeyP){currentInterface=ChangeInterface(currentInterface,KeyP);}
  }
  
  fileObject = SD.open(newFile, FILE_WRITE);
  SDCardPrintHeaders(fileObject);
  
  }

  fileObject = SD.open(newFile, FILE_WRITE);
  SDCardSaveData(fileObject);
  delay(samplingRate);

}
