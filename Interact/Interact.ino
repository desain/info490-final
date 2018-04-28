#include <CapacitiveSensor.h>

CapacitiveSensor touchSensor{4,8};
int const touchSensorResolution = 30;
int const threshold = 1000;

enum class State {
  WaitingForTouch,
  WaitingForResponse
} state = State::WaitingForTouch;

void setup() {
  Serial.begin(9600);
}

void loop() {
  switch(state) {
  case State::WaitingForTouch:
    if (touchSensor.capacitiveSensor(touchSensorResolution) > threshold) {
      state = State::WaitingForResponse;
    }
    break;
  case State::WaitingForResponse: {
    Serial.find('\02');
    String fact = Serial.readStringUntil('\03');
    //TODO something with fact
    state = State::WaitingForTouch;
    break;
  }}
}
