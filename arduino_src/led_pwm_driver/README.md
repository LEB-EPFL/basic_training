# LED PWM Driver

A simple pulse width modulation (PWM) driver for LED control.

## Summary

The PWM signal is a square wave signal that is output on a digital pin. The duty cycle of the square wave determines for how long the signal remains high: a 50% duty cycle means that the square wave signal spends half its time high and half low. On the average, this will halve the apparent brightness of a LED.

The Arduino Nano Every's default PWM frequency is around 960 Hz.

All commands must be terminated with a linefeed (LF) character, i.e. `\n`. To get a list of all commands, simply send `help` to the device.

Whenever the board successfully parses your command, a `0` will be returned as an acknowledgement. Any non-zero response is an error.

## Getting started

Set the PWM duty cycle (i.e. the LED brightness) to maximum. Remember to send a linefeed (LF) terminator at the end:

```console
pwm 255
```

The `255` stands for `ON with max brightness` (100%). To illuminate the LED with half the maximum brightness, send

```console
pwm 127
```

To turn off the LED, send

```console
pwm 0
```

## Setup

This sketch is intended for the Arduino Nano Every, so no special setup is required. Just upload the sketch using the Arduino IDE and use the Serial Monitor to send commands.
