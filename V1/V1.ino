// Set states
enum State {
  S0, S1, S2, S3, S4
};
enum State nextState = S0;
enum State currentState = S0;

// Set pins
const int buttonPin = 2;
const int ledPins[3] = {13, 12, 11};  // LED pins
const int blinkerPin = 8;

// Set stateMachine
const int tickSpeed = 600; // Adjust tick speed of state changes in milliseconds.
int lastTick = 0;

// Set components
int button = 0;
const int blinkerFreq = 200;

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(2, INPUT);

  lastTick = millis();
  Serial.begin(9600);
}

void loop() {
  stateMachine();

  button = digitalRead(buttonPin); // Read button state each tick

  switch(currentState) {
    case S0:
      setLight(0,0,0);
      noTone(blinkerPin);

      if (button == HIGH) {
        nextState = S1;
      };
    break;

    case S1:
      setLight(1,0,0);
      tone(blinkerPin, blinkerFreq);
      nextState = S2;
    break;

    case S2:
      setLight(1,1,0);
      noTone(blinkerPin);

      nextState = S3;
    break;

    default:
      setLight(1,1,1);
      tone(blinkerPin, blinkerFreq);
      
      nextState = S0;
    break;
  }

  delay(100);
}

void setLight(bool a, bool b, bool c) {
  const bool light[] = {a, b, c};

  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPins[i], light[i] ? HIGH : LOW);
  }
}

void stateMachine() {
  if (millis() >= (lastTick + tickSpeed)) {
    lastTick = millis();
    currentState = nextState;
    Serial.println(String("State: ") + currentState); // Log current state for debugging
  }
}