#include "character.h"
#include "nanostation.h"
#include <VGAX.h>
#include "text.h"

Character::Character() :
Entity(0, 0, 1, 2), vel(0, 0) {
}

void Character::update(Entity platforms[], byte amount) {

	for (byte i = 0; i != amount; ++i) {
		Vector pen_vec = Vector(0, 0);

		if (this->collide(this->vel, platforms[i], pen_vec)) {
			//this->vel.stop();
			//this->vel.invert();

			VGAX::fillrect(this->x, this->y, this->width, this->height, COLOR_BLACK);
			//this->x -= pen_vec.x;
			//this->y -= pen_vec.y;
			byte magnitude = sqrt(this->vel.x * this->vel.x + this->vel.y * this->vel.y);
			char dotprod = this->vel.x * pen_vec.x + this->vel.y * pen_vec.y;

			if (dotprod > 0) dotprod = 1;
			else if (dotprod < 0) dotprod = -1;

			this->vel.x = dotprod * pen_vec.x * magnitude;
			this->vel.y = dotprod * pen_vec.y * magnitude;

			drawText("BINGO", 10, 15, COLOR_YELLOW);
			return;
		}
	}

	this->prev_x = this->x;
	this->prev_y = this->y;

	this->x += vel.x;
	this->y += vel.y;

	this->vel.x = 0;
}

void Character::draw() {
	VGAX::fillrect(this->prev_x, this->prev_y, this->width, this->height, COLOR_BLUE);
	Entity::draw(COLOR_WHITE);
}
