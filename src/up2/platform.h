#ifndef PLATFORM_H
#define PLATFORM_H

#include <VGAX.h>
#include "nanostation.h"
#include "text.h"

// there's a lot of ugly inline stuff but it's f4st3rrrrr!
class Platform {
private:
	byte x;
	byte y;
	byte width;
	byte height;
	byte frequency; // has to be a power of 2
	byte offset; // blink offset

public:
	inline Platform(byte x_, byte y_, byte width_, byte height_, byte frequency_, byte offset_):
	x(x_), y(y_), width(width_), height(height_), frequency(frequency_), offset(offset_) {
	}
	inline Platform(byte settings[]):
	Platform(settings[0], settings[1], settings[2], settings[3], settings[4], settings[5]) {
	}
	inline void draw(byte color) {
		VGAX::fillrect(this->x, this->y, this->width, this->height, color);
	}
	inline byte get_color(byte time) {
		if (frequency == 0) return COLOR_BLACK;

		return ((time + offset)/(256/this->frequency))%2 ? COLOR_BLACK : COLOR_YELLOW;
	}
	inline bool should_update(byte time) {
		if (frequency == 0) return false;

		return (time + offset) % (256/this->frequency) == 0;
	}
};

#endif /* PLATFORM_H */
