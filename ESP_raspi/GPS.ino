#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#define MYPORT_TX 12
#define MYPORT_RX 13


TinyGPSPlus gps;
SoftwareSerial mySerial; // RX, TX
//TinyGPSCustom magneticVariation(gps, "GPRMC", 10);
 
void GPS_setup() {
 // Open serial communications and wait for port to open:
 // Serial.begin(9600);
 // while (!Serial) {
 // ; // wait for serial port to connect. Needed for native USB port only
 // }
 
 // Serial.println("Goodnight moon!");
 
 // set the data rate for the SoftwareSerial port
 mySerial.begin(9600, SWSERIAL_8N1, MYPORT_RX, MYPORT_TX, false);
 mySerial.println("Hello, world?");
}
 
void GPS_calc() { // run over and over
// Serial.println("hello!");
 if (mySerial.available() > 0){
   char c = mySerial.read();
   //Serial.print(c);
   gps.encode(c);
   if (gps.location.isUpdated()){
     // Serial.print("LAT="); Serial.println(gps.location.lat(), 6);
     // Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
     // Serial.print("ALT="); Serial.println(gps.altitude.meters());
     lat_now = (float)gps.location.lat();
     lng_now = (float)gps.location.lng();
     // Serial.print(lat_now);
     // Serial.print(" , ");
     // Serial.println(lng_now);
     r1 = (float)(sqrt(pow(lng_goal - lng_now, 2) + pow(lat_goal - lat_now, 2)) * 99096.44); //m //パラメータは調整の余地あり
     theta1 = (float)(atan2((lng_goal - lng_now) * 1.23, (lat_goal - lat_now)) * 57.3 + 180); //degree //パラメータは調整の余地あり
     // Serial.print(r1);
     // Serial.print(" , ");
     // Serial.println(theta1);
   } else {
    ;
   }
 }

}