/// Communications datatypes and functions.
///
/// This module contains the datatypes and functions for parsing serial input into
/// commands.
#ifndef COMMS_H
#define COMMS_H

/// Communications configuration
const uint32_t BAUD = 115200;
const uint8_t OK    = 0;
const uint8_t ERROR = 1;

// The maximum number of characters that can be read from Serial.
const size_t CHAR_LIMIT = 16;

// The line terminator character for Serial input.
//
// Update the printHelp function if this changes.
const char LINE_TERMINATOR = '\n';

void printHelp();

// The set of possible commands.
enum class Command {pwm, help};

// Message data after parsing the serial input.
// Each Command uses a non-exclusive subset of the fields.
typedef struct {
  Command cmd;
  uint8_t dutyCycle;
  bool isValid;
  String errorMsg;
} Message;

// Initialize a Message struct with default values.
void messageInit(Message& msg);

// Read from Serial until untilChar char found or char limit read or timeout reached.
// 
// The function returns true when untilChar is found or the input is length limited.
// Otherwise false is returned. untilChar, if found, is returned as last char in String.
//
// If no char limit is desired, then pass 0 for the `charLimit` argument.
// 
// This function call is non-blocking.
bool readStringUntil(String& input, char untilChar, size_t charLimit);

// Parse the string and convert it to a known message format.
void parseMessage(const String& input, Message& msg);

#endif // #COMMS_H
