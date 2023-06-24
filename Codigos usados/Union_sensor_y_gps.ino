#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Adafruit_Fingerprint.h>
// Choose two Arduino pins to use for software serial
SoftwareSerial mySerial(2, 4); // Crear Serial para Sensor Rx, TX del Arduino
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial); // Crea el objeto Finger comunicacion pin 2 , 4
const byte pinBuzzer = 9;
int RXPin = 7;
int TXPin = 6;
int analogo5=0;

int GPSBaud = 9600;

// Create a TinyGPS++ object
TinyGPSPlus gps;

// Create a software serial port called "gpsSerial"
SoftwareSerial gpsSerial(RXPin, TXPin);

void setup()
{
pinMode(7, OUTPUT);
pinMode(5, OUTPUT);
pinMode(4, OUTPUT);
// Start the Arduino hardware serial port at 9600 baud
Serial.begin(9600);

// Start the software serial port at the GPS's default baud
gpsSerial.begin(GPSBaud);

while (!Serial); // Yun/Leo/Micro/Zero/...
delay(100);
Serial.println("Sistema de apertura con huella dactilar");

// set the data rate for the sensor serial port
finger.begin(57600); // inicializa comunicacion con sensor a 57600 Baudios
delay(5);
if (finger.verifyPassword()) { //veificacion conexion al sensor de huella
Serial.println("Detectado un sensor de huella!");
} else {
Serial.println("No hay comunicacion con el sensor de huella");
Serial.println("Revise las conexiones");
while (1) { delay(1); }
}

finger.getTemplateCount(); // Informacion de la memoria del sensor de huella
Serial.print("El sensor contiene "); Serial.print(finger.templateCount); Serial.println(" plantillas");
Serial.println("Esperando por una huella valida...");
}

void loop()
{
getFingerprintIDez(); //Refresh para la huella
delay(50);
// This sketch displays information every time a new sentence is correctly encoded.
}

int getFingerprintIDez() {
uint8_t p = finger.getImage();
if (p != FINGERPRINT_OK) return -1;

p = finger.image2Tz();
if (p != FINGERPRINT_OK) return -1;

p = finger.fingerFastSearch();
if (p != FINGERPRINT_OK) {
Mal_Registro();
return -1;
}
// Si hay coincidencias de huella
Serial.print("ID #"); Serial.print(finger.fingerID);
Serial.print(" coincidencia del "); Serial.println(finger.confidence);
if(finger.fingerID==1){
Serial.print("BIENVENIDO PROFE *** ");
abrirPuerta();
}
if(finger.fingerID==2){
Serial.print("BIENVENIDO DIEGO *** ");
abrirPuerta();
}
return finger.fingerID;
}
void Mal_Registro() { // Activa el Buzzer 2 veces por tarjeta no autorizada
digitalWrite(7, HIGH);
analogWrite(pinBuzzer, 10);
delay(200);
digitalWrite(7, LOW);
analogWrite(pinBuzzer, LOW);
delay(25);
digitalWrite(7, HIGH);
analogWrite(pinBuzzer, 10);
delay(200);
digitalWrite(7, LOW);
analogWrite(pinBuzzer, LOW);
delay(25);
digitalWrite(7, HIGH);
analogWrite(pinBuzzer, 10);
delay(200);
digitalWrite(7, LOW);
analogWrite(pinBuzzer, LOW);
delay(25);

while (gpsSerial.available() > 0)
{
if (gps.encode(gpsSerial.read()))
{
if (gps.location.isValid())
{
Serial.print("Latitude: ");
Serial.println(gps.location.lat(), 6);
Serial.print("Longitude: ");
Serial.println(gps.location.lng(), 6);
Serial.print("Altitude: ");
Serial.println(gps.altitude.meters());
}
else
{
Serial.println("Location: Not Available");
}

  Serial.print("Date: ");
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.print("Time: ");
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(".");
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.println(gps.time.centisecond());
  }
  else
  {
    Serial.println("Not Available");
  }
}
}
if (millis() > 5000 && gps.charsProcessed() < 10)
{
Serial.println("No GPS detected");
}

Serial.println();
Serial.println();
delay(1000);
}

void abrirPuerta() {
Serial.println(" AUTORIZADA *** ");
analogWrite(pinBuzzer, 10);
digitalWrite(5, HIGH); // Abrir la cerradura
delay(1000);
analogWrite(pinBuzzer, LOW);
digitalWrite(5, LOW);
delay(1000); // cierra la cerradura
}
