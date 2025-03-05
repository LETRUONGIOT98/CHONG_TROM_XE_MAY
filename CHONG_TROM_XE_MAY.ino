#include <SoftwareSerial.h>
#include <Arduino.h>
#include <TinyGPSPlus.h>//https://github.com/mikalhart/TinyGPSPlus
// The TinyGPS++ object
#define rxPin 2
#define txPin 3
#define congtac 12
SoftwareSerial sim800(rxPin, txPin);
float flat=12.285702, flon=109.198756, val, val1;
TinyGPSPlus gps;
SoftwareSerial ss(8, 9);
String sms_status, sender_number, received_date, msg;
int old = 0;
int khoa =0;
int olds = 0, i = 0, h = 0, k = 0;
unsigned long age, times;
unsigned time ;
int gui = 0;
String valr="";
int m=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(A2, INPUT_PULLUP);
  pinMode(congtac, INPUT_PULLUP);
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  digitalWrite(11, LOW);
  
  Serial.begin(9600);
  sim800.begin(9600);
  ss.begin(9600);
  delay(7000);
  sms_status = "";
  sender_number = "";
  received_date = "";
  msg = "";
  delay(10);
  // Unlock your SIM card with a PIN
  //modem.simUnlock("1234");
  delay(1000);
  sim800.println("AT"); //Check GSM Module
  delay(1000);
  sim800.println("ATE1"); //Echo ON
  delay(1000);
  sim800.println("AT+CPIN?"); //Check SIM ready
  delay(1000);
  sim800.println("AT+CMGF=1"); //SMS text mode
  delay(1000);
  sim800.println("AT+CNMI=2,2,0,0,0"); //set sms received format
  delay(3000); 
  //sendATcommưand("AT+CSCLK=2", "OK", 1000);
  if (digitalRead(12) == LOW) {
    phanhoi(3);
    delay(100);   
    digitalWrite(4, HIGH);
    delay(150);
    digitalWrite(4, LOW);
    delay(150);
    digitalWrite(4, HIGH);
    delay(150);
    digitalWrite(4, LOW);
    delay(150);
    digitalWrite(4, HIGH);
    delay(150);
    digitalWrite(4, LOW);
    delay(150);
  }
  if (digitalRead(12) == HIGH) {
    phanhoi(4);
    delay(100);
  }
  phanhoi(0);
  digitalWrite(4, HIGH);
  delay(500);
  digitalWrite(4, LOW);
  time = millis();
}

void loop() {
 if(Serial.available()>0){
    valr = Serial.readStringUntil('\n');
    Serial.println(valr);
    if(valr=="gps\r" || valr=="GPS\r" || valr=="Gps\r"){
      delay(100);
      phanhoi(5);
    }
    }
  valr="0";
  if(khoa == 0 && flat == 0.0 && flon ==0.0){
  static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  printFloat2(gps.location.lng(), gps.location.isValid(), 12, 6);
  Serial.println();
  times = millis();}
  // put your main code here, to run repeatedly:
  if (digitalRead(12) == LOW) {
    if (digitalRead(A2) == HIGH) {
      time = millis();
      khoa==1;
       m = m+1;
       Serial.println(m);
      delay(10);}}
      if(m >= 2 && m < 20){
        m=200;
        Serial.println(m);
        Serial.println("PHAT HIEN XE BI TROM");
        digitalWrite(4, HIGH);
        phanhoi(2);
        delay(1000);
        khoa == 0;
        }
      if (millis() - time > 500 && digitalRead(A2) == LOW) {
        m=0;
      }
  else {
    phanhoi(0);
    khoa == 0;
    time = millis();
  }
  if (digitalRead(12) == HIGH) {
    delay(100);
    if (digitalRead(12) == LOW) {
      phanhoi(3);
      delay(200);
      digitalWrite(4, HIGH);
      delay(150);
      digitalWrite(4, LOW);
      delay(150);
      digitalWrite(4, HIGH);
      delay(150);
      digitalWrite(4, LOW);
      delay(150);
      digitalWrite(4, HIGH);
      delay(150);
      digitalWrite(4, LOW);
      delay(150);
    }
  }
  if (digitalRead(12) == LOW) {
    delay(100);
    if (digitalRead(12) == HIGH) {
      phanhoi(4);
    }
  }
}
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (ss.available()) {
      gps.encode(ss.read());
    }
  } while (millis() - start < ms);
}

static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    flat = val;
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i = flen; i < len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}
static void printFloat2(float val1, bool valid1, int len1, int prec1)
{
  if (!valid1)
  {
    while (len1-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val1, prec1);
    flon = val1;
    int vi = abs((int)val1);
    int flen = prec1 + (val1 < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i = flen; i < len1; ++i)
      Serial.print(' ');

  }
  smartDelay(0);
}

void phanhoi(int tipe) {
  if(tipe == 1){
   Serial.println("DA KHOI DONG");
  }
  if (tipe == 2) {
    sim800.println("AT+CMGF=1");
    delay(1000);
    sim800.println("AT+CMGS=\"+0328813393\"\r");   //Số điện thoại nhận tin nhắn phản hồi 0979838023
    delay(1000);
    sim800.print("http://maps.google.com/maps?q=loc:");
    sim800.print(flat);
    sim800.print(",");
    sim800.print(flon);
    delay(1000);
    sim800.println((char)26); //ascii code for ctrl-26 //sim800.println((char)26); //ascii code for ctrl-26
    delay(3000);
    sim800.println("ATD+84328813393;");             ////////Thay số điện thoại cần gọi
    delay(100);
    delay(1000);
    Serial.println("DA NHAN TIN");
    Serial.println("DANG GOI DIEN");
    delay(30000);
    sim800.println("ATH");                              // Ngat cuoc goi
    digitalWrite(4, LOW);
    delay(2000);
  }
  if (phanhoi == 3) {
    sim800.println("AT+CMGF=1");
    delay(1000);
    sim800.println("AT+CMGS=\"+0365801715\"\r");   //Số điện thoại nhận tin nhắn phản hồi
    delay(1000);
    sim800.println("BAT CHE DO CHONG TROM");
    Serial.println("DA BAT CHONG TROM");
    delay(100);
    sim800.println((char)26);
    delay(1000);
  }
  if (phanhoi == 4) {
    sim800.println("AT+CMGF=1");
    delay(1000);
    sim800.println("AT+CMGS=\"+0365801715\"\r");   //Số điện thoại nhận tin nhắn phản hồi
    delay(1000);
    sim800.println("DA TAT CHE DO CHONG TROM");
    Serial.println("DA TAT CHONG TROM");
    delay(100);
    sim800.println((char)26);
    delay(1000);
  }
  if (tipe == 5) {
    sim800.println("AT+CMGF=1");
    delay(1000);
    sim800.println("AT+CMGS=\"+0365801715\"\r");   //Số điện thoại nhận tin nhắn phản hồi
    delay(1000);
    delay(1000);
    sim800.print("http://maps.google.com/maps?q=loc:");
    sim800.print(flat);
    sim800.print(",");
    sim800.print(flon);
    delay(1000);
    sim800.println((char)26); //ascii code for ctrl-26 //sim800.println((char)26); //ascii code for ctrl-26
    delay(1000);
    Serial.println("DA GUI TIN NHAN");
    delay(1000);
}
}
