#ifndef ENTITY_H
#define ENTITY_H

#include <VGAX.h>
#include <avr/pgmspace.h>

class Entity {
public:
	byte x;
	byte y;
protected:
	byte width;
	byte height;

public:
	Entity(byte x, byte y, byte width, byte height);
	void draw(byte color);
	boolean collide(byte vec_x, byte vec_y, Entity & other);
};

#endif /* ENTITY_H */
