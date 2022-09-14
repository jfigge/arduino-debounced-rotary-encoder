// ************************************************************
// Software de-bounced rotary encoder example
// ************************************************************
// The sketch uses a jelly-bean rotary encoder with no special 
// hardware debouncing. For best performance the Clk & Dt lines
// (also known as A & B) should be connected to interrupt lines
// For the arduino nano this would be pins 2 & 3.  The switch
// can be connected anywhere, but for this sketch it's on pin 4

void rotaryEncoderInterrupt() {
  static uint8_t states[] = {0,1,4,0, 0,1,1,2, 2,1,3,2, 0,3,3,2, 0,4,4,5, 5,6,4,5, 0,6,6,5};
  static uint8_t last_state = 0;
  uint8_t state = states[((PIND & B00001100) >> 2) | (last_state << 2)];
  if (state == 0) {
    if (last_state == 6) {
      Serial.println("Left");
    } else if (last_state == 3) {
      Serial.println("Right");
    }
  }
  last_state = state;
}

void setup() {
  Serial.begin(57600);
  Serial.println("Rotary encoder example, by Jason Figge");

  pinMode(2, INPUT);        // Pin A
  pinMode(3, INPUT);        // Pin B
  pinMode(4, INPUT_PULLUP); // Switch
  attachInterrupt(digitalPinToInterrupt(2), rotaryEncoderInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), rotaryEncoderInterrupt, CHANGE);
}

void loop() {
  static uint8_t last_switchState = HIGH;
  uint8_t switchState = PIND & B00010000 ? HIGH : LOW;
  if (last_switchState != switchState) {
    Serial.println(switchState == LOW ? "Down:" : "Up:");
    last_switchState = switchState;
  }
}
