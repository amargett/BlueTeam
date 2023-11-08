// digital pins
    // inputs
int soapSensor = 9;
// sensor value initialization
int soapVal = 0;
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(soapSensor, INPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  soapVal = digitalRead(soapSensor);
  if (soapVal == 1) {
    Serial.println("SOAP FULL");
  }
  else {
    Serial.println("SOAP EMPTY");
  }
  delay(10000);
}
