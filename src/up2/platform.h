#ifndef PLATFORM_H
#define PLATFORM_H

#include "vector.h"
#include "character.h"
#include <VGAX.h>

// there's a lot of ugly inline stuff but it's f4st3rrrrr!

class Platform {
public:
	char x;
	char y;
protected:
	byte width;
	byte height;

public:
	Platform(signed char x_, signed char y_, byte width_, byte height_);
	void draw(byte color);
	inline boolean collide(signed char x, signed char y) {
		// AABB-point collision detection
		return (
			x >= this->x &&
			x <= this->get_max_x() &&
			y >= this->y &&
			y <= this-get_max_y()
		);
	}
	inline signed char get_max_x() {
		return this->x + this->width - 1;
	}
	inline signed char get_max_y() {
		return this->y + this->height - 1;
	}
};

#endif /* PLATFORM_H */
