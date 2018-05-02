#include "platform.h"
#include "nanostation.h"
#include "text.h"
#include <VGAX.h>

Platform::Platform(signed char x_, signed char y_, byte width_, byte height_) :
x(x_), y(y_), width(width_), height(height_) {
}

void Platform::draw(byte color) {
	VGAX::fillrect(this->x, this->y, this->width, this->height, color);
}
