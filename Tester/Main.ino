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
int IPSectionBuffer = 0;
int IPSection1 = 0;
int IPSection2 = 0;
int IPSection3 = 0;
int IPSection4 = 0;
int SubSection1 = 0;
int SubSection2 = 0;
int SubSection3 = 0;
int IPToEdit = 0;
int ret = 0;
int ExitCondition = 0;

IPAddress RecalcIP ();
int IntConvert (char StringConvert);
void AllLEDsHigh();
void AllLEDsLow();
int GetIPToEdit();
void EditIPSection(int SectionNr);
int EditSubsection(int SubsectionNr,int IPSectionBuffer,int SectionNr);
void PrintIPSection (int SectionNr,int IPSectionBuffer);

IPAddress ip1 (10, 10, 1, 8);
IPAddress ip2 (10, 10, 0, 1);
IPAddress ip3 (10, 10, 0, 254);
IPAddress ip4 (1, 1, 1, 1);
IPAddress ip (IPSection1, IPSection2, IPSection3, IPSection4); // The remote ip to ping 

char keys[ROWS][COLS] = {
  { '1', '2', '3',},
  { '4', '5', '6',},
  { '7', '8', '9',},
  { 'L', '0', 'R',},
};

byte rowPins[ROWS] = { 33, 25, 26, 27};  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 13, 12, 14};  //connect to the column pinouts of the keypad

//Create an object of keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
int key = keypad.getKey();
void setup()
{
  

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
  #define BLED 0
  pinMode(BLED, OUTPUT);
  //Button Pins
  #define InterruptOutput 32
  pinMode(InterruptOutput, OUTPUT);
  digitalWrite(InterruptOutput, HIGH);
  #define InterruptPin 35
  pinMode(InterruptPin, INPUT); //Button 
  Serial.begin(9600);
  // initialize the lcd 
  lcd.init();                      


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
  
  if(digitalRead(InterruptPin) == HIGH) {
    EditMode();
  }
//Ping IP #1
  digitalWrite(BLED, HIGH);
  delay(100);
  digitalWrite(BLED, LOW);
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

  if(digitalRead(InterruptPin) == HIGH) {
    EditMode();
  }
//Ping IP #2
  digitalWrite(BLED, HIGH);
  delay(100);
  digitalWrite(BLED, LOW);
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
  if(digitalRead(InterruptPin) == HIGH) {
    EditMode();
  }
//Ping IP #3
  digitalWrite(BLED, HIGH);
  delay(100);
  digitalWrite(BLED, LOW);
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
  if(digitalRead(InterruptPin) == HIGH) {
    EditMode();
  }
  //Ping IP #4
  digitalWrite(BLED, HIGH);
  delay(100);
  digitalWrite(BLED, LOW);
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

/*------------------------------------------Edit Section-----------------------------------------------*/

void EditMode () {
  AllLEDsHigh();
  digitalWrite(BLED, HIGH);
  lcd.backlight();
  lcd.display();
  /*lcd.setCursor(10,0);
  lcd.print("T");
  lcd.setCursor(0,0);
  lcd.print("Input IP:");
  lcd.setCursor(0,1);
  lcd.print("123456790123456790");*/
  IPToEdit = GetIPToEdit();
  lcd.setCursor(0,0);
  lcd.print("Input IP: ");
  lcd.setCursor(0,1);
  lcd.print("   .   .   .   ");
  EditIPSection(1);
  EditIPSection(2);
  EditIPSection(3);
  EditIPSection(4);
  if (IPToEdit == 1) {
    ip1 = RecalcIP();
  } else if (IPToEdit == 2) {
    ip2 = RecalcIP();
  } else if (IPToEdit == 3) {
    ip3 = RecalcIP();
  } else if (IPToEdit == 4) {
    ip4 = RecalcIP();
  } else {
    if (DebugMode == true) {
      Serial.println("Invalid Input, EditMode");
    }
  }
  RecalcIP();
  ExitCondition = 0;
  delay(1000);
  digitalWrite(BLED, LOW);
  AllLEDsLow();
  lcd.clear();
  lcd.noDisplay();
}

int GetIPToEdit () {
  key = 666;
  ExitCondition = 0;
  lcd.setCursor(0,0);
  lcd.print("Select IP:");
  lcd.setCursor(10,0);
  lcd.print("       ");
  while (ExitCondition == 0) {
    key = keypad.getKey();
    if (key) {
      if (DebugMode == true) {
      Serial.print("Key Pressed : ");
      Serial.println(key);
      }
      if (key == '1') {
        AllLEDsLow();
        digitalWrite(RLED1, HIGH);
        digitalWrite(GLED1, HIGH);
        lcd.setCursor(10,0);
        lcd.print("IP#1   ");
        ExitCondition = 1;
        return 1;
      } else if (key == '2') {
        AllLEDsLow();
        digitalWrite(RLED2, HIGH);
        digitalWrite(GLED2, HIGH);
        lcd.setCursor(10,0);
        lcd.print("IP#2   ");
        ExitCondition = 1;
        return 2;
      } else if (key == '3') {
        AllLEDsLow();
        digitalWrite(RLED3, HIGH);
        digitalWrite(GLED3, HIGH);
        lcd.setCursor(10,0);
        lcd.print("IP#3   ");
        ExitCondition = 1;
        return 3;
      } else if (key == '4') {
        AllLEDsLow();
        digitalWrite(RLED4, HIGH);
        digitalWrite(GLED4, HIGH);
        lcd.setCursor(10,0);
        lcd.print("IP#4   ");
        ExitCondition = 1;
        return 4;
      } else {
        lcd.setCursor(10,0);
        lcd.print("error");
        if (DebugMode == true) {
        Serial.println("Invalid Input");
        }
      key = 666;
      }
    }
  }
}

void EditIPSection (int SectionNr) {
  ExitCondition = 0;
  IPSectionBuffer = 0;
  IPSectionBuffer = EditSubsection(1, IPSectionBuffer);
  PrintIPSection (SectionNr, IPSectionBuffer);
  IPSectionBuffer = IPSectionBuffer + EditSubsection(2, IPSectionBuffer);
  PrintIPSection (SectionNr, IPSectionBuffer);
  IPSectionBuffer = IPSectionBuffer + EditSubsection(3, IPSectionBuffer);
  PrintIPSection (SectionNr, IPSectionBuffer);
  if (DebugMode == true) {
    Serial.print("EditIPSection:");
    Serial.println(IPSectionBuffer);
  }
  if (SectionNr == 1) {
    IPSection1 = IPSectionBuffer;
  } else if (SectionNr == 2) {
    IPSection2 = IPSectionBuffer;
  } else if (SectionNr == 3) {
    IPSection3 = IPSectionBuffer;
  } else if (SectionNr == 4) {
    IPSection4 = IPSectionBuffer;
  } else {
    if (DebugMode == true) {
      Serial.println("Invalid Input, EditIPSection");
    }
  }

}

int EditSubsection (int SubsectionNr, int IPSectionBuffer) {
key = 666;
ExitCondition = 0;
  while(ExitCondition == 0) {
    key = keypad.getKey();
    if (key) {
      if (SubsectionNr == 1) {
          if ((IntConvert (key) == 1) || (IntConvert (key) == 2) || (IntConvert (key) == 0)) {
            SubSection1 = IntConvert (key) * 100;
          if (DebugMode == true) {
            Serial.println();
            Serial.print("Key Pressed : ");
            Serial.println(key);
            Serial.println();
            Serial.print("Lvl1 Passed");
          }
          ExitCondition = 1;
          return SubSection1;
          } else {
            if (DebugMode == true) {
              Serial.println();
              Serial.print("Invalid entry Lvl1");
              Serial.println();
              //comment out later
              Serial.print("Key Pressed : ");
              Serial.println(key);
            }
          }
      } else if (SubsectionNr == 2) {
        if ((IPSectionBuffer == 200 && IntConvert (key) <= 5)||(IPSectionBuffer != 200 && IntConvert (key) != 666)) {
          SubSection2 = IntConvert (key) * 10;
        if (DebugMode == true) {
          Serial.println();
          Serial.print("Key Pressed : ");
          Serial.println(key);
          Serial.println();
          Serial.print("Lvl2 Passed");
        }
        ExitCondition = 1;
        return SubSection2;
        } else {
          if (DebugMode == true) {
            Serial.println();
            Serial.print("Invalid entry Lvl2");
            //comment out later
            Serial.println();
            Serial.print("Key Pressed : ");
            Serial.println(key);
          }
        }
      } else if (SubsectionNr == 3) {
        if ((IPSectionBuffer == 250 && IntConvert (key) <= 5)||(IPSectionBuffer != 250 && IntConvert (key) != 666)) {
          SubSection3 = IntConvert (key) * 1;
          if (DebugMode == true) {
            Serial.println();
            Serial.print("Key Pressed : ");
            Serial.println(key);
            Serial.println();
            Serial.print("Lvl3 Passed");
          }
          ExitCondition = 1;
          return SubSection3;
        } else {
          if (DebugMode == true) {
            Serial.println();
            Serial.print("Invalid entry Lvl3");
            //comment out later
            Serial.println();
            Serial.print("Key Pressed : ");
            Serial.println(key);
          }
        }
      } else {
        if (DebugMode == true) {
          Serial.println("Invalid Input, EditSubsection");
        }
      }
    }
  }
}

IPAddress RecalcIP () {
    IPAddress ip (IPSection1, IPSection2, IPSection3, IPSection4); // The remote ip to ping 
    Serial.print(ip);
    return ip;
}

void PrintIPSection (int SectionNr,int IPSectionBuffer) {
    
    if (SectionNr == 1) {
    lcd.setCursor(0,1);
  } else if (SectionNr == 2) {
    lcd.setCursor(4,1);
  } else if (SectionNr == 3) {
    lcd.setCursor(8,1);
  } else if (SectionNr == 4) {
    lcd.setCursor(12,1);
  } else {
    if (DebugMode == true) {
      Serial.println("Invalid Input, PrintIPSection");
    }
  }
  lcd.print(IPSectionBuffer);
}

/*--------------- Utility Functions------------------------------*/

void AllLEDsHigh () {
  digitalWrite(RLED1, HIGH);
  digitalWrite(RLED2, HIGH);
  digitalWrite(RLED3, HIGH);
  digitalWrite(RLED4, HIGH);
  digitalWrite(GLED1, HIGH);
  digitalWrite(GLED2, HIGH);
  digitalWrite(GLED3, HIGH);
  digitalWrite(GLED4, HIGH);
}

void AllLEDsLow () {
  digitalWrite(RLED1, LOW);
  digitalWrite(RLED2, LOW);
  digitalWrite(RLED3, LOW);
  digitalWrite(RLED4, LOW);
  digitalWrite(GLED1, LOW);
  digitalWrite(GLED2, LOW);
  digitalWrite(GLED3, LOW);
  digitalWrite(GLED4, LOW);
}

int IntConvert (char StringConvert) {

if (StringConvert == '9') {
  if (DebugMode == true) {
    Serial.println();
    Serial.print("Converted 9");
  }
  return 9;
} else if (StringConvert == '8') {
  if (DebugMode == true) {
    Serial.println();
    Serial.print("Converted 8");
  }
  return 8;
} else if (StringConvert == '7') {
  if (DebugMode == true) {
    Serial.println();
    Serial.print("Converted 7");
  }
  return 7;
} else if (StringConvert == '6') {
  if (DebugMode == true) {
    Serial.println();
    Serial.print("Converted 6");
  }
  return 6;
} else if (StringConvert == '5') {
  if (DebugMode == true) {
    Serial.println();
    Serial.print("Converted 5");
  }
  return 5;
} else if (StringConvert == '4') {
  if (DebugMode == true) {
    Serial.println();
    Serial.print("Converted 4");
  }
  return 4;
} else if (StringConvert == '3') {
  if (DebugMode == true) {
    Serial.println();
    Serial.print("Converted 3");
  }
  return 3;
} else if (StringConvert == '2') {
  if (DebugMode == true) {
    Serial.println();
    Serial.print("Converted 2");
  }
  return 2;
} else if (StringConvert == '1') {
  if (DebugMode == true) {
    Serial.println();
    Serial.print("Converted 1");
  }
  return 1;
} else if (StringConvert == '0') {
  if (DebugMode == true) {
    Serial.println();
    Serial.print("Converted 0");
  }
  return 0;
} else {
  if (DebugMode == true) {
    Serial.println();
    Serial.print("Converted 0 Fallback");
  }
  return 0;
}
}