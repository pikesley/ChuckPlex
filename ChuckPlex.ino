#include <Chuck.h>

#define SLEEP 50

int pinCount = 3;

int pins0[]        = {  3,  4,  5 }; Chuck chuck0(pins0, pinCount);
int reversePins0[] = {  5,  4,  3 }; Chuck reverseChuck0(reversePins0, pinCount);
int pins1[]        = {  8,  9, 10 }; Chuck chuck1(pins1, pinCount);
int reversePins1[] = { 10,  9,  8 }; Chuck reverseChuck1(reversePins1, pinCount);

void setup() {
  chuck0.sleep = SLEEP;
  chuck1.sleep = SLEEP;
  reverseChuck0.sleep = SLEEP;
  reverseChuck1.sleep = SLEEP;
}

void loop() {
  simple();
  chase();
  flail();
  halfBounce();
  fullBounce();
  swing();
  halfChase();
}

void simple() {
  serial(chuck0, reverseChuck1);
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
  parallel(chuck0, reverseChuck1);
  parallel(reverseChuck0, chuck1);
  parallel(chuck0, reverseChuck1);
  parallel(chuck0, reverseChuck1);
  parallel(chuck0, reverseChuck1);

  parallel(chuck1, reverseChuck0);
  parallel(reverseChuck1, chuck0);
  parallel(chuck1, reverseChuck0);
  parallel(chuck1, reverseChuck0);
  parallel(chuck1, reverseChuck0);
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

/*void roller(int width) {
  int counter = 0;
  int a[chuck.lights];
  for (int j = 0; j < chuck.lights; j++) {
    for (int i = 0; i < chuck.lights; i++) {
      a[i] = 0;
      int offset = counter + width;
      if (i >= counter && i < offset) {
        a[i] = 1;
      }
      if (offset > chuck.lights) {
        for (int k = 0; k < offset - chuck.lights; k++) {
          a[k] = 1;
        }
      }
    }
    chuck.lightSeveral(a, width);
    counter++;
    delay(SLEEP);
  }
}*/
