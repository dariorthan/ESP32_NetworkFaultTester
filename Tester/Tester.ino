#include <WiFi.h>
#include <ESPping.h>

#define WifiPassword "Prinzenrolle"
#define WifiSSID "KP-Wlan"
#define WifiChannel 6
#define LED1 21
#define LED2 22

void setup(void) {
  Serial.begin(115200);
  WiFi.begin(WifiSSID, WifiPassword, 6);
  Serial.print("Connecting to WiFi ");
  WiFi.setHostname("EXP32_Tester");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");
  Serial.print("IP-Adress:");
  Serial.println(WiFi.localIP());
  
}

void loop(void) {

  delay(5000);
  IPAddress ip (192, 178, 168, 163); // The remote ip to ping 
  int ret = Ping.ping(ip);
  Serial.print(ret);
  

}
