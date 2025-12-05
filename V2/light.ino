
void updateLight(State current, State *next, const int ledPins[3], int turnPin, int brakePin) {
  const int turn = digitalRead(turnPin);
  const int brake = digitalRead(brakePin);

  switch(current) {
    case S0:
      setLight(ledPins, 0,0,0);

      if (turn == HIGH) {
        *next = S1;
      } else if (brake == HIGH) {
        *next = S3;
      }
    break;

    case S1:
      setLight(ledPins, 1,0,0);
      
      *next = S2;
    break;

    case S2:
      setLight(ledPins, 1,1,0);

      *next = S3;
    break;

    // Handle all other states as if they were S3, for safety
    default:
      setLight(ledPins, 1,1,1);
      
      if (brake == LOW || turn == HIGH) {
        *next = S0;  
      }
    break;
  }
}

void setLight(const int ledPins[3], bool a, bool b, bool c) {
  const bool light[3] = {a, b, c};

  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPins[i], light[i] ? HIGH : LOW);
  }
}