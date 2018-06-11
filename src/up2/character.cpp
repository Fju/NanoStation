#include "character.h"
#include "nanostation.h"
#include "text.h"

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
	this->handle_jump();

	this->prev_x = this->x;
	this->prev_y = this->y;

	char next_x = this->get_next_x();
	char nextY = this->y + this->vel_y;
	// prevent from going out of screen
	if (nextY < 0) nextY = 0;
	if (nextY >= SCREEN_HEIGHT) return FLAG_DIED; // you fell -> you die

	char color_collide = bresenham(
		this->x,
		this->y,
		next_x,
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
	register bool colliding = color_collide != COLOR_BLUE;

	// going down & colliding means that
	// - the character is on the ground
	// - the character is wall-jumping
	this->can_jump = colliding && this->vel_y >= 0;

	if (colliding) {
		this->vel_y = 0;
	}

	return FLAG_NOTHING;
}
