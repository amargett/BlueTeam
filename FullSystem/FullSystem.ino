//parameters
int safe_temp = 120; // degrees F
int heater_startup_time = 5; // seconds
int hotwater_time = 25; // seconds
int coldwater_time = 30; // seconds

// digital pins
    // inputs
int onOffButton = 1; 
int ESTOP = 2; 
int doorSensor = 3; 
    // outputs 
int soapPump = 4; 
int heater = 5; 
int doorLock = 6; 
int sol1 = 7; 
int sol2 = 8; 
// analog pins, both inputs
int thermistor = A0; 
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

void setup() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
    Serial.begin(9600); 
    pinMode(onOffButton, INPUT); 
    pinMode(doorSensor, INPUT); 
    pinMode(heater, OUTPUT); 
    pinMode(soapPump, OUTPUT); 
    pinMode(doorLock, OUTPUT); 
    pinMode(sol1, OUTPUT); 
    pinMode(sol2, OUTPUT); 
}

void loop() {
    make_display(); 
    if (bottle_present() & door_closed()){
        if (state == 1) {
            if (start_stop_pressed()) state = 2; 
        }
        if (state ==2){
            if (cycle_time = 0){
                lock_door(); 
                heater_ON();
                cycle_time = millis();
            }
            if (start_stop_pressed()) state = 4; 
            Cycle();
        }
        if (state ==3){
            unlock_door(); 
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

void read_thermistor(){
  Vo = analogRead(thermistor);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0;
}

bool temp_OK(){
    read_thermistor(); 
    if (T< safe_temp) return true; 
    else return false; 
}

bool start_stop_pressed(){
    //implement, should check whether or not someone pressed the button
}

bool bottle_present(){
// read strain gauges
}

bool door_closed(){
// read from door lock
}

void lock_door(){

}

void unlock_door(){

}

void heater_ON(){

}

void heater_OFF(){

}

void open_sol1(){

}
void close_sol1(){

}
void open_sol2(){

}
void close_sol2(){

}

void pumpON(){
    digitalWrite(soapPump, HIGH); 
}

void pumpOFF(){
    digitalWrite(soapPump, LOW); 
}

void Cycle(){
    if (cycle_time > heater_startup_time*1000){
        if(cycle_time < hotwater_time*1000){
            open_sol1();
            pumpON();
            delay(50); 
            pumpOFF(); 
            delay(100); 
        }
        else if (cycle_time < coldwater_time*1000){
            heater_OFF();
            close_sol1(); 
            open_sol2(); 
        }
        else {
            close_sol2(); 
            state = 3; 
        }
    }
}

void pauseCycle(){

}
