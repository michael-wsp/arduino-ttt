#include <FastLED.h>

#define NUM_LEDS 256
#define DATA_PIN 6
#define COLS 16
#define ROWS 16
#define RED 0x080000
#define GREEN 0x000800
#define BLUE 0x000008
#define BLANK 0x000000

#define BUTTON1_PIN 12
#define BUTTON2_PIN 7
#define BUTTON3_PIN 2

CRGB leds[NUM_LEDS];

enum GameState {
  SelectRow,
  SelectCol,
  PlacePiece,
  GameOver
};

enum GameState gamestate = SelectRow;

unsigned curr_row;
unsigned curr_col;

const unsigned PLAYER_X = 0b01;
const unsigned PLAYER_O = 0b10;
unsigned curr_player = PLAYER_X;
unsigned curr_state[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

void clear(bool dots) {
  for (unsigned x = 0; x < COLS; x++) {
    for (unsigned y = 0; y < ROWS; y++) {
      unsigned curr = translateXY(x, y);
      if (x % 5 == 2 && y % 5 == 2 && dots) {
        leds[curr] = BLUE;
      } else {
        leds[curr] = BLANK;
      }
    }
  }
}

unsigned translateXY(unsigned x, unsigned y) {
  unsigned value = y * COLS;
  if (y & 1) {
    value += COLS - x - 1;
  } else {
    value += x;
  }
  return value;
}

void drawPixel(unsigned x, unsigned y, CRGB color) {
  unsigned pos = translateXY(x, y);
  leds[pos] = color;
}

void drawX(unsigned start_x, unsigned start_y) {
  unsigned x = start_x;
  unsigned y = start_y;
  drawPixel(x, y, RED);
  x += 4;
  drawPixel(x, y, RED);
  y += 1;
  x -= 3;
  drawPixel(x, y, RED);
  x += 2;
  drawPixel(x, y, RED);
  y += 1;
  x -= 1;
  drawPixel(x, y, RED);
  y += 1;
  x -= 1;
  drawPixel(x, y, RED);
  x += 2;
  drawPixel(x, y, RED);
  y += 1;
  x -= 3;
  drawPixel(x, y, RED);
  x += 4;
  drawPixel(x, y, RED);
}

void animDrawX(unsigned start_x, unsigned start_y) {
  unsigned x = start_x + 2;
  unsigned y = start_y + 2;
  drawPixel(x, y, RED);
  FastLED.show();
  delay(100);
  x += 1;
  y += 1;
  drawPixel(x, y, RED);
  x -= 2;
  drawPixel(x, y, RED);
  y -= 2;
  drawPixel(x, y, RED);
  x += 2;
  drawPixel(x, y, RED);
  FastLED.show();
  delay(100);
  x += 1;
  y += 3;
  drawPixel(x, y, RED);
  x -= 4;
  drawPixel(x, y, RED);
  y -= 4;
  drawPixel(x, y, RED);
  x += 4;
  drawPixel(x, y, RED);
  FastLED.show();
  delay(100);
}

void drawO(unsigned start_x, unsigned start_y) {
  unsigned x = start_x;
  unsigned y = start_y;
  drawPixel(x, y, GREEN);
  x += 1;
  drawPixel(x, y, GREEN);
  x += 1;
  drawPixel(x, y, GREEN);
  x += 1;
  drawPixel(x, y, GREEN);
  x += 1;
  drawPixel(x, y, GREEN);
  y += 1;
  drawPixel(x, y, GREEN);
  x -= 4;
  drawPixel(x, y, GREEN);
  y += 1;
  drawPixel(x, y, GREEN);
  x += 2;
  drawPixel(x, y, BLANK);
  x += 2;
  drawPixel(x, y, GREEN);
  y += 1;
  drawPixel(x, y, GREEN);
  x -= 4;
  drawPixel(x, y, GREEN);
  y += 1;
  drawPixel(x, y, GREEN);
  x += 1;
  drawPixel(x, y, GREEN);
  x += 1;
  drawPixel(x, y, GREEN);
  x += 1;
  drawPixel(x, y, GREEN);
  x += 1;
  drawPixel(x, y, GREEN);
}

void resetO(unsigned start_x, unsigned start_y) {
  for (unsigned dx = 0; dx < 5; dx++) {
    for (unsigned dy = 0; dy < 5; dy++) {
      drawPixel(start_x + dx, start_y + dy, BLANK);
    }
  }
}

void animDrawO(unsigned start_x, unsigned start_y) {
  unsigned x = start_x + 2;
  unsigned y = start_y + 2;
  drawPixel(x, y, GREEN);
  FastLED.show();
  delay(100);
  resetO(start_x, start_y);
  x += 1;
  drawPixel(x, y, GREEN);
  y += 1;
  drawPixel(x, y, GREEN);
  x -= 1;
  drawPixel(x, y, GREEN);
  x -= 1;
  drawPixel(x, y, GREEN);
  y -= 1;
  drawPixel(x, y, GREEN);
  y -= 1;
  drawPixel(x, y, GREEN);
  x += 1;
  drawPixel(x, y, GREEN);
  x += 1;
  drawPixel(x, y, GREEN);
  FastLED.show();
  delay(100);
  resetO(start_x, start_y);
  y += 1;
  x += 1;
  drawPixel(x, y, GREEN);
  y += 1;
  drawPixel(x, y, GREEN);
  y += 1;
  drawPixel(x, y, GREEN);
  x -= 1;
  drawPixel(x, y, GREEN);
  x -= 1;
  drawPixel(x, y, GREEN);
  x -= 1;
  drawPixel(x, y, GREEN);
  x -= 1;
  drawPixel(x, y, GREEN);
  y -= 1;
  drawPixel(x, y, GREEN);
  y -= 1;
  drawPixel(x, y, GREEN);
  y -= 1;
  drawPixel(x, y, GREEN);
  y -= 1;
  drawPixel(x, y, GREEN);
  x += 1;
  drawPixel(x, y, GREEN);
  x += 1;
  drawPixel(x, y, GREEN);
  x += 1;
  drawPixel(x, y, GREEN);
  x += 1;
  drawPixel(x, y, GREEN);
  y += 1;
  drawPixel(x, y, GREEN);
  FastLED.show();
  delay(100);
}

void animDraw(unsigned x, unsigned y, unsigned player) {
  if (player == PLAYER_X) {
    animDrawX(x, y);
  } else {
    animDrawO(x, y);
  }
}

void cycle() {
  for (unsigned i = 0; i < 256; i++) {
    leds[i] = RED;
    FastLED.show();
    delay(100);
    leds[i] = BLANK;
  }
}

unsigned getInput() {
  while (true) {
    int b1 = digitalRead(BUTTON1_PIN);
    int b2 = digitalRead(BUTTON2_PIN);
    int b3 = digitalRead(BUTTON3_PIN);
    if (b1 == HIGH) {
      return 0;
    } else if (b2 == HIGH) {
      return 1;
    } else if (b3 == HIGH) {
      return 2;
    }
  }
}

void drawRowSelect(CRGB color) {
  unsigned x = 15;
  unsigned y;
  for (y = 1; y < 15; y += 3) {
    unsigned curr = translateXY(x, y);
    leds[curr] = color;
    y += 1;
    curr = translateXY(x, y);
    leds[curr] = color;
    y += 1;
    curr = translateXY(x, y);
    leds[curr] = color;
  }
}

void drawRowSelected(unsigned row) {
  unsigned x = 15;
  unsigned y = (2 - row) * 5 + 1;
  unsigned curr = translateXY(x, y);
  leds[curr] = BLUE;
  y += 1;
  curr = translateXY(x, y);
  leds[curr] = BLUE;
  y += 1;
  curr = translateXY(x, y);
  leds[curr] = BLUE;
}

void drawColSelect(CRGB color) {
  unsigned x;
  unsigned y = 15;
  for (x = 1; x < 15; x += 3) {
    unsigned curr = translateXY(x, y);
    leds[curr] = color;
    x += 1;
    curr = translateXY(x, y);
    leds[curr] = color;
    x += 1;
    curr = translateXY(x, y);
    leds[curr] = color;
  }
}

void drawColSelected(unsigned col) {
  unsigned x = (2 - col) * 5 + 1;
  unsigned y = 15;
  unsigned curr = translateXY(x, y);
  leds[curr] = BLUE;
  x += 1;
  curr = translateXY(x, y);
  leds[curr] = BLUE;
  x += 1;
  curr = translateXY(x, y);
  leds[curr] = BLUE;
}

// 0 is not primitive
// 1 is lose
// 2 is tie
unsigned primitiveValue(unsigned* state) {
  for (int i = 0; i < 3; i++) {
    unsigned rowstart = i * 3;
    if (state[rowstart] != 0 && state[rowstart] == state[rowstart + 1] && state[rowstart] == state[rowstart + 2]) {
      clear(false);
      delay(500);
      unsigned p = state[rowstart];
      animDraw(10, (2 - i) * 5, p);
      animDraw(5, (2 - i) * 5, p);
      animDraw(0, (2 - i) * 5, p);
      return 1;
    }
    if (state[i] != 0 && state[i] == state[i + 3] && state[i] == state[i + 6]) {
      clear(false);
      delay(500);
      unsigned p = state[i];
      animDraw((2 - i) * 5, 10, p);
      animDraw((2 - i) * 5, 5, p);
      animDraw((2 - i) * 5, 0, p);
      return 1;
    }
  }
  if (state[0] != 0 && state[0] == state[4] && state[0] == state[8]) {
    clear(false);
    delay(500);
    unsigned p = state[0];
    animDraw(10, 10, p);
    animDraw(5, 5, p);
    animDraw(0, 0, p);
    return 1;
  }
  if (state[2] != 0 && state[2] == state[4] && state[2] == state[6]) {
    clear(false);
    delay(500);
    unsigned p = state[2];
    animDraw(10, 0, p);
    animDraw(5, 5, p);
    animDraw(0, 10, p);
    return 1;
  }
  for (int i = 0; i < 9; i++) {
    if (state[i] == 0) {
      return 0;
    }
  }
  return 2;
}

void updateBoard(unsigned* state) {
  for (unsigned pos = 0; pos < 9; pos++) {
    unsigned val = state[8 - pos];
    unsigned draw_x = (pos % 3) * 5;
    unsigned draw_y = (pos / 3) * 5;
    if (val == PLAYER_X) {
      Serial.print("X");
      drawX(draw_x, draw_y);
    } else if (val == PLAYER_O) {
      Serial.print("O");
      drawO(draw_x, draw_y);
    }
  }
}

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  clear(true);
  FastLED.show();
  pinMode(BUTTON1_PIN, INPUT);
  pinMode(BUTTON2_PIN, INPUT);
  pinMode(BUTTON3_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (gamestate == SelectRow) {
    drawRowSelect(BLUE);
    FastLED.show();
    int row = getInput();
    curr_row = row;
    gamestate = SelectCol;
    drawRowSelect(BLANK);
  } else if (gamestate == SelectCol) {
    drawRowSelected(curr_row);
    drawColSelect(BLUE);
    FastLED.show();
    delay(500);
    int col = getInput();
    curr_col = col;
    drawColSelect(BLANK);
    if (curr_state[curr_col + curr_row * 3] == 0) {
      gamestate = PlacePiece;
      drawColSelected(curr_col);
    } else {
      gamestate = SelectRow;
      delay(500);
    }
    FastLED.show();
  } else if (gamestate == PlacePiece) {
    delay(500);
    unsigned pos = curr_row * 3 + curr_col;
    curr_state[pos] = curr_player;
    Serial.print("piece placed at: ");
    Serial.print(curr_row);
    Serial.print(", ");
    Serial.print(curr_col);
    Serial.print("\n");
    Serial.print("\n");
    curr_player ^= 0b11;
    clear(true);
    updateBoard(curr_state);
    FastLED.show();
    if (primitiveValue(curr_state) == 0) {
      gamestate = SelectRow;
    } else {
      Serial.print("gameover\n");
      gamestate = GameOver;
    }
  } else if (gamestate == GameOver) {
    getInput();
    gamestate = SelectRow;
    for (unsigned i = 0; i < 9; i++) {
      curr_state[i] = 0;
    }
    curr_player = PLAYER_X;
    clear(true);
    delay(200);
    FastLED.show();
  }
}
/*
const unsigned POSITIONS[9] = {0, 5, 10, 80, 85, 90, 160, 165, 170}

void doTurn() {
  unsigned value = primitiveValue(curr_state);
  if (value != 0) {
    gamestate = GameOver;
  } else {
    unsigned row, col;
    // get row, col
    unsigned move_pos = row * 3 + col;
    unsigned move_shift = move_pos << 1;
    unsigned move = curr_player << move_shift;
    curr_state = doMove(curr_state, move);
    curr_player ^= 0b11;
  }
}

unsigned doMove(unsigned state, unsigned move) {
  return state | move;
}

unsigned* generateMoves(unsigned state, unsigned player) {
  unsigned* moves = new unsigned[9];
  for (unsigned pos = 0; pos < 9; pos++) {
    unsigned shift = pos << 1;
    if ((state >> shift) & 0b11 == 0) {
      moves[pos] = player << shift;
    }
  }
  return moves;
}
*/