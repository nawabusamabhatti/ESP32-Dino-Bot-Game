#include <LiquidCrystal.h>
#include <BlynkSimpleEsp32.h>
#include <WiFiUdp.h>
#include <Keypad.h>
#include <EEPROM.h>
#include "bitmaps.h"

int adc_key_in  = 0;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

byte runnerArea[16] {32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32};
byte jump = 32;

int score = 0;
bool freeze_score = 0;

byte correct_code = 123;


unsigned long previousMillis = 0;
unsigned long previousMillisLED = 0;
unsigned long jumpTime = 0;
const int jumpLength = 500;

#define checkSafe runnerArea[1] == 32 || runnerArea[1] == 0




const byte chance_of_ob = 15;
int speedOfScroller = 300;



//ESP-CODE

const byte ROWS = 4; 
const byte COLS = 3; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {27, 26, 25, 33}; 
byte colPins[COLS] = {14, 12, 13}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

const char *ssid     = "UsAmA";
const char *password = "144A4C3E1";



LiquidCrystal lcd(23, 22, 18, 17, 16, 15);

 


void setup()
{
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("  Developed By");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("      NaWaB");
  lcd.setCursor(0,1);
  lcd.print("   UsAmA BhAtti");
  delay(4000);
  lcd.clear();
  
  lcd.createChar(0, dino);
  lcd.createChar(1, cacti);
  lcd.createChar(2, bird);
  lcd.createChar(3, block);
    lcd.clear();
  showSplashScreen(1000, true);
  
}




 
void loop() 
{
     

//GAME-CODE

unsigned long currentMillis = millis();
unsigned long currentMillisOb = millis();
if (currentMillisOb - previousMillis >= speedOfScroller) {
    previousMillis = currentMillisOb;
    if (random(chance_of_ob) == 0) {
      runnerArea[15] = 1;
    } else if (random(chance_of_ob) == 1) {
      runnerArea[15] = 2;
    } else {
      runnerArea[15] = 32;
    }
    for (int i = 0; i <= 15; i++) {
      runnerArea[i] = runnerArea[i + 1];
    }
    if (freeze_score == 0) {
      score++;
    }
  }
  drawBarrier();


///////////////////////////
//btnSELECT
   if (read_LCD_buttons() == btnUP) {
    // runnerArea[1] = 32;
    if (runnerArea[1] != 32 && (runnerArea[1] != 1 || runnerArea[1] != 2)) {
      runnerArea[1] = 32;
    }
    jump = 0;
    freeze_score = 1;
    jumpTime = millis();
  }
  if (millis() - jumpTime >= jumpLength) {
    if (checkSafe) {
      runnerArea[1] = 0;
      jump = 32;
      freeze_score = 0;
    } else {
      showCrashScreen();
    }
  }

  updateLcd();
  printScore();

  if (millis() - previousMillisLED >= 500) {
    previousMillisLED = currentMillis;
    digitalWrite(13, !digitalRead(13));
  }
  //////////////////////////////////////
  
   
  
}




char ASWD()
{
  if(digitalRead(2))
  {
    return 'L';
    }
    if(digitalRead(4))
  {
    return 'D';
    }
    if(analogRead(34) > 4000)
  {
    return 'U';
    }
    if(analogRead(36) > 4000)
  {
    return 'R';
    }
    char customKey = customKeypad.getKey();
  
  if (customKey){
    return customKey;
  }
    return 'N';
  }


// Functions for main.cpp

int read_LCD_buttons() {
  char PAD = ASWD();

  if (adc_key_in > 1000) return btnNONE;

  if (PAD == 'R')  return btnRIGHT;
  if (PAD == 'U')  return btnUP;
  if (PAD == 'D')  return btnDOWN;
  if (PAD == 'L')  return btnLEFT;
  if (PAD == '0')  return btnSELECT;

  return btnNONE;
}

void updateLcd() {
  for (int i = 0; i <= 15; i++) {
    lcd.setCursor(i, 1);
    lcd.write(runnerArea[i]);
  }
  lcd.setCursor(1, 0);
  lcd.write(jump);
}

void drawBarrier() {
  runnerArea[0] = 3;
  runnerArea[15] = 3;
}

void printScore() {
  lcd.setCursor(4, 0);
  lcd.print("Score: ");
  lcd.setCursor(11, 0);
  lcd.print(score);
}

void showSplashScreen(int delayTime, boolean wait_for_start) {
  lcd.home();
  lcd.print("Chrome Dino Game");
  drawSplashGraphics();
  delay(delayTime);
  if (wait_for_start) {
    while (read_LCD_buttons() != btnSELECT) {
      checkForEEPROMUserInitErase();
    }
  }
  lcd.clear();
}

boolean checkForEEPROMUserInitErase() {
  if (read_LCD_buttons() == btnDOWN) {
    lcd.clear();
    lcd.home();
    lcd.print("Enter Executive");
    lcd.setCursor(0, 1);
    lcd.print("Code: ");
    if (EnterPassword() == 0) {
      lcd.clear();
      lcd.home();
      lcd.print("Chrome Dino Game");
      drawSplashGraphics();
      return 0;
    }
    lcd.home();
    lcd.print("Clearing EEPROM");
    EEPROMWriteInt(0, 0);
    delay(250);
    lcd.home();
    lcd.print("               ");
    lcd.home();
    lcd.print("Done!");
    digitalWrite(13, !digitalRead(13));
    delay(100);
    digitalWrite(13, !digitalRead(13));
    delay(400);
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.home();
    lcd.print("Chrome Dino Game");
    drawSplashGraphics();
  }
  return 1;
}

bool leave = 0;
byte code = 0;

boolean EnterPassword() {
  lcd.setCursor(0, 1);
  lcd.print("Code: ");
  while (leave == 0) {
    lcd.setCursor(6, 1);
    lcd.print("    ");
    lcd.setCursor(6, 1);
    lcd.print(code);
    if (read_LCD_buttons() == btnUP) {
      code++;
      delay(50);
    } else if (read_LCD_buttons() == btnDOWN) {
      code--;
      delay(50);
    }
    if (read_LCD_buttons() == btnSELECT) {
      if (code == correct_code) {
        leave = 1;
      } else {
        wrong();
      }
    }
    delay(50);
  }
  delay(250);
  lcd.home();
  lcd.clear();
  lcd.print("Access granted!");
  delay(500);
  lcd.clear();
  return 1;
}

void wrong() {
  lcd.setCursor(0, 1);
  lcd.print("Incorrect!");
  code = 0;
  delay(250);
  lcd.setCursor(0, 1);
  lcd.print("Code: ");
}

void drawRandChar() {
  lcd.setCursor(random(3, 15), 1);
  lcd.write(byte(random(1, 3)));
}

void drawSplashGraphics() {
  lcd.setCursor(0, 1);
  lcd.write(byte(3));
  lcd.setCursor(15, 1);
  lcd.write(byte(3));
  lcd.setCursor(1, 1);
  lcd.write(byte(0));
  drawRandChar();
  drawRandChar();
  drawRandChar();
}

void showCrashScreen() {
  lcd.setCursor(4, 1);
  lcd.print("Game Over!");
  delay(2500);
  lcd.setCursor(4, 1);
  lcd.print("Best: ");
  lcd.setCursor(10, 1);
  lcd.print("      ");
  lcd.setCursor(10, 1);
  if (EEPROMReadInt(0) <= score) {
    EEPROMWriteInt(0, score);
  }
  lcd.print(EEPROMReadInt(0));
  while (true) {
    digitalWrite(13, !digitalRead(13));
    delay(500);
  }
}

void EEPROMWriteInt(int address, int value)
{
  byte two = (value & 0xFF);
  byte one = ((value >> 8) & 0xFF);
//
//  EEPROM.update(address, two);
//  EEPROM.update(address + 1, one);
}

int EEPROMReadInt(int address)
{
  long two = EEPROM.read(address);
  long one = EEPROM.read(address + 1);

  return ((two << 0) & 0xFFFFFF) + ((one << 8) & 0xFFFFFFFF);
}













  
