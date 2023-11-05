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

//state variables
// 0: Machine Powered on, No power to buttons, cycle not going
// 1: Bottle has been placed & Door is closed, button turns green
// 2: Button has been pressed & Cycle is in process, button turns red
// 3: Cycle successfully completed
// 4: Stop button pressed
// 5: ESTOP pressed
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
    read_thermistor(); // updates variable T, degrees F
    if (cycle_ready()){
        if (state == 1) {
            power_button(); 
            if (start_stop_pressed()) state = 2; 
        }
        if (state ==2){
            if (cycle_time = 0){
                lock_door(); 
                pumpON();
                cycle_time = millis();
            }
            Cycle();
            if (start_stop_pressed()) state = 4; 
            if (estop_pressed()) state = 5; 
        }
        if (state ==3){
            unlock_door(); 
            cut_power_heater();
            pumpOFF(); 
        }
        if (state ==4) pauseCycle(); 
        if (state == 5) estop(); 
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

bool start_stop_pressed(){
    //implement, should check whether or not someone pressed the button
}

bool estop_pressed(){

}

bool cycle_ready(){
    if (bottle_present() & door_closed()) return true; 
    else return false; 
}

bool bottle_present(){

}

bool door_closed(){
    
}

void lock_door(){

}

void unlock_door(){

}

void power_button(){

}

void power_heater(){

}

void cut_power_heater(){

}

void switchsol1(){

}

void switchsol2(){

}

void pumpON(){

}

void pumpOFF(){

}

void Cycle(){
    if (cycle_time > 20000){

    }
}

void pauseCycle(){

}

void estop(){

}