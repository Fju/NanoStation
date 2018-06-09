#ifndef PLATFORM_H
#define PLATFORM_H

#include "vector.h"
#include "character.h"
#include <VGAX.h>
#include "nanostation.h"
#include "text.h"

// there's a lot of ugly inline stuff but it's f4st3rrrrr!
class Platform {
public:
	byte x;
	byte y;
protected:
	byte width;
	byte height;
	byte frequency; // has to be a power of 2

public:
	inline Platform(signed char x_, signed char y_, byte width_, byte height_, byte frequency_):
	x(x_), y(y_), width(width_), height(height_), frequency(frequency_) {
	}
	inline void draw(byte color) {
		VGAX::fillrect(this->x, this->y, this->width, this->height, color);
	}
	inline byte get_color(byte time) {
		return (time/(256/this->frequency))%2 ? COLOR_BLACK : COLOR_YELLOW;
	}
	inline bool should_update(byte time) {
		return time % (256/this->frequency) == 0;
	}
};

#endif /* PLATFORM_H */
