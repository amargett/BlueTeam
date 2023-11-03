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

void setup() {
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
}
