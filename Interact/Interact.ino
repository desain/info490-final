#include <SoftwareSerial.h>
#include <CapacitiveSensor.h>

char const PRE_FACT = '+';
char const POST_FACT = '+';

int const rxFromEsp = 10;
int const txToEsp = 11;
SoftwareSerial esp{rxFromEsp, txToEsp};

CapacitiveSensor touchSensor{4,8};
int const touchSensorResolution = 30;
int const threshold = 1000;

int const MAX_FACT_LENGTH = 1000;
char factBuffer[MAX_FACT_LENGTH];
int bufCurPos;

enum class State {
  WaitingForTouch,
  WaitingForResponse,
  ReadingFact,
} state = State::WaitingForTouch;

void setup() {
  esp.begin(4800);
  Serial.begin(9600);
  Serial.println("up");
}

void loop() {
  switch(state) {
  case State::WaitingForTouch:
    if (touchSensor.capacitiveSensor(touchSensorResolution) > threshold) {
      state = State::WaitingForResponse;
      Serial.println("OW");
      esp.print('\07');
    }
    break;
  case State::WaitingForResponse:
    if (esp.read() == PRE_FACT) {
      state = State::ReadingFact;
      bufCurPos = 0;
    }
    break;
  case State::ReadingFact: factBuffer[esp.readBytesUntil(POST_FACT, factBuffer, MAX_FACT_LENGTH)] = '\0'; Serial.println(factBuffer); state = State::WaitingForTouch; break; /*{
      char c = esp.read();
      if (c == POST_FACT) {
        factBuffer[bufCurPos] = '\0';
        Serial.println(factBuffer);
        state = State::WaitingForTouch;
      } else if (isAscii(c)) {
        factBuffer[bufCurPos++] = c;
      }
      break;
  }}*/
  }
}
