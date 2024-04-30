void setup() {
  Serial.begin(9600); // открыли порт для связи
  // подключили кнопку на D2 и GND
  pinMode(2, INPUT_PULLUP);
  pinMode(8, OUTPUT);
  attachInterrupt(0, lightOn, LOW);
}
void lightOn() {
  digitalWrite(8, HIGH);
  Serial.println("LED: on");
}

void loop() {
  digitalWrite(8, LOW);
  Serial.println("LED: off");
}