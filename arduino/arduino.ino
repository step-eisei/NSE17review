//これはCansat制御プログラムのメインファイルです
//今回はヘッダファイルを使わず，このファイル内で変数を定義し，関数を引用します

#include <Servo.h>
#include <Wire.h>
#include <math.h>

//各種変数を定義
float lat_now = 0.00; //自分の緯度．GPSからのデータで更新されることになる．
float lng_now = 0.00; //自分の経度．GPSからのデータで更新されることになる．
float lat_goal = 36.110097; //ゴールの緯度．今はとりあえず学費の緯度を入れている．static変数でもいいかな？
float lng_goal = 140.101396; //ゴールの経度．今はとりあえず学費の緯度を入れている．static変数でもいいかな？
int16_t axRaw, ayRaw, azRaw, temperature, gxRaw, gyRaw, gzRaw; //9軸センサ関係
double ax, ay, az, celsius, gx, gy, gz; //9軸センサ関係
int mx, my, mz; //9軸センサ関係
int theta_North; //9軸センサの地磁気情報から算出した，北極の方向(-180~180)
int yCalib; //myの最小値と最大値の平均
int Duty_R,Duty_L;//左右のDuty比

//モーターセットアップ
#define AIN1 2
#define AIN2 3
#define BIN1 8
#define BIN2 6
#define PWMA 10
#define PWMB 5
#define STBY 4
#define L 0
#define R 1
#define BOTH 2
int st=0;


//サーボ
#define SV 9
Servo myservo;

//落下判定用(パラメーターは試行錯誤で)
double tc = 0.5; //ローパスの時定数0~1の間の数値で．大きいほど強いローパスになる
double th_fall =　1.0; //落下判定の閾値．着地後の静止したときの加速度より少し大きい値を想定 

void setup(){
    motorpin();
    myservo.attach(SV);
    myservo.write(0);
    nineAxissetup();
}

void loop(){
    if (i == 0) { // 落下~カプセル展開
    delay(60000UL);//1分まつ（起動→発射等々の時間を考慮して調整）
    double LPF_abs_a = 0;
    double abs_a = 0;
    abs_a = sqrt(pow(ax, 2)+pow(ay, 2)+pow(az, 2));
    LPF_abs_a = LPF_abs_a * tc +(1-tc) * abs_a;

      if(LPF_abs_a < th_fall){
        myservo.write(90);
        delay(1000);
        Motor(255,st,st_sec,2);//
        delay(1000);
        i+=1
      }

      else if (i==1){
        GPScalc();
        magnetic();
        controlduty();
        Motor(Duty_R,Duty_L,st,st_sec);
        i+=1;
      }

    else if (i==2)
    
  }
}
