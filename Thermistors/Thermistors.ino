int ThermistorPin = 0;
int Vo;
//float R1 = 10000; for steve's
float R1 = 100000;
float logR2, R2, T;
//float c1 = 0.9144715380e-03, c2 = 2.245308254e-04, c3 = 1.139737662e-07; for steve's
float c1 = 0.4387959262e-03, c2 = 2.532398804e-04, c3 = -0.002040347193e-07;

void setup() 
{
Serial.begin(9600);
}
void loop() 
{
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0;
  Serial.print("Temperature: ");
  Serial.print(T);
  Serial.println(" F");
  delay(500);
}