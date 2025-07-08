#include <Adafruit_Protomatter.h>
#include <Arduino.h>

#include "comms.h"
#include "drawing.h"

void clearMatrix(Adafruit_Protomatter& matrix) {
  /// Queue the fillScreen command with 0's but do not call matrix.show().
  ///
  /// This allows you to clear the matrix before drawing other patterns.
  matrix.fillScreen(0);
}

void draw(const Message& msg, Adafruit_Protomatter& matrix) {
  matrix.drawPixel(msg.x, msg.y, matrix.color565(msg.level, msg.level, msg.level));
  matrix.show();
}

void fill(const Message& msg, Adafruit_Protomatter& matrix) {
  matrix.fillScreen(matrix.color565(msg.level, msg.level, msg.level));
  matrix.show();
}

void brightfield(const Message& msg, Adafruit_Protomatter& matrix) {
  matrix.fillCircle(msg.x, msg.y, msg.r, matrix.color565(msg.level, msg.level, msg.level));
  matrix.show();
}

void darkfield(const Message& msg, Adafruit_Protomatter& matrix) {
  matrix.fillScreen(matrix.color565(msg.level, msg.level, msg.level));
  matrix.fillCircle(msg.x, msg.y, msg.r, 0);
  matrix.show();
}

void halfMoon(const Message& msg, Adafruit_Protomatter& matrix) {
  int orientation = msg.variant;

  clearMatrix(matrix);

  switch (orientation) {
    case Orientations::TOP:
      matrix.fillCircle(msg.x, msg.y, msg.r, matrix.color565(msg.level, msg.level, msg.level));
      matrix.fillRect(msg.x - msg.r, msg.y, msg.r * 2 + 1, msg.r + 1, 0);
      break;
    case Orientations::BOTTOM:
      matrix.fillCircle(msg.x, msg.y, msg.r, matrix.color565(msg.level, msg.level, msg.level));
      matrix.fillRect(msg.x - msg.r, msg.y - msg.r, msg.r * 2 + 1, msg.r + 1, 0);
      break;
    case Orientations::RIGHT:
      matrix.fillCircle(msg.x, msg.y, msg.r, matrix.color565(msg.level, msg.level, msg.level));
      matrix.fillRect(msg.x - msg.r, msg.y - msg.r, msg.r + 1, msg.r * 2 + 1, 0);
      break;
    case Orientations::LEFT:
      matrix.fillCircle(msg.x, msg.y, msg.r, matrix.color565(msg.level, msg.level, msg.level));
      matrix.fillRect(msg.x, msg.y - msg.r, msg.r + 1, msg.r * 2 + 1, 0);
      break;
    default:
      break;
  }

  matrix.show();
}
