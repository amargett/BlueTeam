// digital pins
    // inputs
int onOffButton = 1; 
int ESTOP = 2; 
int doorSensor = 3; 
    // outputs
int heater = 4; 
int soapPump = 5; 
int doorLock = 6; 
int sol1 = 7; 
int sol2 = 8; 
// analog pins, both inputs
int thermistor = A0; 
int strainGauge = A1; 

// For Display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
int time = 0; 

//state variables
// 0: Machine Powered on, No power to buttons, cycle not going
// 1: Bottle has been placed & Door is closed, button turns green
// 2: Button has been pressed & Cycle is in process, button turns red
// 3: Cycle successfully completed
// 4: Stop button pressed
// 5: ESTOP pressed
int state = 0;

void setup() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
    Serial.begin(9600); 
    pinMode(onOffButton, INPUT); 
    pinMode(ESTOP, INPUT); 
    pinMode(doorSensor, INPUT); 
    pinMode(heater, OUTPUT); 
    pinMode(soapPump, OUTPUT); 
    pinMode(doorLock, OUTPUT); 
    pinMode(sol1, OUTPUT); 
    pinMode(sol2, OUTPUT); 
}

void loop() {
    make_display(); 
}

void make_display(){
    display.clearDisplay();
    if(time<100) {
        time ++; 
        drawPercentbar( 0, 8, 120, 20,time);}
    else cycle_complete(); 
    display.display();
    delay(10);
}

void drawPercentbar(int x,int y, int width,int height, int progress)
{
   progress = progress > 100 ? 100 : progress;
   progress = progress < 0 ? 0 :progress;
   float bar = ((float)(width-4) / 100) * progress; 
   display.drawRect(x, y, width, height, WHITE);
   display.fillRect(x+2, y+2, bar , height-4, WHITE);
    display.setCursor((width/2) -3, y+5 );
    display.setTextSize(1);
    display.setTextColor(WHITE);
   if( progress >=50){
     display.setTextColor(BLACK, WHITE); // 'inverted' text
  }
    display.print(progress);
     display.print("%");
}

void cycle_complete(){
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.setTextColor(WHITE); 
    display.print("Cycle     Complete!");
}