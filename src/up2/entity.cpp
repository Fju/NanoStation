#include "entity.h"
#include <VGAX.h>

Entity::Entity(byte x, byte y, byte width, byte height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void Entity::draw(byte color) {
	VGAX::fillrect(this->x, this->y, this->width, this->height, color);
}
boolean Entity::collide(byte vec_x, byte vec_y, Entity & other) {
	byte new_x = this->x + vec_x,
		 new_y = this->y + vec_y;

	return !(
		other.x >= new_x + this->width ||
		other.x + other.width <= new_x ||
		other.y >= new_y + this->height ||
		other.x + other.height <= new_y
	);
	/* return !(
		this->x <= other.x + other.width &&
		this->x + this->width >= other.x &&
		this->y <= other.y + other.height &&
		this->height + this->y >= other.y
	);*/
}
