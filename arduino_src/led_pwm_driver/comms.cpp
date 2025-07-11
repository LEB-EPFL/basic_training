#include <Arduino.h>

#include "comms.h"

void clearSerialBuffer();
void parsePWMArgs(const String& args, Message& msg);

///////////////////////////////////////////////////////////////////////////////////////
/// Serial communications
///////////////////////////////////////////////////////////////////////////////////////

// Prints a help message to the screen.
//
// Update this function if LINE_TERMINATOR changes.
void printHelp() {
  Serial.println(F("Available commands:"));
  Serial.println(F("  pwm (0 - 255)\\n"));
  Serial.println(F("  help\\n"));
  Serial.println(F(""));
  Serial.println(F("Note: commands must be terminated with a \\n character."));
}

// Initialize a Message instance to its default values.
void messageInit(Message& msg) {
  msg.cmd = Command::help;
  msg.dutyCycle = 0;
  msg.isValid = true;
  msg.errorMsg = "";
}

// Read from Serial until untilChar char found or char limit read or timeout reached.
// 
// The function returns true when untilChar is found or the input is length limited.
// Otherwise false is returned. untilChar, if found, is returned as last char in String.
//
// If no char limit is desired, then pass 0 for the `char_limit` argument.
// 
// This function call is non-blocking.
bool readStringUntil(String& input, char untilChar, size_t charLimit) {
  static bool timerRunning;
  static unsigned long timerStart;
  static const unsigned long timeout_ms = 1000; // 1 sec; set to 0 for no timeout

  while (Serial.available()) {
    timerRunning = false;

    char c = Serial.read();
    input += c;
    if (c == untilChar) {
      return true;
    }
    if (charLimit && (input.length() >= charLimit)) {
      return true;
    }
    // Restart timer running if the timeout is non-zero.
    if (timeout_ms > 0) {
      timerRunning = true;
      timerStart = millis();
    }
  }

  if (timerRunning && ((millis() - timerStart) > timeout_ms)) {
    timerRunning = false;
    return true;
  }
  
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Message parsing
///////////////////////////////////////////////////////////////////////////////////////////////////
// Parse the string and convert it to a known message format.
void parseMessage(const String& input, Message& msg) {
  // Terminator must be present because serial input has a char limit;
  // exceeding the limit should produce an invalid command.
  if (input.charAt(input.length() - 1) != LINE_TERMINATOR) {
    msg.isValid = false;
    msg.errorMsg = "Command character limit exceeded without finding a line terminator";
    clearSerialBuffer();
    return;
  }
  int verbEnd = input.indexOf(' ');
  String verbStr;
  String argStr;
  if (verbEnd == -1) {
    // verbStr is the whole string; get rid of the line terminator.
    verbStr = input.substring(0, input.length() - 1);
  } else {
    verbStr = input.substring(0, verbEnd);
    argStr = input.substring(verbEnd + 1);
  }

  // Parse the verb part of the command
  msg.isValid = true;
  if (verbStr.equalsIgnoreCase("pwm")) {
    msg.cmd = Command::pwm;
    parsePWMArgs(argStr, msg);
  } else if (verbStr.equalsIgnoreCase("help")) {
    msg.cmd = Command::help;
  } else {
    // Handle unrecognized commands
    msg.isValid = false;
    msg.errorMsg = "Unrecognized command: " + input;
    return;
  }
}

void parsePWMArgs(const String& args, Message& msg) {
  int dutyCycle;
  int n = sscanf(args.c_str(), "%d ", &dutyCycle);
  if (n == 1) {
    msg.dutyCycle = dutyCycle;
  } else {
    msg.isValid = false;
  }

  // Bounds check
  if (dutyCycle < 0 || dutyCycle > 255) {
    msg.isValid = false;
    msg.errorMsg = "Value for duty cycle must be between 0 and 255 inclusive.";
  }
}

void clearSerialBuffer() {
  // Small delay to allow the buffer to fill with any pending characters
  delay(10);

  while (Serial.available() > 0) {
    Serial.read();
  }
}
