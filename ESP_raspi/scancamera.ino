#include <SoftwareSerial.h>

SoftwareSerial piSerial(34,35);

float r2,phi;

void setuppiserial(){
  pinMode(35, INPUT);
  pinMode(34, OUTPUT);
  piSerial.begin(9600);
  Serial.begin(9600);
}

void scancamera(){
  piSerial.write("scan");
  if (piSerial.available() > 0) {
    Serial.print("read");
    char theta = piSerial.read();//シリアル通信で受け取ったデータを読み込む
    char dist = piSerial.read();//シリアル通信で受け取ったデータを読み込む
    r2=float(theta);
    phi=float(dist);
  }
  
}
