// parameters
float heater_startup_time = 5.0; // seconds
float hotwater_time = 20.0;      // seconds
float coldwater_time = 10.0;     // seconds
float pump_time = 1.2;           // seconds
float time_to_pause = 2.0;

// digital pins
// inputs
int buttonManualOverride = 0; // [HENRY] MANUAL OVERRIDE
int buttonStartStop = 2;      // interrupt pin
int soapSensor = 9;
int overflow = 10;

// outputs
int LEDs = 3;
int soapPump = 4; // MOSFET
int heater = 5;   // relay
int doorLock = 6; // MOSFET
int sol1 = 7;     // relay
int sol2 = 8;     // relay

int bottleDetect = A1; // hall effect
int doorDetect = A2;   // hall effect

// state variables
//  1: Bottle has been placed & Door is closed, button turns green
//  2: Button has been pressed & Cycle is in process, button turns red
//  3: Cycle successfully completed
//  4: Stop button pressed
int state = 1;

// For Display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
int display_time = 0;

// cycle & pause vars
long int cycle_time = 0;
long int pause_time = 0;

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize display
    Serial.begin(9600);
    pinMode(heater, OUTPUT);
    pinMode(soapPump, OUTPUT);
    pinMode(doorLock, OUTPUT);
    pinMode(sol1, OUTPUT);
    pinMode(sol2, OUTPUT);
    pinMode(buttonStartStop, INPUT_PULLUP);
    pinMode(doorDetect, INPUT);
    pinMode(soapSensor, INPUT);
    pinMode(bottleDetect, INPUT);
    pinMode(overflow, INPUT_PULLUP);
    pinMode(buttonManualOverride, INPUT); // [HENRY] Manual Override button
}

void loop()
{
    if (pinHigh(buttonManualOverride) == true)
    {
        // IN THIS MANUAL OVERRIDE STATE, THE ARDUINO'S STATE MACHINE
        // WILL BE IGNORED.  INSTEAD, WE WILL HAVE MANUAL SWITCHES
        // (CONNECTED DIRECTLY TO THE RESPECTIVE MECHANISMS THEY
        // CONTROL) TO POWER ON/OFF THE DIFFERENT SYSTEMS.  THIS ALLOWS
        // US TO DEBUG THE SYSTEM LIVE AND DEMONSTRATE DIFFERENT
        // ASPECTS OF THE SYSTEM WHEN PEOPLE REQUEST TO SEE IT.

        // MAKE THE DISPLAY SAY THE WE ARE MANUALLY OVERRIDING
        display.clearDisplay();
        display.print("MANUALLY OVERRIDING ARDUINO STATE MACHINE!");
        display.println("USE THE MANUAL SWITCHES TO CONTROL THE MACHINE!");
        display.display();

        // TURN OFF EVERYTHING
        OFF(soapPump);
        OFF(heater);
        OFF(doorLock);
        OFF(sol1);
        OFF(sol2);
    }
    else
    {
        make_display();
        if (pinHigh(soapPump) == false)
            ON(LEDs); // check soap levels
        if (pinHigh(overflow) == true)
            ON(LEDs); // Liquid level overflow
        if (pinHigh(bottleDetect) & pinHigh(doorDetect))
        { // if bottle present and door closed
            if (state == 1)
            {
                if (pinHigh(buttonStartStop) == false)
                    state = 2;
            }
            if (state == 2)
            {
                if (cycle_time = 0)
                {
                    ON(doorLock);
                    ON(heater);
                    cycle_time = millis();
                }
                if (pinHigh(buttonStartStop) == true)
                    state = 4;
                else
                    Cycle();
            }
            if (state == 3)
            {
                OFF(doorLock);
            }
            if (state == 4)
                pauseCycle();
        }
    }
}

void make_display()
{
    display.clearDisplay();
    if (display_time < 100)
    {
        display_time++;
        drawPercentbar(0, 8, 120, 20, display_time);
    }
    else
        cycle_complete();
    display.display();
    delay(10);
}

void drawPercentbar(int x, int y, int width, int height, int progress)
{
    progress = progress > 100 ? 100 : progress;
    progress = progress < 0 ? 0 : progress;
    float bar = ((float)(width - 4) / 100) * progress;
    display.drawRect(x, y, width, height, WHITE);
    display.fillRect(x + 2, y + 2, bar, height - 4, WHITE);
    display.setCursor((width / 2) - 3, y + 5);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    if (progress >= 50)
        display.setTextColor(BLACK, WHITE); // 'inverted' text
    display.print(progress);
    display.print("%");
}

void cycle_complete()
{
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("Cycle     Complete!");
}

bool pinHigh(int pin_toRead)
{
    int val = digitalRead(pin_toRead);
    if (val == HIGH)
        return true;
    else
        return false;
}

void ON(int pin_toWrite)
{
    digitalWrite(pin_toWrite, HIGH);
}

void OFF(int pin_toWrite)
{
    digitalWrite(pin_toWrite, LOW);
}

void Cycle()
{
    if (cycle_time > heater_startup_time * 1000)
    {
        if (cycle_time < (heater_startup_time + hotwater_time) * 1000)
        {
            ON(sol1);
            if (cycle_time < (heater_startup_time + pump_time) * 1000)
                ON(soapPump);
            else
                OFF(soapPump);
        }
        else if (cycle_time < (heater_startup_time + hotwater_time + coldwater_time) * 1000)
        {
            OFF(heater);
            OFF(sol1);
            ON(sol2);
        }
        else
        {
            OFF(sol2);
            state = 3;
        }
    }
}

void pauseCycle()
{
    while (pause_time < time_to_pause * 1000)
    {
        OFF(heater);
        OFF(soapPump);
        OFF(sol1);
        OFF(sol2);
        OFF(doorLock);
    }
}
