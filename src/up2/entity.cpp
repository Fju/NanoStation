#include "entity.h"
#include <VGAX.h>
#include "text.h"
#include "nanostation.h"

Entity::Entity(signed char x_, signed char y_, byte width_, byte height_) :
x(x_), y(y_), width(width_), height(height_) {
}

void Entity::draw(byte color) {
	VGAX::fillrect(this->x, this->y, this->width, this->height, color);
}
boolean Entity::collide(Vector vel, Entity & other, Vector & pen_vec) {
	/*byte new_x = this->x + vel.x,
		 new_y = this->y + vel.y;

	return !(
		other.x >= new_x + this->width ||
		other.x + other.width <= new_x ||
		other.y >= new_y + this->height ||
		other.y + other.height <= new_y
	);*/
	Entity md = Entity(
		this->x - other.get_max_x(),
		this->y - other.get_max_y(),
		this->width + other.width,
		this->height + other.height
	);

	pen_vec = md.get_pen_vec();

	VGAX::fillrect(10, 10, 50, 30, COLOR_BLUE);
	drawInt(pen_vec.x, 10, 10, COLOR_YELLOW);
	drawInt(pen_vec.y, 10, 20, COLOR_YELLOW);
	/*drawInt(md.get_max_x(), 25, 10, COLOR_YELLOW);
	drawInt(md.get_max_y(), 25, 20, COLOR_YELLOW);*/

	return (
		md.x <= 0 &&
		md.get_max_x() >= 0 &&
		md.y <= 0 &&
		md.get_max_y() >= 0
	);
}
Vector Entity::get_pen_vec() {

	byte min_dist = abs(this->x);
	Vector pen_vec = Vector(this->x, 0);

	byte test = abs(this->get_max_x());
	if (test > min_dist) {
		min_dist = test;
		pen_vec = Vector(this->get_max_x(), 0);
	}

	test = abs(this->get_max_y());
	if (test < min_dist) {
		min_dist = test;
		pen_vec = Vector(0, this->get_max_y());
	}

	test = abs(this->y);
	if (test < min_dist) {
		min_dist = test;
		pen_vec = Vector(0, this->y);
	}

	return pen_vec;
}
