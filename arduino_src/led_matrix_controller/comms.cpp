#include <Arduino.h>

#include "comms.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Declarations
///////////////////////////////////////////////////////////////////////////////////////////////////
void clearSerialBuffer();

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Serial communications
///////////////////////////////////////////////////////////////////////////////////////////////////
void messageInit(Message& msg) {
  msg.cmd = Command::draw;
  msg.x = 0;
  msg.y = 0;
  msg.r = 0;
  msg.r2 = 0;
  msg.variant = 0;
  msg.level = 0;
  msg.isValid = false;
  msg.errorMsg = "";
}

// Read from Serial until until_c char found or char limit read or timeout reached.
// 
// The function returns true when until_c is found or the input is length limited. Otherwise false
// is returned. until_c, if found, is returned as last char in String.
//
// If no char limit is desired, then pass 0 for the `char_limit` argument.
// 
// This function call is non-blocking.
bool readStringUntil(String& input, char until_c, size_t char_limit) {
  static bool timerRunning;
  static unsigned long timerStart;
  static const unsigned long timeout_ms = 1000; // 1 sec; set to 0 for no timeout

  while (Serial.available()) {
    timerRunning = false;

    char c = Serial.read();
    input += c;
    if (c == until_c) {
      return true;
    }
    if (char_limit && (input.length() >= char_limit)) {
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

void clearSerialBuffer() {
  // Small delay to allow the buffer to fill with any pending characters
  delay(10);

  while (Serial.available() > 0) {
    Serial.read();
  }
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
  if (verbStr.equalsIgnoreCase("draw")) {
    msg.cmd = Command::draw;
    parseDrawArgs(argStr, msg);
  } else if (verbStr.equalsIgnoreCase("fill")) {
    msg.cmd = Command::fill;
    parseFillArgs(argStr, msg);
  } else if (verbStr.equalsIgnoreCase("brightfield")) {
    msg.cmd = Command::brightfield;
    parseBrightfieldArgs(argStr, msg);
  } else if (verbStr.equalsIgnoreCase("darkfield")) {
    msg.cmd = Command::darkfield;
    parseDarkfieldArgs(argStr, msg);
  } else if (verbStr.equalsIgnoreCase("halfMoon")) {
    msg.cmd = Command::halfMoon;
    parseHalfMoonArgs(argStr, msg);
  } else if (verbStr.equalsIgnoreCase("ring")) {
    msg.cmd = Command::ring;
    parseRingArgs(argStr, msg);
  } else if (verbStr.equalsIgnoreCase("help")) {
    msg.cmd = Command::help;
  } else {
    // Handle unrecognized commands
    msg.isValid = false;
    msg.errorMsg = "Unrecognized command: " + input;
    return;
  }
}

// Parse the arguments for the draw command
void parseDrawArgs(const String& args, Message& msg) {
  int x, y, level;
  int n = sscanf(args.c_str(), "%d %d %d", &x, &y, &level);
  if (n == 3) {
    msg.x = x;
    msg.y = y;
    msg.level = level;
  } else {
    msg.isValid = false;
  }
}

// Parse the arguments for the fill command
void parseFillArgs(const String& args, Message& msg) {
  int level;
  int n = sscanf(args.c_str(), "%d", &level);
  if (n == 1) {
    msg.level = level;
  } else {
    msg.isValid = false;
  }
}

// Parse the arguments for the brightfield command
void parseBrightfieldArgs(const String& args, Message& msg) {
  int x, y, r, level;
  int n = sscanf(args.c_str(), "%d %d %d %d", &x, &y, &r, &level);
  if (n == 4) {
    msg.x = x;
    msg.y = y;
    msg.r = r;
    msg.level = level;
  } else {
    msg.isValid = false;
  }
}

void parseDarkfieldArgs(const String& args, Message& msg) {
  int x, y, r, level;
  int n = sscanf(args.c_str(), "%d %d %d %d", &x, &y, &r, &level);
  if (n == 4) {
    msg.x = x;
    msg.y = y;
    msg.r = r;
    msg.level = level;
  } else {
    msg.isValid = false;
  }
}

void parseHalfMoonArgs(const String& args, Message& msg) {
  int x, y, r, variant, level;
  int n = sscanf(args.c_str(), "%d %d %d %d %d", &x, &y, &r, &variant, &level);
  if (n == 5) {
    msg.x = x;
    msg.y = y;
    msg.r = r;
    msg.variant = variant;
    msg.level = level;
  } else {
    msg.isValid = false;
  }
}

void parseRingArgs(const String& args, Message& msg) {
  int x, y, r, r2, level;
  int n = sscanf(args.c_str(), "%d %d %d %d %d", &x, &y, &r, &r2, &level);
  if (n == 5) {
    msg.x = x;
    msg.y = y;
    msg.r = r;
    msg.r2 = r2;
    msg.level = level;
  } else {
    msg.isValid = false;
  }

  if (msg.r >= msg.r2) {
    msg.isValid = false;
    msg.errorMsg = "Ring inner diameter must be less than outer diameter";
  }
}
