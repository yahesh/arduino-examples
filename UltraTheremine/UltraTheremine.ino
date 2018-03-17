#define PIEZO_PIN  2
#define OUT_PIN    4
#define LED_PIN    6
#define TRIG_PIN   8
#define ECHO_PIN  10

int HIGH_DIST = 0;
int LOW_DIST  = 10240;

uint16_t getDistance() {
  uint16_t result;
  
  // trigger ultra sonic ranger
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // read ultra sonic output
  result = pulseIn(ECHO_PIN, HIGH);
  
  return result;
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {} // Leonardo
  
  pinMode(PIEZO_PIN, OUTPUT);
  pinMode(OUT_PIN,   INPUT);
  pinMode(TRIG_PIN,  OUTPUT);
  pinMode(ECHO_PIN,  INPUT);
  pinMode(LED_PIN,   OUTPUT);
  
  digitalWrite(PIEZO_PIN, LOW);
  digitalWrite(TRIG_PIN,  LOW);
  digitalWrite(LED_PIN,   HIGH);
  
  uint16_t sensorValue = 0;
  
  uint16_t startTime = millis();
  
  HIGH_DIST = 0;
  LOW_DIST  = 10240;
  while ((millis() - startTime) < 5000) {
    sensorValue = getDistance();
    Serial.println(sensorValue);
    delay(20);
    if (sensorValue != 0) {
      if (sensorValue > HIGH_DIST) {
        HIGH_DIST = sensorValue;
      }
      if (sensorValue < LOW_DIST) {
        LOW_DIST = sensorValue;
      }
    }
  }
  
  Serial.print("LOW: ");
  Serial.println(LOW_DIST);

  Serial.print("HIGH: ");
  Serial.println(HIGH_DIST);
  
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  delay(1);
  uint16_t distance = (getDistance() / 25) * 25;
//  Serial.println(distance);

  uint16_t pitch = map(distance, LOW_DIST, HIGH_DIST, 200, 1000);
  if (pitch > 50) {
    delay(1);
    tone(PIEZO_PIN, pitch, 50);
    delay(20);
  }
}
