const int button_pin = 2; 
const int pump_pin = 4; 

int button_state; 
void setup() {
pinMode(button_pin, INPUT_PULLUP);
pinMode(pump_pin, OUTPUT); 
Serial.begin(9600);
}

void loop() {
    digitalWrite(pump_pin, HIGH); 
    delay(1000); 
    digitalWrite(pump_pin, LOW ); 
    delay(1000); 
}
