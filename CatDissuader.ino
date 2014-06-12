#define SQUIRT_PIN 7
#define MOTION_PIN 12

typedef enum {
  WAITING, TRIGGERED, TIMEOUT
} state_t;

state_t state;
unsigned long triggered_start_time;
unsigned long timeout_start_time;

void squirt() {
  Serial.println("started squirt");
  digitalWrite(SQUIRT_PIN, HIGH);
  delay(1000);
  digitalWrite(SQUIRT_PIN, LOW);
  Serial.println("ended squirt");
}

void setup() {
  pinMode(SQUIRT_PIN, OUTPUT);
  pinMode(MOTION_PIN, INPUT);
  state = WAITING;
  Serial.begin(57600);
  Serial.println("started");
}

void loop() {
  switch (state) {
    case WAITING:
    if (digitalRead(MOTION_PIN)) {
      Serial.println("triggered");
      state = TRIGGERED;
      triggered_start_time = millis();
      return;
    }
    break;

    case TRIGGERED:
    if (millis() - triggered_start_time > 5000) {
      squirt();
      state = TIMEOUT;
      timeout_start_time = millis();
      return;
    }
    break;

    case TIMEOUT:
    if (millis() - timeout_start_time > 10000) {
      Serial.println("watching");
      state = WAITING;
      return;
    }
    break;
  }
}
