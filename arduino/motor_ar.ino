
//#define MaxTorque
//#define Voltage 

// ----------------------------------------------------------------------------
// - Motor forward, back, stop                                                             ----
// ----------------------------------------------------------------------------

#define AIN1 2
#define AIN2 3
#define BIN1 8
#define BIN2 6
#define PWMA 10
#define PWMB 5
#define STBY 4

void Lback(){
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
}

void Rback(){
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}

void Lforward(){
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
}

void Rforward(){
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
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

void 

// ----------------------------------------------------------------------------
// - Motor  main()                                                            ----
// ----------------------------------------------------------------------------

//wheelはどのタイヤを回すか．0=>L, 1=>R, 2=>両方

int Motor(float Duty_R,float Duty_L,int st,int st_sec){ //st,st_secはモータ止める用
    int RDirection = abs((int)Duty_R);
    int LDirection = abs((int)Duty_L);
    
    digitalWrite(STBY, HIGH);
    Duty>255? Duty=255:Duty=Duty;
    Duty<-255? Duty=-255:Duty=Duty;

    if (s!=0){
        LRstop(st_sec);
        return 0;
    }
    
    if(Duty_R>0){Rforward();}
    else{Rback();}

    if(Duty_L>0){Lforward();}
    else{Lback();}

    analogWrite(PWMA,LDirection);
    analogWrite(PWMB,RDirection);

    return 0;
}

void motorpin(){
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);
}
