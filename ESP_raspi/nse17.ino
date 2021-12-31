// グローバル変数はこのファイルの冒頭で宣言してください．
// このやり方で不都合があれば，ヘッダファイルの作成も考えています．
#include <WiFi.h>
#include <Servo.h>

float lat_now = 0.00; //自分の緯度．GPSからのデータで更新されることになる．
float lng_now = 0.00; //自分の経度．GPSからのデータで更新されることになる．
float lat_goal = 36.110097; //ゴールの緯度．今はとりあえず学費の緯度を入れている．static変数でもいいかな？
float lng_goal = 140.101396; //ゴールの経度．今はとりあえず学費の緯度を入れている．static変数でもいいかな？
int16_t axRaw, ayRaw, azRaw, temperature, gxRaw, gyRaw, gzRaw; //9軸センサ関係
double ax, ay, az, celsius, gx, gy, gz; //9軸センサ関係
int mx, my, mz; //9軸センサ関係
int theta_North; //9軸センサの地磁気情報から算出した，北極の方向(-180~180)
int yCalib; //myの最小値と最大値の平均


//-----------------
//モーターのピンの位置
#define A 0
#define B 1
#define AIN1 A4 //L_motor
#define AIN2 A5
#define BIN1 A19 //R_motor
#define BIN2 A18
#define PWMA A15 //GPIO=12
#define PWMB A16 //GPIO=14
#define STBY A17
//------------------
//テレメトリの変数たち
const char ssid[] = "ESP32AP-WiFi";
const char pass[] = "esp32apwifi";
const IPAddress ip(192,168,30,3);
const IPAddress subnet(255,255,255,0);
WiFiServer server(80);

String place = "default";　//テレメトリで表示する文字．ちゃんと動かすときには変える！！！！！
//------------------
//落下判定用(パラメーターは試行錯誤で)
double tc = 0.5; //ローパスの時定数0~1の間の数値で．大きいほど強いローパスになる
double th_fall =　1.0; //落下判定の閾値．着地後の静止したときの加速度より少し大きい値を想定 


void setup() {
  motorpin(); // Motorのピンを設定する
  telemetorysetup(); //telemetoryのセットアップ（シリアル通信とかAPモードとかの設定）
  myservo.attach(9);

}

void loop() {

  if (i == 0) { // 落下~カプセル展開
    delay(60000UL);//1分まつ（起動→発射等々の時間を考慮して調整）
    double LPF_abs_a = 0;
    double abs_a = 0;
    abs_a = sqrt(pow(ax, 2)+pow(ay, 2)+pow(az, 2));
    LPF_abs_a = LPF_abs_a * tc +(1-tc) * abs_a;

    if(LPF_abs_a < th_fall){
      myservo.write(90);
      i+=1
    }
    
  }
  
  if (i == 1) {　// GPS情報に基づき走行
    GPS_setup();
    
  }
  
  if (i == 2) {　// カメラ情報に基づき走行
    
  }
  
}
