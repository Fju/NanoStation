#include "character.h"
#include "nanostation.h"
#include "text.h"
#include <VGAX.h>

#define SENSIBILITY 200
#define MAX_SPEED_Y 4

#define INIT_POS_X 10
#define INIT_POS_Y 49

Character::Character() :
Character(INIT_POS_X, INIT_POS_Y) {
}
// the character is just 1 pixel which simplifies collisions
Character::Character(signed char x_, signed char y_) :
x(x_), y(y_), prev_x(x_), prev_y(y_), vel(0, 0) {
}

void Character::draw() {
	VGAX::putpixel(this->prev_x, this->prev_y, COLOR_BLUE);
	VGAX::putpixel(this->x, this->y, COLOR_WHITE);
}

char bresenham(char x0, char y0, char x1, char y1, char * collisionX, char * collisionY) {
	char dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	char dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
	char err = (dx>dy ? dx : -dy)/2, e2;

	char return_color = COLOR_BLUE;

	for(;;) {
		if (x0 >= x1 && y0 >= y1) {
			*collisionX = x1;
			*collisionY = y1;
			return return_color; // end of the line
		}

		e2 = err;
		if (e2 > -dx) {
			err -= dy;
			char futureX = x0 + sx;
			return_color = VGAX::getpixel(futureX, y0);
			if (return_color == COLOR_BLACK) {
				--x1;
				continue;
			} else if (return_color != COLOR_BLUE) {
				return return_color;
			}
			x0 = futureX;
		}
		if (e2 < dy) {
			err += dx;
			char futureY = y0 + sy;
			return_color = VGAX::getpixel(x0, futureY);
			if (return_color == COLOR_BLACK) {
				--y1;
				continue;
			} else if (return_color != COLOR_BLUE) {
				return return_color;
			}
			y0 = futureY;
		}
	}

	return return_color;
}

byte Character::update() {
	this->vel.x += this->getXDirection();

	if (this->vel.y < MAX_SPEED_Y) ++this->vel.y;

	this->prev_x = this->x;
	this->prev_y = this->y;

	char nextX = this->x + this->vel.x;
	char nextY = this->y + this->vel.y;

	// prevent from going out of screen
	if (nextX <= 0) nextX = 0;
	if (nextX > 120) nextX = 120;
	if (nextY <= 0) nextY = 0;

	if (nextY > 60) return FLAG_DIED; // you fell -> you die

	char color_collide = bresenham(
		this->x,
		this->y,
		nextX,
		nextY,
		&this->x,
		&this->y
	);

	switch(color_collide) {
		case COLOR_YELLOW:
			return FLAG_DIED;
		case COLOR_WHITE:
			return FLAG_WON;
	}
	if (color_collide != COLOR_BLUE) {
		this->vel.y = 0;
		if (digitalRead(PIN_BUTTON_B) == HIGH) this->vel.y = -MAX_SPEED_Y;
	}
	this->vel.x = 0;
	return FLAG_NOTHING;
}
