#ifndef CHARACTER_H
#define CHARACTER_H

#include "nanostation.h"
#include <VGAX.h>

#define FLAG_NOTHING 0 // when nothing special happens
#define FLAG_DIED 1
#define FLAG_WON 2

#define MAX_SPEED_X 2
#define MAX_SPEED_Y 3
#define JUMP_SPEED (-2)

#define INIT_POS_X 3
#define INIT_POS_Y 49

// the character is just 1 pixel which simplifies collisions
class Character {
private:
	char prev_x;
	char prev_y;
	char x;
	char y;
	char vel_y;
	bool can_jump;
	byte jump_time;

private:
	inline char get_next_x() {
		char next_x = this->x + this->getXDirection();

		if (next_x < 0) return 0;
		if (next_x >= SCREEN_WIDTH) return SCREEN_WIDTH - 1;

		return next_x;
	}

	inline void handle_jump() {
		if (this->vel_y < MAX_SPEED_Y && jump_time % 2 == 0) ++this->vel_y; // % to make it fall slower
		++this->jump_time;
		if (digitalRead(PIN_BUTTON_B) == HIGH && this->can_jump) {
			this->vel_y = JUMP_SPEED;
			this->jump_time = 1; // stays longer at MAX_SPEED
		}
	}

public:
	inline Character(signed char x_, signed char y_) :
	x(x_), y(y_), prev_x(x_), prev_y(y_), vel_y(0), can_jump(false), jump_time(0) {
	};
	inline Character() :
	Character(INIT_POS_X, INIT_POS_Y) {
	};

	inline void force_draw() {
		VGAX::putpixel(this->prev_x, this->prev_y, COLOR_BLUE);
		VGAX::putpixel(this->x, this->y, COLOR_WHITE);
	}
	inline void draw() {
		if (this->prev_x == this->x && this->prev_y == this->y) return;

		this->force_draw();
	}
	inline void Character::animate_death() {
		for (byte i = 1; i <= 3; ++i) {
			VGAX::fillrect(this->x - i, this->y - i, 1 + i*2, 1 + i*2, COLOR_WHITE);
			VGAX::delay(33);
		}
	}

	byte update();
	inline char getXDirection() {
		int sx = analogRead(PIN_STICK_X);
		// the spread is between 0 and MAX_SPEED*2 (both included)
		byte spread = (sx + 1023/(MAX_SPEED_X*4)) / (1023/(MAX_SPEED_X*2)); // 1023/(MAX_SPEED*4) to round it up

		return spread - MAX_SPEED_X;
	}
};

#endif /* CHARACTER_H */
