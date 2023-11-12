int safe_temp = 120;         // degrees F
int heater_startup_time = 5; // seconds
int hotwater_time = 25;      // seconds
int coldwater_time = 30;     // seconds
int pump_time = 1.2;         // seconds

// digital pins
// inputs
int button = 2; // interrupt pin
int soapSensor = 9;
int overflow = 10;
int bottleDetect = 11;
int doorDetect = 12;
// outputs
int LEDs = 3;
int soapPump = 4;
int heater = 5;
int doorLock = 6;
int sol1 = 7;
int sol2 = 8;

void setup()
{
    Serial.begin(9600);
    pinMode(button, INPUT_PULLUP);
    pinMode(soapPump, OUTPUT);
    pinMode(sol1, OUTPUT);
    pinMode(sol2, OUTPUT);
}

void loop()
{
    int val = digitalRead(button);
    if (val == LOW)
    {
        Serial.println("button");
        ON(sol1);
        delay(3000);
        OFF(sol1);
        ON(sol2);
        delay(3000);
        OFF(sol2);
        delay(100000);
    }
    else
    {
        Serial.println("button off");
        OFF(sol1);
        OFF(soapPump);
        OFF(sol2);
    }
}

void ON(int pin_toWrite)
{
    digitalWrite(pin_toWrite, HIGH);
}

void OFF(int pin_toWrite)
{
    digitalWrite(pin_toWrite, LOW);
}
