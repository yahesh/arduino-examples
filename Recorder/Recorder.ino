const int BUTTON_IN = 2;
const int LED_PIN   = 13;
const int SOUND_OUT = 11;

int THRESHOLD = 0;

byte PLAYBACK[600];

int PLAYBACK_SIZE = 600;
int PLAYBACK_POS  = 0;
int PLAYBACK_LEN  = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(BUTTON_IN, INPUT);
  digitalWrite(BUTTON_IN, HIGH);
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(SOUND_OUT, OUTPUT);
  digitalWrite(SOUND_OUT, LOW);
  
  /*
  digitalWrite(LED_PIN, HIGH);
  while (millis() < 5000) {
    tone(SOUND_OUT, 500, 20);

    int soundIn = analogRead(A0);
    if (soundIn > THRESHOLD) {
      THRESHOLD = soundIn;
    }

    delay(10);
  }
  Serial.print("THRESHOLD: ");
  Serial.println(THRESHOLD);
  digitalWrite(LED_PIN, LOW);
  */
}

void loop() {
  // when record button is pressed
  if (digitalRead(BUTTON_IN) == LOW) {
    // cancel out all remaining sound output
    delay(100);
    
    // show that we're recording
    digitalWrite(LED_PIN, HIGH);

    int soundIn   = 0;
    int recordPos = 0;
    
    while ((digitalRead(BUTTON_IN) == LOW) &&
           (recordPos < PLAYBACK_SIZE)) {
      soundIn = analogRead(A0);
      
      PLAYBACK[recordPos] = soundIn;
      recordPos++;
      
      delay(30);
    }

    // disable recording LED
    digitalWrite(LED_PIN, LOW);

    PLAYBACK_POS = 0;
    PLAYBACK_LEN  = recordPos;
  } else {
    if (PLAYBACK_LEN > 0) {
        Serial.print("PLAYBACK[");
        Serial.print(PLAYBACK_POS);
        Serial.print("] = ");

      if (PLAYBACK[PLAYBACK_POS] > 100) {
        tone(SOUND_OUT, 750, 20);
        Serial.println(PLAYBACK[PLAYBACK_POS]);
      } else {
        Serial.println("0");
      }
      PLAYBACK_POS = (PLAYBACK_POS+1) % PLAYBACK_LEN;
    }
  }

  delay(1);
}
