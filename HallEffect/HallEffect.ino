int sensorPin = 2;
int val = 0;
int digitalVal;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}
void loop()
{
  // put your main code here, to run repeatedly:
  digitalVal = digitalRead(sensorPin);
  Serial.println(digitalVal);
  delay(100);
  // if (digitalVal == HIGH)
  //{
  // Serial.println(digitalVal);
  //}
}
