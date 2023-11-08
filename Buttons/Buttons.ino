
int button_pin = 2; 

void setup(){
    Serial.begin(9600); 
    pinMode(button_pin, OUTPUT);
}
void loop(){
    digitalWrite(button_pin, HIGH);
}