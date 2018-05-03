#include "character.h"
#include "nanostation.h"
#include "text.h"
#include <VGAX.h>

#define SENSIBILITY 200

// the character is just 1 pixel which simplifies collisions
Character::Character(signed char x_, signed char y_) :
x(x_), y(y_), prev_x(x_), prev_y(y_), vel(0, 0) {
}

void Character::draw() {
	VGAX::putpixel(this->prev_x, this->prev_y, COLOR_BLUE);
	VGAX::putpixel(this->x, this->y, COLOR_WHITE);
}

void Character::update() {
	int sx = analogRead(PIN_STICK_X);
	int sy = analogRead(PIN_STICK_Y);

	this->vel.x += sx - 512 >> 7;
	if (sy < 512 - SENSIBILITY) this->vel.y -= 3;

	if (this->vel.y < 6) ++this->vel.y;

	this->prev_x = this->x;
	this->prev_y = this->y;
}
