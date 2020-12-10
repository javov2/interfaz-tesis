const byte prevArrow[] = {B00011,B00110,B01100,B11000,B11000,B01100,B00110,B00011}; // <-
const byte nextArrow[] = {B11000,B01100,B00110,B00011,B00011,B00110,B01100,B11000}; // ->
const byte keyIcon[]   = {B00000,B00000,B00011,B00010,B00111,B01100,B11000,B10000};
const byte gpsIcon[]   = {B00000,B11001,B10010,B10100,B10001,B01111,B01000,B11110};
const byte checkIcon[] = {B00000,B00000,B00001,B00011,B10110,B11100,B01000,B00000};

void iSDDiagnostic(){
  int b1 = 0;
  while (b1 == 0) {
    if (!SD.begin(SSpin)) {
      lcd.setCursor(4,0);
      lcd.print("FALLO SD");
      delay(500);
    }
    else {
      fileObject = SD.open(newFile, FILE_WRITE);
      if (fileObject) {
        fileObject.println("Medición de turbidez");
        fileObject.close();
        b1 = 1;
        
      } else {
        lcd.setCursor(4,0);
        lcd.print("ERROR SD");
      }
    }
  }
  lcd.home();
  lcd.setCursor(3,0);
  lcd.print("SD CORRECTA");
  delay(500);
  lcd.clear();
}


int GetSystemParameters(int currentInterface, int sampleRate, int numberOfSensors){

  if( currentInterface==20 ){
  bool OK = false; 
  char NumP[] = {' ', ' ', ' ', ' ', ' ', ' ', ' ',' ',' ', ' ', ' ', ' ', ' ', ' ', ' ',' ',}; 
  int C = 0;
   
  while (OK == false){
    iSamplingRate(NumP);
    char Num = keypad.waitForKey();
    if (Num == '0'||Num == '1'||Num == '2'||Num == '3'||Num == '4'||Num == '5'||Num == '6'||Num == '7'||Num == '8'||Num == '9')
    { 
      NumP[C] = Num;
      iSamplingRate(NumP);
    for (int i=0; i < 1; i++){
      i++; C++;
      }
    }
    else if (Num == 'A') {
      if (C>0){
        NumP[C-1]=' ';
        C=C-1;
      }
      }
    
    else if(Num == 'D'){
      int NumInt = atoi(NumP);
      if (NumInt > 0){
        lcd.clear();
        OK=true;
        return(NumInt);
        }}}}
    
  if( currentInterface==30 ){ 
  bool OK = false;
  char NumP[] = {' ', ' ', ' ', ' ', ' ', ' ', ' ',' ',' ', ' ', ' ', ' ', ' ', ' ', ' ',' ',}; 
  int C = 0;
  
  while (OK == false){
    NumberOfSensors(NumP);
    char Num = keypad.waitForKey();
    if (Num == '0'||Num == '1'||Num == '2'||Num == '3'||Num == '4'||Num == '5'||Num == '6'||Num == '7'||Num == '8'||Num == '9')
    { NumP[C] = Num; NumberOfSensors(NumP);
    for (int i=0; i < 1; i++){ i++; C++;}}
    else if (Num == 'A') { if (C>0){
        NumP[C-1]=' ';
        C=C-1;
      }}
    
    else if(Num == 'D'){
    int NumInt = atoi(NumP);
    if (NumInt > 0 && NumInt <= NUMBERS_OF_SENSORS_ALLOWED){
        lcd.clear(); 
        bool OK2 = false;
        OK=true;
        OK2=true;
        lcd.clear();
        return(NumInt); 
        }
    
    }}}
    }

void iCredits(){
  lcd.setCursor(4, 0);
  lcd.print("CREDITOS");
  lcd.setCursor(3,1); lcd.print("JAVO & GAMC");}

void iNotifications(){
  lcd.setCursor(2, 0);
  lcd.print("ALERTA SD:");
  lcd.setCursor(1, 1);
  lcd.print("NO ENCONTRADA");
  }

void iPrincipalMenu(String dateTime){
  lcd.setCursor(3, 0);
  lcd.print("BIENVENIDO");
  lcd.setCursor(0,1);
  lcd.print(dateTime);
  }

void iAdjustSamplingRateMenu(){
  lcd.createChar(0, prevArrow); lcd.createChar(1, nextArrow);
  lcd.home(); lcd.write(0);
  lcd.setCursor(15,0);  lcd.write(1);
  lcd.setCursor(4, 0);
  lcd.print("AJUSTAR");
  lcd.setCursor(1, 1);
  lcd.print("FREQ MUESTREO:");
  }

void iSensorDiagnostic(int sensorNumber, float sensorValue){
  lcd.createChar(0, keyIcon);
  lcd.home(); lcd.write(0);
  lcd.createChar(1, gpsIcon);
  lcd.setCursor(0,1); lcd.write(1);
  lcd.setCursor(2,0); lcd.print("SENSOR: ");
  lcd.setCursor(11,0); lcd.print(sensorNumber);
  lcd.setCursor(2,1); lcd.print(sensorValue);
  lcd.setCursor(12,1); lcd.print("NTU");}

void iSensorsDiagnostic(int numberOfSensors){

  char sensorsArray[numberOfSensors];
  for (int i=1; i<= numberOfSensors; i++){
    sensorsArray[i-1]=(i);
  }

  int sensorCounter = 0;

  while(sensorCounter < numberOfSensors){
    float sensorValue = GetSensorValue(availableSensors[sensorCounter]);
    iSensorDiagnostic(sensorsArray[sensorCounter], sensorValue);
    char Num = keypad.getKey();
    if (Num == 'D'){ sensorCounter++; lcd.clear();}
  }}

void iGPSDiagnostic(float latitude, float longitude){
  lcd.createChar(0, keyIcon);
  lcd.home(); lcd.write(0);
  lcd.createChar(1, gpsIcon);
  lcd.setCursor(0,1); lcd.write(1);
  lcd.setCursor(2,0); lcd.print("Lat:"); 
  lcd.setCursor(7,0); lcd.print(latitude,4);
  lcd.setCursor(2,1); lcd.print("Lon:");
  lcd.setCursor(7,1); lcd.print(longitude,4);}
void iSystemReady(){
  lcd.createChar(0,checkIcon); lcd.setCursor(13, 0); lcd.write(0);
  lcd.setCursor(4, 0);
  lcd.print("SISTEMA");
  lcd.setCursor(2,1); lcd.print("CONFIGURADO");}

void iSamplingRate(char sampleRate[16]){
  lcd.setCursor(0,0); lcd.print("FREC DE MUESTREO"); 
  lcd.setCursor(4,1); lcd.print(sampleRate); lcd.setCursor(8,1); lcd.print("min");}

void NumberOfSensors(char numberOfSensors[16]){
  lcd.setCursor(1,0); lcd.print("# DE SENSORES"); 
  lcd.setCursor(7,1); lcd.print(numberOfSensors);}

int ChangeInterface(int currentInterface, char keyPressed){

  if (currentInterface == 70 && keyPressed == 'D'){
    Screen = false;
    lcd.clear();
    lcd.noBacklight();
    return(0);
  }
  else if (keyPressed == 'D'){
    lcd.clear();
    int newInterface = currentInterface+10;
    return (newInterface);
  }
  }

/* ELECTRONIC FUNCTIONS */

String GetTime(int returnSelector){
  DateTime now = RTC.now();
  if (returnSelector == 0){
    char buf1[] = "DD/MM/YYYY hh:mm ";
    String dateTime = now.toString(buf1);
    return(dateTime);

  }
  
  if (returnSelector == 1) {
    char buf1[] = "YYYY_MM_DD_hh_mm";
    String dateTime = now.toString(buf1);
    return(dateTime);
  }

}

void getGPS(){

  while(Serial3.available()){ 
    if(GPS.encode(Serial3.read()))
    { 
    GPS.f_get_position(&latitude,&longitude,&age);
   }
  }
  }

float GetSensorValue(int pinSensor){
  float sensorValue = analogRead(pinSensor);
  float voltage = sensorValue * (5.0 / 1024.0);
  //Serial.println(voltage);
  float NTU = ( -(36.063*pow(voltage,4)) + (344.75*pow(voltage,3)) - (795.75*pow(voltage,2)) - (1686.9*(voltage)) + 7004.2 );
  //-4E-15x4 + 3E-12x3 + 2E-07x2 - 0,0015x + 4,445
  return NTU;
}

void SDCardPrintHeaders(File fileObject){
if (fileObject) {
    fileObject.print("Fecha,");
    int sensorCounter = 0;
    while(sensorCounter < numberOfSensors){
      fileObject.print("Sensor");
      fileObject.print(sensorCounter+1);
      fileObject.print(",");
      sensorCounter++;
      }
    fileObject.print("Latitud,");
    fileObject.println("Longitud"); 
    fileObject.close();  
  }
}

void SDCardSaveData(File fileObject){
  if (fileObject) {
    
  String dateTime = GetTime(0);
  fileObject.print (dateTime);
  fileObject.print(",");
  int sensorCounter = 0;
  while(sensorCounter < numberOfSensors){
    float sensorValue = GetSensorValue(availableSensors[sensorCounter]);
//    Serial.print("Sensor");
//    Serial.print(sensorCounter+1);
//    Serial.print(": ");
    fileObject.print(sensorValue);
    fileObject.print(",");
    sensorCounter++;
    }
  getGPS();
  fileObject.print(latitude,5);
  fileObject.print(",");
  fileObject.println(longitude,5);
  fileObject.close();
  }
}
