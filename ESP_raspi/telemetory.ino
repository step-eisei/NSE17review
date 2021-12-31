#include <WiFi.h>

const char ssid[] = "ESP32AP-WiFi";
const char pass[] = "esp32apwifi";
const IPAddress ip(192,168,30,3);
const IPAddress subnet(255,255,255,0);


String place = "default";



WiFiServer server(80);

void telemetorysetup()
{
    Serial.begin(9600);

    WiFi.softAP(ssid,pass);
    delay(100);
    WiFi.softAPConfig(ip,ip,subnet);

    IPAddress myIP = WiFi.softAPIP();


    server.begin();

    Serial.print("SSID: ");
    Serial.println(ssid);
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    Serial.println("Server start!");
}

void telemetory(){
    WiFiClient client = server.available();


    if(Serial.available()){
      place = Serial.readString();
      Serial.println(place);
    }

    if (client) {
        String currentLine = "";
        Serial.println("New Client.");
 
//client.connected()はたぶんクライアントの接続の時にtrue
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                Serial.write(c);
                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        client.print("NOW PLACE =>");
                        client.println(place);
                        client.print("DIRECTION =>");
                        client.println(place);
                        client.print("motive =>");
                        client.println(place);                                                
                        client.println("---------------------------------");
                        break;
                    } else {
                        currentLine = "";
                    }
                } else if (c != '\r') {
                    currentLine += c;
                }
            }
        }
    }
}
                
