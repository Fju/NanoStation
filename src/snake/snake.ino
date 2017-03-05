#include <VGAX.h>
#include <avr/pgmspace.h>

#include "text.h"
#include "nanostation.h"

#define COLOUR_WHITE        3
#define COLOUR_BLUE         2
#define COLOUR_YELLOW       1
#define COLOUR_BLACK        0

#define GAME_BORDER         2
#define GAME_WIDTH          (80 - GAME_BORDER * 2)
#define GAME_HEIGHT         (VGAX_HEIGHT - GAME_BORDER * 2)

#define DRAW_BORDER         vga.fillrect(0, 0, GAME_WIDTH + GAME_BORDER * 2, GAME_HEIGHT + GAME_BORDER * 2, COLOUR_YELLOW);
#define CLEAR_GAME          vga.fillrect(GAME_BORDER, GAME_BORDER, GAME_WIDTH, GAME_HEIGHT, COLOUR_BLACK);


const char str_title[] PROGMEM = "SNAKE";
const char str_game_over[] PROGMEM = "GAME OVER";
const char str_score[] PROGMEM = "SCORE";
const char str_instructions[] PROGMEM = "PRESS A BUTTON TO START";


VGAX vga;

//game variables
byte gameState;
byte length;
byte score, last_score;
char vel_x, vel_y;
byte last_x[64];
byte last_y[64];

byte spawn_timer;
byte food_x, food_y;
boolean food;


byte stick_pos; // [ up ] [ down ] [ right ] [ left ] //4 bit
byte buttons; // [ btn1 ] [ btn2 ] //2 bit

void processInputs() {
  stick_pos = 0;
  buttons = 0;

  int sx = map(analogRead(PIN_STICK_X), 178, 871, 0, 1000);
  int sy = map(analogRead(PIN_STICK_Y), 206, 860, 0, 1000);
  if (sx < 140) stick_pos |= 2;
  if (sx > 860) stick_pos |= 1;
  if (sy < 140) stick_pos |= 4;
  if (sy > 860) stick_pos |= 8;

  if (digitalRead(PIN_BUTTON_A) == HIGH) buttons |= 1;
  if (digitalRead(PIN_BUTTON_B) == HIGH) buttons |= 2;
  if (digitalRead(PIN_STICK_BUTTON) == HIGH) buttons |= 4;
}




void reset() {
  vga.clear(COLOUR_BLACK);
  DRAW_BORDER;
  CLEAR_GAME;

  score = 0;
  last_score = 255;
  vel_x = -1;
  vel_y = 0;
  length = 3;

  food = false;
  spawn_timer = 0;

  last_x[0] = GAME_WIDTH / 2;
  last_y[0] = GAME_HEIGHT / 2;
}


void setup() {
  randomSeed(analogRead(A0)); //generate random seed
  vga.begin();
  vga.clear(COLOUR_BLUE);

  gameState = 0;

  byte width_title = getWidth(str_title, true);
  byte width_instr = getWidth(str_instructions, true);
  drawTextPROGMEM(str_title, (VGAX_WIDTH - width_title) / 2, 20, COLOUR_YELLOW);
  drawTextPROGMEM(str_instructions, (VGAX_WIDTH - width_instr) / 2, 40, COLOUR_WHITE);
}

void loop() {
  processInputs();

  if (gameState == 1) {
    if (stick_pos & 1 && vel_x != 1) {
      vel_x = -1;
      vel_y = 0;
    } else if (stick_pos & 2 && vel_x != -1) {
      vel_x = 1;
      vel_y = 0;
    } else if (stick_pos & 4 && vel_y != -1) {
      vel_x = 0;
      vel_y = 1;
    } else if (stick_pos & 8 && vel_y != 1) {
      vel_x = 0;
      vel_y = -1;
    }

    boolean gameover = false;

    if (last_x[0] + vel_x < 0 || last_x[0] + vel_x > GAME_WIDTH - 1 || last_y[0] + vel_y < 0 || last_y[0] + vel_y > GAME_HEIGHT - 1) {
      gameover = true;
    } else {
      if (last_score != score) {
        char scoreStr[4];
        scoreStr[3] = 0;
        char *scrptr = &scoreStr[2];
        byte s = score, sl = 3;
        while (sl--) {
          *scrptr = (s % 10) + 48;
          s /= 10;
          scrptr--;
        }

        byte twidth = getWidth(scoreStr, false);
        vga.fillrect(VGAX_WIDTH - twidth - 3, 10, twidth, FNT_HEIGHT, COLOUR_BLACK);

        drawText(scoreStr, VGAX_WIDTH - twidth - 3, 10, COLOUR_WHITE);
        drawTextPROGMEM(str_score, VGAX_WIDTH - 23, 3, COLOUR_YELLOW);
      }

      last_score = score;

      byte l = length;
      while (l--) {
        if (l == length - 1) vga.putpixel(last_x[l] + GAME_BORDER, last_y[l]+ GAME_BORDER, COLOUR_BLACK);
        if (l == 0) {
          last_x[l] += vel_x;
          last_y[l] += vel_y;
        } else {
          last_x[l] = last_x[l - 1];
          last_y[l] = last_y[l - 1];
        }

        vga.putpixel(last_x[l] + GAME_BORDER, last_y[l] + GAME_BORDER, COLOUR_WHITE);
      }

      byte cx = last_x[0], cy = last_y[0];
      l = length;
      while (l--) {
        if (l != 0 && last_x[l] == cx && last_y[l] == cy) {
          gameover = true;
          break;
        }
      }

      if (cx == food_x && cy == food_y) {
        length++;
        l = length;
        while (--l != 0) {
          last_x[l] = last_x[l - 1];
          last_y[l] = last_y[l - 1];
        }
        last_x[0] = cx;
        last_y[0] = cy;

        food = false;
        spawn_timer = 0;
        score++;
      }

      if (!food) {
        spawn_timer = ++spawn_timer % 30; //30 * 150ms
        if (spawn_timer == 0) {
          food_x = random(GAME_WIDTH);
          food_y = random(GAME_HEIGHT);
          food = true;
        }
      } else vga.putpixel(food_x + GAME_BORDER, food_y + GAME_BORDER, COLOUR_BLUE);
    }

    if (gameover) {
      byte width_game_over = getWidth(str_game_over, true);
      drawTextPROGMEM(str_game_over, (GAME_WIDTH - width_game_over) / 2 + GAME_BORDER, 40, COLOUR_BLUE);
      gameState = 0; //switch game state to Game Over      
    }
    if (score < 4) vga.delay(100);
    else if (score >= 4 && score < 8) vga.delay(80);
    else if (score >= 8 && score < 12) vga.delay(60);
    else if (score >= 12 && score < 16) vga.delay(40);
    else vga.delay(33);

  } else { //Game Over    
    if (buttons) {
      reset();
      gameState = 1;
    }
    vga.delay(20);
  }
}
