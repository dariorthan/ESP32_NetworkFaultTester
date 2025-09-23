#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <WiFi.h>
#include <ESPping.h>

#define WifiPassword "Prinzenrolle"
#define WifiSSID "KP-Wlan"
#define WifiChannel 6

bool DebugMode = true;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
const byte ROWS = 5;  //four rows
const byte COLS = 4;  //four columns
int IPSection1 = 0;
int IPSection2 = 0;
int IPSection3 = 0;
int IPSection4 = 0;
int SubSection1 = 0;
int SubSection2 = 0;
int SubSection3 = 0;
int ret = 0;
void SubSection();
int IntConvert (char StringConvert);
int ExitCondition = 0;
IPAddress RecalcIP ();

IPAddress ip1 (10, 10, 1, 8);
IPAddress ip2 (10, 10, 1, 8);
IPAddress ip3 (10, 10, 1, 8);
IPAddress ip4 (10, 10, 1, 8);
IPAddress ip (IPSection1, IPSection2, IPSection3, IPSection4); // The remote ip to ping 

char keys[ROWS][COLS] = {
  { 'Y', 'X', '#', '*' },
  { '1', '2', '3', 'U' },
  { '4', '5', '6', 'D' },
  { '7', '8', '9', 'E' },
  { 'L', '0', 'R', 'R' },
};

byte rowPins[ROWS] = { 32, 33, 25, 26, 27};  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 17, 16, 12, 14 };  //connect to the column pinouts of the keypad

//Create an object of keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
int key = keypad.getKey();
void setup()
{
  
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  //LED Pins
  pinMode(17, OUTPUT); //Red LED 1
  #define RLED1 17
  pinMode(16, OUTPUT); //Red LED 2
  #define RLED2 16
  pinMode(4, OUTPUT); //Red LED 3
  #define RLED3 4
  pinMode(15, OUTPUT); //Red LED 4
  #define RLED4 15
  pinMode(23, OUTPUT); //Green LED 1
  #define GLED1 23
  pinMode(19, OUTPUT); //Green LED 2
  #define GLED2 19
  pinMode(18, OUTPUT); //Green LED 3
  #define GLED3 18
  pinMode(5, OUTPUT); //Green LED 4
  #define GLED4 5
  //Button Pins
  pinMode(36, INPUT); //Button 
  pinMode(39, INPUT); //Button 
  pinMode(34, INPUT); //Button 
  pinMode(35, INPUT); //Button 
  Serial.begin(9600);
  // initialize the lcd 
  lcd.init();                      
  lcd.backlight();
  lcd.setCursor(0,0);

  WiFi.begin(WifiSSID, WifiPassword, 6);
  Serial.print("Connecting to WiFi ");
  WiFi.setHostname("EXP32_Tester");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
    digitalWrite(RLED1, HIGH);
    digitalWrite(RLED2, HIGH);
    digitalWrite(RLED3, HIGH);
    digitalWrite(RLED4, HIGH);
  }
  Serial.println(" Connected!");
  Serial.print("IP-Adress:");
  Serial.println(WiFi.localIP());
  digitalWrite(GLED1, HIGH);
  digitalWrite(GLED2, HIGH);
  digitalWrite(GLED3, HIGH);
  digitalWrite(GLED4, HIGH);

  delay(1000);

  digitalWrite(RLED1, LOW);
  digitalWrite(RLED2, LOW);
  digitalWrite(RLED3, LOW);
  digitalWrite(RLED4, LOW);
  digitalWrite(GLED1, LOW);
  digitalWrite(GLED2, LOW);
  digitalWrite(GLED3, LOW);
  digitalWrite(GLED4, LOW);
}

void loop() {
  
//Ping IP #1
  ret = Ping.ping(ip1);
  Serial.println();
  Serial.print(ret);
  if (ret == 1) {
    if(DebugMode == true) {
    Serial.println();
    Serial.print("Target 1 Active");
    }
    digitalWrite(RLED1, LOW);
    digitalWrite(GLED1, HIGH);
  } else {
    if(DebugMode == true) {
    Serial.println();
    Serial.print("Target 1 inctive");
    }
    digitalWrite(RLED1, HIGH);
    digitalWrite(GLED1, LOW);
  };

  Serial.println();
    Serial.print("break");
//Ping IP #2
  ret = Ping.ping(ip2);
  if (ret == 1) {
    if(DebugMode == true) {
    Serial.println();
    Serial.print("Target 2 Active");
    }
    digitalWrite(RLED2, LOW);
    digitalWrite(GLED2, HIGH);
  } else {
    if(DebugMode == true) {
    Serial.println();
    Serial.print("Target 2 inctive");
    }
    digitalWrite(RLED2, HIGH);
    digitalWrite(GLED2, LOW);
  };
//Ping IP #4
  ret = Ping.ping(ip3);
  if (ret == 1) {
    if(DebugMode == true) {
    Serial.println();
    Serial.print("Target 3 Active");
    }
    digitalWrite(RLED3, LOW);
    digitalWrite(GLED3, HIGH);
  } else {
    if(DebugMode == true) {
    Serial.println();
    Serial.print("Target 3 inctive");
    }
    digitalWrite(RLED3, HIGH);
    digitalWrite(GLED3, LOW);
  };
  //Ping IP #2
  ret = Ping.ping(ip4);
  if (ret == 1) {
    if(DebugMode == true) {
    Serial.println();
    Serial.print("Target 4 Active");
    }
    digitalWrite(RLED4, LOW);
    digitalWrite(GLED4, HIGH);
  } else {
    if(DebugMode == true) {
    Serial.println();
    Serial.print("Target 4 inctive");
    }
    digitalWrite(RLED4, HIGH);
    digitalWrite(GLED4, LOW);
  };
}
