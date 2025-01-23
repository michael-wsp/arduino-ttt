# arduino-ttt

A basic tic-tac-toe game for use on Arduino with a 16x16 WS2812B LED matrix. Makes use of the FastLED library for LED control.

Uses the following pin assignments, which may need to be adjusted if used on other setups:
  LED data (output) -> 6
  Button 1 (input) -> 12
  Button 2 (input) -> 7
  Button 3 (input) -> 2

The buttons are used to select row and column individually.
