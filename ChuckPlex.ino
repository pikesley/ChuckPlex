#include <Chuck.h>

#define SLEEP 50

const int buttonPin = 2;
volatile int changeMode = false;

int pinCount = 3;

int leftPins[]  = {  7,  6,  5 }; Chuck left(leftPins, pinCount, SLEEP);
int rightPins[] = {  8,  9, 10 }; Chuck right(rightPins, pinCount, SLEEP);

int mode = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(0, pin_ISR, FALLING);
  right.debug(true);
}

void loop() {
  if (changeMode) {
    mode++;
    changeMode = false;
    if (mode > 6) {
      mode = 0;
    }
  }

  switch (mode) {
    case 0:
      clockwise();
      break;
      
    case 1:
      antiClockwise();
      break;

    case 2:
      clockwiseChase();
      break;
      
    case 3:
      antiClockwiseChase();
      break;

    case 4:
      bounce();
      break;

    case 5:
      swing();
      break;

    case 6:
      chaos();
      break;
  }
}

void pin_ISR() {
  changeMode = true;
}

void clockwise() {
  simple(right, left);
}

void antiClockwise() {
  simple(left, right);
}

void clockwiseChase() {
  chase(left, right);
}

void antiClockwiseChase() {
  chase(right, left);
}

void bounce() {
  clockwise();
  antiClockwise();
}

void swing() {
  chase(right, left);
  chase(left, right);
  chase(right, left);
  chase(right, left);
  chase(right, left);

  chase(left, right);
  chase(right, left);
  chase(left, right);
  chase(left, right);
  chase(left, right);
}

void simple(Chuck first, Chuck second) {
  first.forwards();
  second.backwards();
}

void chase(Chuck first, Chuck second) {
  for (int i = 0; i < first.lights; i++) {
    first.lightLed(i);
    second.lightLed((first.lights - i) - 1);
    delay(SLEEP);
  }
  first.resetPins();
  second.resetPins();
}

void chaos() {
  left.lightLed(random(7));
  delay(random(SLEEP * 2));
  right.lightLed(random(7));
  delay(random(SLEEP * 2));
}
