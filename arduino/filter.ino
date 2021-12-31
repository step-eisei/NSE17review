//https://nobita-rx7.hatenablog.com/entry/27644291　参考ページ

#define KP 0.0125
#define KI 10
#define KD 10
#define DELTA_T 10

float target_theta=0; //GPSのデータを(-3.14~3.14)に変換
float current_theta; //現在の角度(-3.14~3.14)
float x[3]={0};

int calctheta(){
  float theta=atan2((lng_goal - lng_now) * 1.23, (lat_goal - lat_now)) * 57.3 + 180;//北から時計回りの角度(°)
  return theta;
}

void controlduty(){
  //GPSの値から目的地までの距離を計算
  float dist=sqrt(pow(lng_goal - lng_now, 2) + pow(lat_goal - lat_now, 2)) * 99096.44, 0);//目的地までの距離[m]
  
  //目的地までの角度を計算
  float theta=atan2((lng_goal - lng_now) * 1.23, (lat_goal - lat_now)) * 57.3 + 180;//北0°から時計回りの角度(°)
  float current_theta=theta-theta_North;//機体から見た北の方角を使って正面からの角度を計算

  if (dist>2){
    Duty_R=200;
    Duty_L=200;
  }
  else{
    Duty_R=100;
    Duty_L=100;
  }

  //PIDでDuty比のプラマイを決定
  x[0]=x[1];
  x[1]=x[2];
  x[2]=current_theta-target_theta;
  float integral=(x[0]+x[1]+x[2])/3.0*DELTA_T;

  Duty_R+= KP*x[2]+KI*integral+KD*(x[2]-x[0])/DELTA_T
  Duty_L-= KP*x[2]+KI*integral+KD*(x[2]-x[0])/DELTA_T
  
}
