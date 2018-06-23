#ifndef PLATFORM_H
#define PLATFORM_H

#include <VGAX.h>
#include "nanostation.h"

// there's a lot of ugly inline stuff but it's f4st3rrrrr!
class Platform {
private:
	byte x;
	byte y;
	byte width;
	byte height;
	byte frequency_offset_field; // merges the frequency and the offset in 1 byte. Whoohoo memory optimisations!

public:
	inline Platform(byte settings[]):
	Platform(settings[0], settings[1], settings[2], settings[3], settings[4], settings[5]) {
	}
	inline void draw(byte color) {
		VGAX::fillrect(this->x, this->y, this->width, this->height, color);
	}
	inline byte get_color(byte time) { // note: it's always COLOR_BLACK when the interval is 1
		return ((time + this->get_offset())/(256/this->get_interval()))%2 ? COLOR_YELLOW : COLOR_BLACK;
	}
	inline bool should_update(byte time) {
		byte interval = this->get_interval();

		if (interval == 1) return false;

		return (time + this->get_offset()) % (256/interval) == 0;
	}
private:
	inline Platform(byte x_, byte y_, byte width_, byte height_, byte frequency_, byte offset_):
	x(x_), y(y_), width(width_), height(height_) {
		// the frequency is from 0 (slow) to 7 (fast)
		// it occupies the first 3 bits

		// the offset is granular up to 8 ticks (it's expected as a multiple of 8, if it's not it will be floored)
		// it occupies the last 5 bits

		this->frequency_offset_field = (frequency_ << 5) + (offset_ / 8);
	}
	inline byte get_interval() {
		// 2^frequency
		// returns the interval during which the color stays the same
		return 1 << (this->frequency_offset_field >> 5);
	}
	inline byte get_offset() {
		// the stored offset has to be a multiple of 8,
		// if not it will be floored to the closet power of 8 (see constructor)

		// byte tmp = this->frequency_offset_field << 3 >> 3; // to crush the frequency
		// return tmp << 3; // or this->offset * 8
		// but it can be simplified to the following since it's already multiplied by 8:
		return this->frequency_offset_field << 3;
	}
};

#endif /* PLATFORM_H */
