#define SLEEP 20
#define DEBUG 0
#define PATTERN 1

int pins[] = { 3, 4, 5, 6 };
int pinCount = 4;
int lights = 12;

void setup() {
  if (DEBUG == 1) {
    Serial.begin(9600);
  }
  inputise();
}

void loop() {
  switch (PATTERN) { 
    case 0:   
      simple();
      break;

    case 1:
      roller(3);
      break;
  }
}

void simple() {
  for (int i = 0; i < lights; i++) {
    lightLED(i);
    delay(SLEEP);
  }
}

void roller(int width) {
  int counter = 0;
  int a[lights];
  for (int j = 0; j < lights; j++) {
    for (int i = 0; i < lights; i++) {
      a[i] = 0;
      int offset = counter + width;
      if (i >= counter && i < offset) {
        a[i] = 1;
      }
      if (offset > lights) {
        for (int k = 0; k < offset - lights; k++) {
          a[k] = 1;
        }
      }
    }
    lightElements(a, width);
    counter++;
    delay(SLEEP);
  }
}

void lightElements(int list[], int width) {
  for (int t = 0; t < round(float(SLEEP) / float(width)); t++) {
    for (int i = 0; i < lights; i++) {
      if (list[i] == 1) {
        lightLED(i);
        delay(1);
      }
    }
  }
}

void inputise() {
  for (int i = 0; i < pinCount; i++) {
    pinMode(pins[i], INPUT);
  }
}

void resetPins() {
  inputise();
  for (int i = 0; i < pinCount; i++) {
    digitalWrite(pins[i], LOW);
  }
}

void setPins(int highIndex, int lowIndex) {
  if (DEBUG == 1) {
    Serial.print(pins[highIndex]);
    Serial.print(" HIGH, ");
    Serial.print(pins[lowIndex]);
    Serial.println(" LOW");
  }
  resetPins();

  pinMode(pins[highIndex], OUTPUT);
  pinMode(pins[lowIndex], OUTPUT);

  digitalWrite(pins[highIndex], HIGH);
  digitalWrite(pins[lowIndex], LOW);
}

void lightLED(int index) {
  int bracket = lights / pinCount;
  int left = index / bracket;
  if (DEBUG == 1) {
    Serial.print(bracket);
    Serial.print(", ");
    Serial.print(index);
    Serial.print(" ... ");
  }

  int valids[pinCount - 1];
  int bump = 0;
 
  for (int i = 0; i < pinCount - 1; i++) {
    if (i == left) {
      bump = 1;
    }

    valids[i] = i + bump;
  }

  int right = valids[index % (pinCount - 1)];
  if (DEBUG == 1) {
    Serial.print(left);
    Serial.print(" - [ ");
    Serial.print(valids[0]);
    Serial.print(", ");
    Serial.print(valids[1]);
    Serial.print(" ] ");
  }

  setPins(left, right);
}


