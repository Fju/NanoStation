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

void bresenham(char x0, char y0, char x1, char y1) {
	char dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	char dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
	char err = (dx>dy ? dx : -dy)/2, e2;

	for(;;) {
		VGAX::putpixel(x0, y0, COLOR_WHITE);
		if (x0==x1 && y0==y1) return; // end of the line
		e2 = err;
		if (e2 >-dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
}

void Character::update() {
	int sx = analogRead(PIN_STICK_X);
	int sy = analogRead(PIN_STICK_Y);

	this->vel.x += sx - 512 >> 7;
	if (sy < 512 - SENSIBILITY) this->vel.y -= 3;

	if (this->vel.y < 6) ++this->vel.y;

	this->prev_x = this->x;
	this->prev_y = this->y;

	// this->x += this->vel.x;
	// this->y += this->vel.y;

	// logging
	// VGAX::fillrect(10, 10, 50, 30, COLOR_BLUE);
	// drawInt(this->vel.x, 10, 10, COLOR_YELLOW);
	// drawInt(this->vel.y, 10, 20, COLOR_YELLOW);

	bresenham(10, 10, 11, 12);
}
