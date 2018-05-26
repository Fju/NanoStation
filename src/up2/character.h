#ifndef CHARACTER_H
#define CHARACTER_H

#include "vector.h"
#include <VGAX.h>

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
	bool update();
};

#endif /* CHARACTER_H */
