#ifndef ENTITY_H
#define ENTITY_H

#include <VGAX.h>
#include "vector.h"

class Entity {
public:
	char x;
	char y;
protected:
	byte width;
	byte height;

public:
	Entity(signed char x_, signed char y_, byte width_, byte height_);
	void draw(byte color);
	boolean collide(Vector vel, Entity & other, Vector & pen_vec);
	inline signed char get_max_x() {
		return this->x + this->width;
	}
	inline signed char get_max_y() {
		return this->y + this->height;
	}
	Vector get_pen_vec();
};

#endif /* ENTITY_H */
