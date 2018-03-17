const int LED_PIN   = 13;
const int SOUND_OUT = 11;

int HIGH_LIGHT = 0;
int LOW_LIGHT  = 1023;

void setup() {
  Serial.begin(9800);
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(SOUND_OUT, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  
  int sensorValue = 0;
  
  HIGH_LIGHT = 0;
  LOW_LIGHT  = 1023;
  while (millis() < 5000) {
    sensorValue = analogRead(A0);
    Serial.println(sensorValue);
    delay(10);
    if (sensorValue > HIGH_LIGHT) {
      HIGH_LIGHT = sensorValue;
    }
    if (sensorValue < LOW_LIGHT) {
      LOW_LIGHT = sensorValue;
    }
  }
  
  Serial.print("LOW: ");
  Serial.println(LOW_LIGHT);

  Serial.print("HIGH: ");
  Serial.println(HIGH_LIGHT);
  
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  int pitch = map(analogRead(A0), LOW_LIGHT, HIGH_LIGHT, 50, 2000);
  tone(SOUND_OUT, pitch, 10);
  delay(1);
}
