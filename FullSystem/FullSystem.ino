//parameters
int safe_temp = 120; // degrees F
int heater_startup_time = 5; // seconds
int hotwater_time = 25; // seconds
int coldwater_time = 30; // seconds
int pump_time = 1.2; //seconds

// digital pins
    // inputs
int onOffButton = 2; //interrupt pin
    // outputs 
int LEDs = 3;
int soapPump = 4; 
int heater = 5; 
int doorLock = 6; 
int sol1 = 7; 
int sol2 = 8; 
int soapSensor =9; 
int drainSwitch = 10;
int bottleDetect = 11;
int doorDetect = 12;
// analog pins, both inputs
int strainGauge = A1; 

//state variables
// 0: Machine Powered on, No power to buttons, cycle not going
// 1: Bottle has been placed & Door is closed, button turns green
// 2: Button has been pressed & Cycle is in process, button turns red
// 3: Cycle successfully completed
// 4: Stop button pressed
int state = 0;

// For Display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
int display_time = 0; 

//Temp reading 
int Vo;
//float R1 = 10000; for steve's
float R1 = 100000;
float logR2, R2, T;
//float c1 = 0.9144715380e-03, c2 = 2.245308254e-04, c3 = 1.139737662e-07; for steve's
float c1 = 0.4387959262e-03, c2 = 2.532398804e-04, c3 = -0.002040347193e-07;

//buttons
int button_state = 0; 

//cycle 
long int cycle_time = 0; 

// liquid level sensor
int soapVal = 0; 


void setup() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
    Serial.begin(9600); 
    pinMode(onOffButton, INPUT); 
    pinMode(doorDetect, INPUT); 
    pinMode(heater, OUTPUT); 
    pinMode(soapPump, OUTPUT); 
    pinMode(doorLock, OUTPUT); 
    pinMode(sol1, OUTPUT); 
    pinMode(sol2, OUTPUT); 
    pinMode(soapSensor, INPUT);
    pinMode(bottleDetect,INPUT);
}

void loop() {
    make_display(); 
    if (soap_OK() == false) serviceLEDON(); // check soap levels
    if (pinHigh(bottleDetect) & pinHigh(doorDetect)){ // if bottle present and door closed 
        if (state == 1) {
            if (start_stop_pressed()) state = 2; 
        }
        if (state ==2){
            if (cycle_time = 0){
                ON(doorLock); 
                ON(heater);
                cycle_time = millis();
            }
            if (start_stop_pressed()) state = 4; 
            Cycle();
        }
        if (state ==3){
            OFF(doorLock); 
        }
        if (state ==4) pauseCycle(); 
    }
}
void make_display(){
    display.clearDisplay();
    if(display_time<100) {
        display_time ++; 
        drawPercentbar( 0, 8, 120, 20,display_time);}
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
   if( progress >=50) display.setTextColor(BLACK, WHITE); // 'inverted' text
    display.print(progress); 
     display.print("%");
}
 
void cycle_complete(){
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.setTextColor(WHITE); 
    display.print("Cycle     Complete!");
}

bool start_stop_pressed(){
    //implement, should check whether or not someone pressed the button
}

bool pinHigh(int pin_toRead){
    int val = digitalRead(pin_toRead); 
    if (val == HIGH) return true; 
    else return false; 
}

bool soap_OK(){
  soapVal = digitalRead(soapSensor);
  if (soapVal == 1) return true; 
  else return false; 
}

void ON(int pin_toWrite){
digitalWrite(pin_toWrite, HIGH);
}

void OFF(int pin_toWrite){
    digitalWrite(pin_toWrite, LOW);
}

void serviceLEDON(){

}

void Cycle(){
    if (cycle_time > heater_startup_time*1000){
        if(cycle_time < hotwater_time*1000){
            ON(sol1);
            if(cycle_time < (hotwater_time +pump_time)*1000) ON(soapPump); 
            else OFF(soapPump); 
        }
        else if (cycle_time < coldwater_time*1000){
            OFF(heater);
            OFF(sol1); 
            ON(sol2); 
        }
        else {
            OFF(sol2); 
            state = 3; 
        }
    }
}

void pauseCycle(){

}
