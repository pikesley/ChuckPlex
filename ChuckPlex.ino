#include <Chuck.h>

#define SLEEP 50

const int buttonPin = 2;
volatile int changeMode = false;

int pinCount = 3;

int pins0[]        = {  3,  4,  5 }; Chuck chuck0(pins0, pinCount, SLEEP);
int reversePins0[] = {  5,  4,  3 }; Chuck reverseChuck0(reversePins0, pinCount, SLEEP);
int pins1[]        = {  8,  9, 10 }; Chuck chuck1(pins1, pinCount, SLEEP);
int reversePins1[] = { 10,  9,  8 }; Chuck reverseChuck1(reversePins1, pinCount, SLEEP);

int mode = 6;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(0, pin_ISR, FALLING);
}

void loop() {
  if (changeMode) {
    mode++;
    changeMode = false;
    if (mode > 7) {
      mode = 0;
    }
  }

  switch (mode) {
    case 0:
      simple();
      break;
    case 1:
      chase();
      break;
    case 2:
      flail();
      break;
    case 3:
      swing();
      break;
    case 4:
      halfChase();
      break;
    case 5:
      chaos();
      break;
    case 6:
      crawler(3);
      break;
    case 7:
      fullBounce();
      break;
  }
}

void pin_ISR() {
  changeMode = true;
}

void simple() {
  serial(chuck0, reverseChuck1);
}

void crawler(int width) {
  chuck0.sleep = 30;
  reverseChuck1.sleep = 30;
  int a[chuck0.lights];
  for (int i = 0; i < chuck0.lights; i++) {

    for (int j = 0; j < chuck0.lights; j++) {
      a[j] = 0;
    }

    for (int k = i; k < i + width; k++) {
      a[k] = 1;
      if (k > chuck0.lights - width) {
        a[k - chuck0.lights] = 1;
      }
    }

    chuck0.lightSeveral(a);
    reverseChuck1.lightSeveral(a);

    delay(SLEEP);
  }

  chuck0.sleep = SLEEP;
  reverseChuck1.sleep = SLEEP;
}

void chaos() {
  chuck0.lightLed(random(7));
  delay(SLEEP / 2);
  chuck1.lightLed(random(7));
  delay(SLEEP / 2);
}

void chase() {
  parallel(chuck0, reverseChuck1);
}

void halfChase() {
  simple();
  chase();
  chase();
}

void flail() {
  parallel(chuck0, reverseChuck1);
  parallel(reverseChuck0, chuck1);
}

void halfBounce() {
  parallel(chuck0, chuck1);
  parallel(reverseChuck0, reverseChuck1);
}

void fullBounce() {
  serial(chuck0, reverseChuck1);
  serial(chuck1, reverseChuck0);
}

void swing() {
  for (int i = 0; i < random(4); i++) {
    parallel(chuck0, reverseChuck1);
    parallel(reverseChuck0, chuck1);
  }
  for (int i = 0; i < random(10); i++) {
    parallel(chuck0, reverseChuck1);
  }

  for (int i = 0; i < random(4); i++) {
    parallel(chuck1, reverseChuck0);
    parallel(reverseChuck1, chuck0);
  }
  for (int i = 0; i < random(10); i++) {
    parallel(chuck1, reverseChuck0);
  }
}

// generics

void serial(Chuck first, Chuck second) {
  for (int i = 0; i < first.lights; i++) {
    Serial.println(first.lightLed(i));
    delay(SLEEP);
  }
  first.resetPins();

  for (int i = 0; i < second.lights; i++) {
    Serial.println(second.lightLed(i));
    delay(SLEEP);
  }
  second.resetPins();
}

void parallel(Chuck first, Chuck second) {
  for (int i = 0; i < first.lights; i++) {
    Serial.println(first.lightLed(i));
    Serial.println(second.lightLed(i));
    delay(SLEEP);
  }
  first.resetPins();
  second.resetPins();
}
