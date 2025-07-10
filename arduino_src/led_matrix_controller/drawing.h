/// Configuration and commands for the LED matrix.
#ifndef DRAWING_H
#define DRAWING_H

#include <Adafruit_Protomatter.h>

#include "comms.h"
#include "drawing.h"

enum Orientations {
  TOP = 0,
  BOTTOM = 1,
  RIGHT = 2,
  LEFT = 3
};

// Draw a single pixel on the LED matrix.
void draw(const Message& msg, Adafruit_Protomatter& matrix);

// Fill the LED matrix with a single value.
void fill(const Message& msg, Adafruit_Protomatter& matrix);

// Draw a circle of pixels on the LED matrix.
void brightfield(const Message& msg, Adafruit_Protomatter& matrix);

// Draw a circle of dark pixels on bright background on the LED matrix.
void darkfield(const Message& msg, Adafruit_Protomatter& matrix);

// Draw a half moon pattern on the LED matrix.
void halfMoon(const Message& msg, Adafruit_Protomatter& matrix);

// Draw a ring pattern on the LED matrix.
void ring(const Message& msg, Adafruit_Protomatter& matrix);

#endif // #DRAWING_H
