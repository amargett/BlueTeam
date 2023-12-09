// digital pins
// inputs
int overflowSensor = 10;
// sensor value initialization
int overflowVal = 0;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(overflowSensor, INPUT_PULLUP);
}
void loop()
{
  // put your main code here, to run repeatedly:
  overflowVal = !digitalRead(overflowSensor);
  Serial.println(overflowVal);
  delay(500);
  // assumes installation with arrows on switch pointing upward
  // reading low = draining well
  // reading high = overflow - need to prevent subsequent cycles from starting
}
