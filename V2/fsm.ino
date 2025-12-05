
const unsigned long stateInterval = 600; // The duration of each state in milliseconds.

void stateMachine(State &current, State &next, unsigned long &lastInterval, bool debug, char stateName[3]) {
  unsigned long now = millis();

  if (now - lastInterval >= stateInterval) {
    lastInterval = now;     // update last tick
    current = next;         // move to next state

    if (debug) {
      Serial.print("Current ");
      Serial.print(stateName);
      Serial.print(" state: ");
      Serial.println((int)current); 
    }
  }
}