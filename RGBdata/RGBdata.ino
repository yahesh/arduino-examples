const int GREEN_IN_PIN = 2;
const int RED_IN_PIN   = 3;
const int BLUE_IN_PIN  = 4;

const int GREEN_OUT_PIN = 10;
const int RED_OUT_PIN   = 9;
const int BLUE_OUT_PIN  = 11;

const int LED_PIN = 13;

byte GREEN_THRESHOLD = 0;
byte RED_THRESHOLD   = 0;
byte BLUE_THRESHOLD  = 0;

byte statusCount = 0;

void setup() {
  // provide test output
  Serial.begin(9600);
  
  // define digital pin modes
  pinMode(GREEN_IN_PIN,  INPUT);
  pinMode(RED_IN_PIN,    INPUT);
  pinMode(BLUE_IN_PIN,   INPUT);
  pinMode(GREEN_OUT_PIN, OUTPUT);
  pinMode(RED_OUT_PIN,   OUTPUT);
  pinMode(BLUE_OUT_PIN,  OUTPUT);
  pinMode(LED_PIN,       OUTPUT);
  
  // activate pull up resistors
  digitalWrite(GREEN_IN_PIN, HIGH);
  digitalWrite(RED_IN_PIN,   HIGH);
  digitalWrite(BLUE_IN_PIN,  HIGH);
  
  // switch of RGB LED
  digitalWrite(GREEN_OUT_PIN, LOW);
  digitalWrite(RED_OUT_PIN,   LOW);
  digitalWrite(BLUE_OUT_PIN,  LOW);
  
  // switch LED on
  digitalWrite(LED_PIN, HIGH);
  
  // find thresholds
  delay(100);
  
  GREEN_THRESHOLD = 0;
  do {
    GREEN_THRESHOLD++;
    analogWrite(GREEN_OUT_PIN, GREEN_THRESHOLD);
    delay(10);
  }
  while ((digitalRead(GREEN_IN_PIN) == HIGH) && (GREEN_THRESHOLD < 0xFF));
  GREEN_THRESHOLD = GREEN_THRESHOLD+2;
  digitalWrite(GREEN_OUT_PIN, LOW);
  Serial.print("Green Threshold: ");
  Serial.println(GREEN_THRESHOLD);

  delay(100);

  RED_THRESHOLD = 0;
  do {
    RED_THRESHOLD++;
    analogWrite(RED_OUT_PIN, RED_THRESHOLD);
    delay(10);
  }
  while ((digitalRead(RED_IN_PIN) == HIGH) && (RED_THRESHOLD < 0xFF));
  RED_THRESHOLD = RED_THRESHOLD+2;
  digitalWrite(RED_OUT_PIN, LOW);
  Serial.print("RED Threshold: ");
  Serial.println(RED_THRESHOLD);

  delay(100);
  
  BLUE_THRESHOLD = 0;
  do {
    BLUE_THRESHOLD++;
    analogWrite(BLUE_OUT_PIN, BLUE_THRESHOLD);
    delay(10);
  }
  while ((digitalRead(BLUE_IN_PIN) == HIGH) && (BLUE_THRESHOLD < 0xFF));
  BLUE_THRESHOLD = BLUE_THRESHOLD+2;
  digitalWrite(BLUE_OUT_PIN, LOW);
  Serial.print("Blue Threshold: ");
  Serial.println(BLUE_THRESHOLD);

}

void loop() {
  switch (statusCount) {
    case 0:
      analogWrite(GREEN_OUT_PIN,  GREEN_THRESHOLD);
      digitalWrite(RED_OUT_PIN,   LOW);
      digitalWrite(BLUE_OUT_PIN,  LOW);
      break;

    case 1:
      digitalWrite(GREEN_OUT_PIN, LOW);
      analogWrite(RED_OUT_PIN,    RED_THRESHOLD);
      digitalWrite(BLUE_OUT_PIN,  LOW);
      break;

    case 2:
      digitalWrite(GREEN_OUT_PIN, LOW);
      digitalWrite(RED_OUT_PIN,   LOW);
      analogWrite(BLUE_OUT_PIN,   BLUE_THRESHOLD);
      break;

    case 3:
      analogWrite(GREEN_OUT_PIN, GREEN_THRESHOLD);
      analogWrite(RED_OUT_PIN,   RED_THRESHOLD);
      digitalWrite(BLUE_OUT_PIN, LOW);
      break;

    case 4:
      analogWrite(GREEN_OUT_PIN, GREEN_THRESHOLD);
      digitalWrite(RED_OUT_PIN,  LOW);
      analogWrite(BLUE_OUT_PIN,  BLUE_THRESHOLD);
      break;

    case 5:
      digitalWrite(GREEN_OUT_PIN, LOW);
      analogWrite(RED_OUT_PIN,    RED_THRESHOLD);
      analogWrite(BLUE_OUT_PIN,   BLUE_THRESHOLD);
      break;

    case 6:
      analogWrite(GREEN_OUT_PIN, GREEN_THRESHOLD);
      analogWrite(RED_OUT_PIN,   RED_THRESHOLD);
      analogWrite(BLUE_OUT_PIN,  BLUE_THRESHOLD);
      break;

    case 7:
      digitalWrite(GREEN_OUT_PIN, LOW);
      digitalWrite(RED_OUT_PIN,   LOW);
      digitalWrite(BLUE_OUT_PIN,  LOW);
      break;
  }
  statusCount = (statusCount+1) % 8;

  delay(1000);

  Serial.print("Green: ");
  delay(1);
  if (digitalRead(GREEN_IN_PIN) == LOW) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }
  
  Serial.print("Red: ");
  delay(1);
  if (digitalRead(RED_IN_PIN) == LOW) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }

  Serial.print("Blue: ");
  delay(1);
  if (digitalRead(BLUE_IN_PIN) == LOW) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }
  
  Serial.println("");
  delay(1000);
}
