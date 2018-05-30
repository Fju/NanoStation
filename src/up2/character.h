#ifndef CHARACTER_H
#define CHARACTER_H

#include "vector.h"

#define FLAG_NOTHING 0 // when nothing special happens
#define FLAG_DIED 1
#define FLAG_WON 2

class Character {
public:
	byte prev_x;
	byte prev_y;
	byte x;
	byte y;

	Vector vel;

public:
	Character(signed char x_, signed char y_);
	void draw();
	byte update();
};

#endif /* CHARACTER_H */
