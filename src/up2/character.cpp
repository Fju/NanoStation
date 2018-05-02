#include "character.h"
#include "nanostation.h"
#include "text.h"
#include <VGAX.h>

// the character is just 1 pixel which simplifies collisions
Character::Character(signed char x_, signed char y_) :
x(x_), y(y_), prev_x(x_), prev_y(y_), vel(0, 0) {
}

void Character::draw() {
	VGAX::putpixel(this->prev_x, this->prev_y, COLOR_BLUE);
	VGAX::putpixel(this->x, this->y, COLOR_WHITE);
}

void Character::update() {
	this->prev_x = this->x;
	this->prev_y = this->y;
}
