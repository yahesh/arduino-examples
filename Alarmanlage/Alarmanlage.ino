#define PIEZO_PIN  2
#define OUT_PIN    4
#define LED_PIN    6
#define TRIG_PIN   8
#define ECHO_PIN  10

uint16_t oldDistance = 0;

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
  
  return (result / 29 / 2);
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
  digitalWrite(LED_PIN,   LOW);
}

void loop() {
  if (digitalRead(OUT_PIN)) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("OUT: HIGH");
    
    uint16_t distance = getDistance();
    Serial.print("DISTANCE: ");
    Serial.print(distance);
    Serial.println(" CM");
    Serial.println("");

    if ((oldDistance != distance) && (oldDistance != 0)) {
      tone(PIEZO_PIN, 1500, 50);
      delay(100);
      tone(PIEZO_PIN, 1000, 50);
      delay(100);
      tone(PIEZO_PIN, 1500, 50);
      delay(100);
      tone(PIEZO_PIN, 1000, 50);
      delay(100);
      tone(PIEZO_PIN, 1500, 50);
      delay(100);
      tone(PIEZO_PIN, 1000, 50);
      delay(100);
      tone(PIEZO_PIN, 1500, 50);
      delay(100);
      tone(PIEZO_PIN, 1000, 50);
      delay(100);
      tone(PIEZO_PIN, 1500, 50);
      delay(100);
      tone(PIEZO_PIN, 1000, 50);
      delay(100);
    }
    oldDistance = distance;
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("OUT: LOW");
  }
  
  delay(10);
}
