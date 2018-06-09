#ifndef CHARACTER_H
#define CHARACTER_H

#include "nanostation.h"
#include "vector.h"

#define FLAG_NOTHING 0 // when nothing special happens
#define FLAG_DIED 1
#define FLAG_WON 2

#define MAX_SPEED_X 2

// the character is just 1 pixel which simplifies collisions
class Character {
public:
	byte prev_x;
	byte prev_y;
	byte x;
	byte y;

	Vector vel;

public:
	Character(signed char x_, signed char y_);
	Character();
	void draw();
	void animate_death();
	byte update();
	inline char getXDirection() {
		int sx = analogRead(PIN_STICK_X);
		// the spread is between 0 and MAX_SPEED*2 (both included)
		byte spread = (sx + 1023/(MAX_SPEED_X*4)) / (1023/(MAX_SPEED_X*2)); // 1023/(MAX_SPEED*4) to round it up

		return spread - MAX_SPEED_X;
	}
};

#endif /* CHARACTER_H */
