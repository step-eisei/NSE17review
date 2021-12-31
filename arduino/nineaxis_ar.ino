void nineAxissetup() {
  Wire.begin();

  Wire.beginTransmission(0x68); Wire.write(0x6B); Wire.write(0x00); Wire.endTransmission();
  Wire.beginTransmission(0x68); Wire.write(0x1C); Wire.write(0x10); Wire.endTransmission();
  Wire.beginTransmission(0x68); Wire.write(0x1B); Wire.write(0x08); Wire.endTransmission();
  Wire.beginTransmission(0x68); Wire.write(0x1A); Wire.write(0x05); Wire.endTransmission();
}

void sixAxis(){

  Wire.beginTransmission(0x68); Wire.write(0x3B); Wire.endTransmission();
  Wire.requestFrom(0x68, 14);
  while (Wire.available() < 14);
  axRaw = Wire.read() << 8 | Wire.read();
  ax = (double)axRaw * 2.0 / 32768.0; //[g]
  ayRaw = Wire.read() << 8 | Wire.read();
  ay = (double)ayRaw * 2.0 / 32768.0; //[g]
  azRaw = Wire.read() << 8 | Wire.read();
  az = (double)azRaw * 2.0 / 32768.0; //[g]
  temperature = Wire.read() << 8 | Wire.read();
  celsius = ((double)temperature-12421.0)/340.0; //[degC]
  gxRaw = Wire.read() << 8 | Wire.read();
  gx = (double)gxRaw * 250.0 / 32768.0; //[/s]
  gyRaw = Wire.read() << 8 | Wire.read();
  gy = (double)gyRaw * 250.0 / 32768.0; //[/s]
  gzRaw = Wire.read() << 8 | Wire.read();
  gz = (double)gzRaw * 250.0 / 32768.0; //[/s]

//   Serial.print("ax="); Serial.print(ax); Serial.print(",");
//   Serial.print("ay="); Serial.print(ay); Serial.print(",");
//   Serial.print("az="); Serial.print(az); Serial.print(",");
//   Serial.print("celsius="); Serial.print(celsius); Serial.print(",");
//   Serial.print("gx="); Serial.print(gx); Serial.print(",");
//   Serial.print("gy="); Serial.print(gy); Serial.print(",");
//   Serial.print("gz="); Serial.println(gz);
}

void magnetic(){
//  int mx, my, mz;
//  int yCalib = (80+270)/2; //myの最小値と最大値の平均
  yCalib = (80+270)/2; //myの最小値と最大値の平均
  
  Wire.beginTransmission(0x0C); Wire.write(0x02); Wire.endTransmission();
  Wire.requestFrom(0x0C, 1);

  uint8_t ST1 = Wire.read();
  if (ST1 & 0x01) {
    Wire.beginTransmission(0x0C);
    Wire.write(0x03);
    Wire.endTransmission();
    Wire.requestFrom(0x0C, 7);
    uint8_t i = 0;
    uint8_t buf[7];
    while (Wire.available()) {
      buf[i++] = Wire.read();
    }
    if (!(buf[6] & 0x08)) {
      mx = ((int16_t)buf[1] << 8) | buf[0];
      my = ((int16_t)buf[3] << 8) | buf[2];
      my -= yCalib;
      mz = ((int16_t)buf[5] << 8) | buf[4];
    }
  }

//    int theta_North = (int)60*atan2(-mx, my);
     theta_North = (int)60*atan2(-mx, my);
   
//   Serial.print("mx="); Serial.print(mx); Serial.print(",");
//   Serial.print("my="); Serial.print(my); Serial.print(",");
//   Serial.print("mz="); Serial.print(mz); Serial.print(",");
//   Serial.print("theta_North="); Serial.println(theta_North);

}
