#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
int time = 0; 

void setup() {
   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
   Serial.begin(9600);
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