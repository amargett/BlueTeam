//initializing input pins
int DrainLevelSensor = 12; //floating drain switch
int DrainLevel = 0; 
int DoorStateSensor = 11; //door limit switch
int DoorState = 0; 
int SoapLevelSensor = 10; //capacitive soap sensor
int SoapLevel = 0;
bool SoapEmpty = false;
int ButtonStatusPin = 5; //button input
int ButtonStatus = 1;
int ButtonPresses = 0; //counter for how many times the button has been pressed
long int prev_time = 0.0; //last button press
long int cycle_start_time; 
long int time = millis(); // current time
//initializing output pins
int cycle_length = 26000; //cycle time, milliseconds
int SoapLevelLED = 9;
int DoorLockLED = 8;
int CycleBeginPLC = 7;
int CycleEndedPLC = 6;
int ButtonBlue = 4;
int ButtonGreen = 3;
int ButtonRed = 2;
//logic booleans 
bool DrainClogged = false;
bool DoorClosed = false;
bool ButtonPressed = false;

void drainCheck(){
    DrainLevel = digitalRead(DrainLevelSensor); //0 when in line, 1 when tilted
    if (DrainLevel == 1) DrainClogged = true; 
    else DrainClogged = false;
}

void soapCheck(){
    SoapLevel = digitalRead(SoapLevelSensor);
    if (SoapLevel == 0){ // check this value
        SoapEmpty = true;
        digitalWrite(ButtonRed, LOW);
        digitalWrite(SoapLevelLED, HIGH);
    }
    else {
        SoapEmpty = false;
        digitalWrite(SoapLevelLED, LOW);
    }
}
void doorClosedCheck(){
  DoorState = digitalRead(DoorStateSensor); //1 when not pressed, 0 when pressed
    if (DoorState == 0) DoorClosed = true;
    else DoorClosed = false;
}

void checkButton(){
    ButtonStatus = digitalRead(ButtonStatusPin); // 0 when pressed, 1 when open
    // Serial.println("ButtonStatus: " + String(ButtonStatus)); 
    Serial.println(time); 
    if (ButtonStatus == 0 & time-prev_time > 1000){ // makes sure at least 1 second has passed since last button press
        prev_time = time;
        ButtonPresses ++;
    }
}

void buttonRed(){
  digitalWrite(ButtonBlue, HIGH); //turns off blue led
  digitalWrite(ButtonGreen, HIGH); //turns off green led
  digitalWrite(ButtonRed, LOW); //turns red led on
}
void buttonGreen(){
  digitalWrite(ButtonBlue, HIGH); //turns off blue led
  digitalWrite(ButtonGreen, LOW); //turns off green led
  digitalWrite(ButtonRed, HIGH); //turns red led on
}
void buttonBlue(){
  digitalWrite(ButtonBlue, LOW); //turns off blue lede
  digitalWrite(ButtonGreen, HIGH); //turns off green led
  digitalWrite(ButtonRed, HIGH); //turns red led on
}
void buttonWhite(){
  digitalWrite(ButtonBlue, LOW); //turns off blue led
  digitalWrite(ButtonGreen, LOW); //turns off green led
  digitalWrite(ButtonRed, LOW); //turns red led on
}
void doorLockBlink(){
    digitalWrite(DoorLockLED, HIGH);
    delay(500);
    digitalWrite(DoorLockLED, LOW);
    delay(500);
    digitalWrite(DoorLockLED, HIGH);
    delay(500);
    digitalWrite(DoorLockLED, LOW);
    delay(500);
    digitalWrite(DoorLockLED, HIGH);
    delay(500);
    digitalWrite(DoorLockLED, LOW);
    delay(500);
}
void blinkGreen(){
    for (int i = 0; i<10; i++){
        buttonGreen(); 
        delay(250); 
        buttonWhite(); 
        delay(250); 
}
    }
void setup() {
    // put your setup code here, to run once:
    time = millis(); 
    Serial.begin(9600);
    pinMode(DrainLevelSensor, INPUT_PULLUP);
    pinMode(DoorStateSensor, INPUT_PULLUP);
    pinMode(SoapLevelSensor, INPUT_PULLUP);
    pinMode(ButtonStatusPin, INPUT_PULLUP);
    pinMode(SoapLevelLED, OUTPUT);
    pinMode(DoorLockLED, OUTPUT);
    pinMode(CycleBeginPLC, OUTPUT);
    pinMode(ButtonBlue, OUTPUT);
    pinMode(ButtonGreen, OUTPUT);
    pinMode(ButtonRed, OUTPUT);
    pinMode(CycleBeginPLC, OUTPUT);
    pinMode(CycleEndedPLC, OUTPUT);
    digitalWrite(CycleBeginPLC, LOW); 
    digitalWrite(CycleEndedPLC, LOW); 
    //turn all button LEDs on -- white button light when powered on 
    buttonWhite();
}
void loop() {
    time = millis(); 
    //check sensors
    drainCheck();
    soapCheck();
    doorClosedCheck();
    // DoorClosed = true; // set to true for testing
    if (ButtonPresses == 0){
        buttonWhite(); 
        digitalWrite(CycleBeginPLC, LOW); 
        digitalWrite(CycleEndedPLC, LOW);
    }
  //turn power LED red if drain is clogged or soap is empty
    if (DrainClogged || SoapEmpty) buttonRed(); 
    else {
        if (DoorClosed){
            buttonGreen();
            checkButton();
        cycle_start_time = time; 
        while (ButtonPresses == 1){
            time = millis(); 
            Serial.println(ButtonPresses); 
            digitalWrite(CycleBeginPLC, HIGH);
            buttonBlue();
            if (time-cycle_start_time > cycle_length){
                ButtonPresses = 0; //cycle done!
                blinkGreen(); 
                Serial.println("cycle over"); 
            }
            checkButton();}
        if (ButtonPresses ==2){ //pause cycle
            Serial.println("pausing"); 
            digitalWrite(CycleBeginPLC, LOW); 
            digitalWrite(CycleEndedPLC, HIGH); 
            buttonRed(); 
            ButtonPresses = 0;   
            delay(5000); 
            }
    }
        else{
            checkButton();
            if (ButtonPresses == 1){
                doorLockBlink();
                Serial.println("resetting"); 
                ButtonPresses = 0;
            }
        }
    }
}
