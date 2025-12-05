
// State management
enum State {S0, S1, S2, S3};

enum State currentLeftS     = S0;
enum State nextLeftS        = S0;
unsigned long lastLeftTick  = 0;
enum State currentRightS    = S0;
enum State nextRightS       = S0;
unsigned long lastRightTick = 0;


const bool debug = 1; // If true, then debugs messages will be printed in the terminal

// Pins
const int leftPin   = 4;
const int rightPin  = 2;
const int brakePin  = 3;

const int leftLeds[3]   = {11, 12, 13};
const int rightLeds[3]  = {10, 9, 8};


void setup() {
  // Set LED pins
  for (int i = 0; i < 3; i++) {
    pinMode(leftLeds[i],  OUTPUT);
    pinMode(rightLeds[i], OUTPUT);
  };

  // Set buttons
  pinMode(leftPin,  INPUT);
  pinMode(rightPin, INPUT);
  pinMode(brakePin, INPUT);

  // Set terminal if debug
  if (debug) {
    Serial.begin(9600);
  }
}

void loop() {
  // Update light states
  stateMachine(currentLeftS,  nextLeftS, lastLeftTick, debug, "Left light");
  stateMachine(currentRightS, nextRightS, lastRightTick, debug, "Right light");

  // Run light logic
  updateLight(
    currentLeftS,
    &nextLeftS,
    leftLeds,
    leftPin,
    brakePin
  );
  updateLight(
    currentRightS,
    &nextRightS,
    rightLeds,
    rightPin,
    brakePin
  );
}