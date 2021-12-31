//#define MaxTorque
//#define Voltage 

// ----------------------------------------------------------------------------
// - Motor forward, back, stop                                                             ----
// ----------------------------------------------------------------------------
#define A 0
#define B 1
#define AIN1 A4 //L_motor
#define AIN2 A5
#define BIN1 A19 //R_motor
#define BIN2 A18
#define PWMA A15 //GPIO=12
#define PWMB A16 //GPIO=14
#define STBY A17

void Lback(int duty){
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  ledcWrite(A, duty);
}
void Rback(int duty){
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  ledcWrite(B, duty);
}

void Lforward(int duty){
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  ledcWrite(A, duty);
}

void Rforward(int duty){
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  ledcWrite(B, duty);
}

void Lstop(int st_sec){
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    delay(st_sec);
}   

void Rstop(int st_sec){
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
    delay(st_sec);
}   

void LRstop(int st_sec){
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
    delay(st_sec);
}    


// ----------------------------------------------------------------------------
// - Motor  main()                                                            ----
// ----------------------------------------------------------------------------

//wheelはどのタイヤを回すか．0=>L, 1=>R, 2=>両方
int Motor(int Duty, int st, int st_sec, int wheel){ //st,st_secはモータ止める用 
    int Direction = (int)Duty;
    
    digitalWrite(STBY, HIGH);
    Duty>255? Duty=255:Duty=Duty;
    Duty<-255? Duty=-255:Duty=Duty;

    Serial.write("A");
    
    // if (st == 1) {
    //   stop(st_sec);    //モータ止める
    //   Serial.println("モータを止めています");
    // }
    
    switch(wheel){
      case 0: //L_Motor
        if (Direction >= 0){
          Lforward(Direction);
          Serial.write("B");
        }else if(st == 1){
          Lstop(st_sec);
          Serial.println("Lモータを止めています");
        }else {
          Lback( abs(Direction) );
          Serial.write("c");
        } 
        break;
     
      case 1: //R_Motor
        if (Direction >= 0){
          Rforward(Direction);
        }else if(st == 1){
          Rstop(st_sec);
          Serial.println("Rモータを止めています");
        }else {
          Rback( abs(Direction) );
        }
        break;
        
      case 2: //L_Motor,R_Motor
        if (Direction >= 0){
          Lforward(Direction);
          Rforward(Direction);
        }else if(st == 1){
          LRstop(st_sec);
          Serial.println("LRモータを止めています");
        }else {
          Lback( abs(Direction) );
          Rback( abs(Direction) );
        }
        break;
    }
    return 0;
}

void motorpin(){
  ledcSetup(A, 12800, 8);
  ledcSetup(B, 12800, 8);
  ledcAttachPin(PWMA,A);
  ledcAttachPin(PWMB,B);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
}
