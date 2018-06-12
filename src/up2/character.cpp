#include "character.h"
#include "nanostation.h"
#include "text.h"

// modified bresenham
// the idea is to ray cast where the (1px) character can go without being interupted by platforms
char bresenham(char x0, char y0, char x1, char y1, char * collisionX, char * collisionY) {
	char dx = abs(x1-x0);
	char sx = x0<x1 ? 1 : -1;
	char dy = abs(y1-y0);
	char sy = y0<y1 ? 1 : -1;
	char err = (dx>dy ? dx : -dy)/2, e2;

	char return_color = COLOR_BLUE;

	for(;;) {
		if (x0 == x1 && y0 == y1) {
			*collisionX = x1;
			*collisionY = y1;
			break; // end of the line
		}

		e2 = err;
		if (e2 < dy) {
			err += dx;
			char futureY = y0 + sy;
			byte color = VGAX::getpixel(x0, futureY);
			switch (color) {
				case COLOR_BLUE:
					y0 = futureY;
					break;
				case COLOR_BLACK: // platform
					if (y0 != y1) y1 -= sy; // we may be able to move along the other axis
					return_color = color;
					continue;
				default:
					return color;
			}
		}
		if (e2 > -dx) {
			err -= dy;
			char futureX = x0 + sx;
			byte color = VGAX::getpixel(futureX, y0);
			switch (color) {
				case COLOR_BLUE:
					x0 = futureX;
					break;
				case COLOR_BLACK: // platform
					if (x1 != x0) x1 -= sx; // we may be able to move along the other axis
					return_color = color;
					continue;
				default:
					return color;
			}
		}
	}

	return return_color;
}

byte Character::update() {
	this->handle_jump();

	this->prev_x = this->x;
	this->prev_y = this->y;

	char next_x = this->get_next_x();
	char next_y = this->y + this->vel_y;
	// prevent from going out of screen
	if (next_y < 0) next_y = 0;
	if (next_y >= SCREEN_HEIGHT) return FLAG_DIED; // you fell -> you die

	// logging
	// VGAX::fillrect(10, 10, 50, 30, COLOR_BLUE);
	// drawInt(this->vel_y, 10, 20, COLOR_YELLOW);
	// drawInt(this->y, 30, 20, COLOR_YELLOW);
	// drawInt(next_y, 40, 20, COLOR_YELLOW);

	char color_collide = bresenham(
		this->x,
		this->y,
		next_x,
		next_y,
		&this->x,
		&this->y
	);

	switch(color_collide) {
		case COLOR_YELLOW:
			return FLAG_DIED;
		case COLOR_WHITE:
			return FLAG_WON;
	}
	bool colliding = color_collide != COLOR_BLUE;

	// going down & colliding means that
	// - the character is on the ground
	// - the character is wall-jumping
	this->can_jump = colliding && this->vel_y >= 0;

	if (colliding) {
		this->vel_y = 0;
	}

	return FLAG_NOTHING;
}
