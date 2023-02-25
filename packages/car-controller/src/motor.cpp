#include "motor.h"
#include <Arduino.h>

void setMotor(int p, int m, String state, int speed) {
  if (state == "FORWARD") {
    analogWrite(p, speed);
    analogWrite(m, 0);
  } else if (state == "BACKWARD") {
    analogWrite(p, 0);
    analogWrite(m, speed);
  } else {
    analogWrite(p, 0);
    analogWrite(m, 0);
  }
}