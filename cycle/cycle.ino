int safe_temp = 120; // degrees F
int heater_startup_time = 5; // seconds
int hotwater_time = 25; // seconds
int coldwater_time = 30; // seconds
int pump_time = 1.2; //seconds
int i = 0; 

// digital pins
    // inputs
int button = 2; //interrupt pin
int soapSensor =9; 
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

void setup() {
    Serial.begin(9600);
    pinMode(button, INPUT_PULLUP);
 pinMode(soapPump, OUTPUT); 
    pinMode(sol1, OUTPUT); 
    pinMode(sol2, OUTPUT); 
}

void loop() {

    delay(20000);
    ON(sol1); 
    ON(soapPump); 
    OFF(sol2);
    delay(1200); 
    OFF(soapPump); 
    delay(3000);
    OFF(sol1); 
    ON(sol2); 
    delay(5000); 
    OFF(sol2);
    OFF(sol1);
    //ON(heater); 
    delay(100000); 
   // ON(sol2);
    //OFF(soapPump); 
    //delay(3000);
    
}

void ON(int pin_toWrite){
digitalWrite(pin_toWrite, HIGH);
}

void OFF(int pin_toWrite){
    digitalWrite(pin_toWrite, LOW);
}