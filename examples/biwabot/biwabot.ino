
// Build a flood early warning system with ESP8266

// The installed version of ArduinoJson library: it MUST be 5.13.5 or lesser
#include <ArduinoJson.h>

// Telegram Bot Library for Sparkfun ESP8266 Think Boaard.
#include "Biwabot.h"

// Include the correct display library
// For a connection via I2C using the Sparkfun ESP8266 Think Wire include:
// Only needed for Arduino 1.6.5 and earlier
#include <Wire.h> 

//  legacy: #include "SSD1306.h"   
//  https://github.com/ThingPulse/esp8266-oled-ssd1306           
#include "SSD1306Wire.h"        

// Initialize the OLED display using ESP8266 Wire:
// ADDRESS, SDA, SCL  -  SDA and SCL usually populate automatically based on your board's pins.
SSD1306Wire display(0x3c, 2, 14);   

#define SENSOR_INFO "SensorInfo"
#define RIVER_INFO "RiverInfo"

Biwabot iBot;
InlineKeyboard iKeyboard; 
bool isKeyboardActive;  

// Wifi config

// YOUR WIFI SSID
String ssid = " "; 
// YOUR WIFI PASSWORD    
String pass = " ";
// YOUR TELEGRAM BOT TOKEN 
String token = " ";   

// Buzzer IO onboard  Sparkfun ESP8266 Think for local Alarm.
uint8_t buzzer      = 5; 
#define DEMO_DURATION 3000
typedef void (*Demo)(void);

int demoMode = 0;
int counter = 1;
// Ultrasonic HC-SR04 config.
long t;
int triggerPin = 12;
int echoPin = 13;
float distance;
float percentage;
float max_level = 32.00;

void calcSonar() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  t = (pulseIn(echoPin, HIGH) / 2);
  distance = float(t * 0.0343);
  Serial.println(distance);
  Serial.println(" cm");
  Serial.println(t);
  percentage = (100 - ((100 / max_level) * distance));
  if (percentage < 0.00) {
    percentage = 0.00;
  }
  delay(500);
 }

void drawTextDistanceDemo() {
  // Text Font 
  display.setFont(ArialMT_Plain_16);
  // https://lastminuteengineers.com/oled-display-esp8266-tutorial/
  // The coordinates define the center of the text
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 22, "Level = "+ String(distance)+ " cm");
}
void drawTextPercentageDemo() {
  // Text Font
  display.setFont(ArialMT_Plain_16);
  // The coordinates define the center of the text
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 22, "Rating = "+ String(percentage)+ " %");
}

Demo demos[] = {drawTextDistanceDemo,  drawTextPercentageDemo};
int demoLength = (sizeof(demos) / sizeof(Demo));
long timeSinceLastModeSwitch = 0;


void setup() {
  // initialize the Serial
  Serial.begin(115200);
  Serial.println("Menghubungkan Telegram Bot...");

  // Initialising the UI will init the display too.
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);

  calcSonar();
  // connect the ESP8266 to the desired access point
  iBot.wifiConnect(ssid, pass);
  // set the telegram bot token
  iBot.setTelegramToken(token);
  // check if all things are ok
  if (iBot.testConnection())
  Serial.println("\nWIFI-Terhubung.");
  else
  Serial.println("\nWIFI-Tidak terhubung.");
  // set the pin connected to the buzzer to act as output pin
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  // turn off the buzzer (inverted logic!)
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // inline keyboard customization
  iKeyboard.addRow();
  // add a query button to the first row of the inline keyboard
  iKeyboard.addButton("1️⃣ Pengukuran ", SENSOR_INFO, KeyboardButtonQuery);
  // add another query button to the first row of the inline keyboard
  iKeyboard.addButton("2️⃣ Info Sensor ", RIVER_INFO, KeyboardButtonQuery);
  // add a new empty button row
  iKeyboard.addRow();
  
}


void loop() {
  // a variable to store telegram message data
 TBMessage msg;

        // if there is an incoming message...
        if (iBot.getNewMessage(msg)) {
        // check what kind of message I received
        if (msg.messageType == MessageText) {
        // received a text message
        if (msg.text.equalsIgnoreCase("kalibrasi ok")){
           digitalWrite(buzzer, LOW); 
        }
        if (msg.text.equalsIgnoreCase("mulai")) {
        // the user is asking to show the inline keyboard --> show it
        iBot.sendMessage(msg.sender.id, "\n🔢 Klik tombol dibawah untuk melihat informasi pengukuran sensor dan informasi sensor.\n\n⬇️", iKeyboard);
				isKeyboardActive = true;         
        }
        else {
        // the user write anithing else --> show a hint message
        iBot.sendMessage(msg.sender.id, "\n🆔 Selamat datang di Notifikasi Peringatan Dini Banjir Berbasis Level Ketinggian Muka Air, untuk mengetahui kondisi ketinggian air sungai yang dideteksi, sebagai antisipasi akan datangnya banjir. \n\nKetik ' mulai ' untuk melanjutkan!!\n");
          }
        } else if (msg.messageType == MessageQuery) 
          {
        if (msg.callbackQueryData.equals(SENSOR_INFO)) {
        iBot.endQuery(msg.callbackQueryID, "\n🔵 INFORMASI PENGUKURAN \n \n🏷 Persentase ketinggian : " + String(percentage) + " % \n🏷 Ketinggian muka air : " + String(distance) + " cm.", true);
          } 
        if (msg.callbackQueryData.equals(RIVER_INFO)) {
        iBot.endQuery(msg.callbackQueryID, "\n🔵 INFORMASI SENSOR\n \nSensor yang digunakan pada sistem peringatan dini banjir ini adalah Sensor HCSR04 yang berfungsi sebagai pendeteksi ketinggian muka air sungai.", true);
            }     
          }
        } 
        
        // Comparison Operators, more reference https://www.arduino.cc/reference/en/
        if (distance <  1 * max_level / 3){
        iBot.sendMessage(msg.sender.id, "\n🔴 BAHAYA BANJIR \n\n⚪️ SEGERA MENGUNGSI.!!");
         // ...turn on the Buzzer extension IO 
         digitalWrite(buzzer, HIGH); 
        }
        else if ( distance < 1.5 * max_level / 3){
        iBot.sendMessage(msg.sender.id, "\n🔵 SIAGA BANJIR \n\n⚪️ HARAP SIAGA.!!");
        // ...turn off the Buzzer extension IO 
        digitalWrite(buzzer, LOW); 
        }
        else if ( distance < 2 * max_level / 3){
        iBot.sendMessage(msg.sender.id, "\n⚫️ WASPADA BANJIR \n\n⚪️ HARAP WASPADA.!!");
        // ...turn off the Buzzer extension IO 
        digitalWrite(buzzer, LOW); 
        }
        

  calcSonar();
  // clear the display
  display.clear();
  
  // draw the current demo method
  demos[demoMode]();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(10, 128, String(millis()));
  
  // write the buffer to the display
  display.display();
  if (millis() - timeSinceLastModeSwitch > DEMO_DURATION) {
    demoMode = (demoMode + 1)  % demoLength;
    timeSinceLastModeSwitch = millis();
  }
  counter++;
  // wait 500 milliseconds
  delay(50);
}
