int button = 4;
int plc = 6; 
int digitalVal;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  pinMode(plc, OUTPUT); 
}
void loop()
{
  // put your main code here, to run repeatedly:
  digitalVal = digitalRead(button);
  if (digitalVal == LOW)
  {
    digitalWrite(plc, HIGH);
  }
  else digitalWrite(plc, LOW); 
}
