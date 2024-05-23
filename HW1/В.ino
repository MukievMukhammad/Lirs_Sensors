int analogPin = 0; // potentiometer wiper (middle terminal) connected to analog pin 3
                    // outside leads to ground and +5V
double val = 0;  // variable to store the value read

void setup() {
  Serial.begin(9600); // открыли порт для связи
}

void loop() {
  val = analogRead(analogPin) / 4;
  Serial.println(val);
  analogWrite(9, val);
  delay(250);
}