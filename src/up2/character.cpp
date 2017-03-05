#include "character.h"
#include "nanostation.h"
#include <VGAX.h>
#include "text.h"

Character::Character() :
Entity(0, 0, 1, 2) {
}

void Character::update(Entity platforms[], byte amount) {
	for (byte i = 0; i != amount; ++i) {
		if (this->collide(vel_x, vel_y + 1, platforms[i])) {
			this->stop();
			drawText("BINGO", 10, 15, COLOR_YELLOW);
			return;
		}
	}

	this->prev_x = this->x;
	this->prev_y = this->y;

	this->x += vel_x;
	this->y += vel_y + 1;

	this->stop();
}

void Character::draw() {
	VGAX::fillrect(this->prev_x, this->prev_y, this->width, this->height, COLOR_BLUE);
	Entity::draw(COLOR_WHITE);
}
