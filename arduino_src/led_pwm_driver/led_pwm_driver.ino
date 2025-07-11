/* A simple pulse width modulation (PWM) driver for LED control.

The PWM signal is a square wave signal that is output on a digital pin. The duty cycle
of the square wave determines for how long the signal remains high: a 50% duty cycle
means that the square wave signal spends half its time high and half low. On the
average, this will halve the apparent brightness of a LED.

The Arduino Nano Every's default PWM frequency is around 960 Hz.
*/

#include "comms.h";

// Main program
const uint8_t PIN = 3;
String input = "";
Message msg;

void setup() {
  Serial.begin(BAUD);
  pinMode(PIN, OUTPUT);

  messageInit(msg);

  printHelp();
}

void loop() {
  if (readStringUntil(input, LINE_TERMINATOR, CHAR_LIMIT)) {
    parseMessage(input, msg);
    if (msg.isValid) {
      doAction(msg);
      Serial.print(String(OK) + LINE_TERMINATOR);
    } else {
      Serial.println(msg.errorMsg);
      Serial.print(String(ERROR) + LINE_TERMINATOR);
    }

    // Clear the input buffer to prepare for the next line.
    input = "";
  }
}

void doAction(const Message& msg) {
  switch (msg.cmd) {
    case Command::pwm:
      analogWrite(PIN, msg.dutyCycle);
      break;
    case Command::help:
      printHelp();
      break;
    default:
      break;
  }
}