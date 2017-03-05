#ifndef CHARACTER_H
#define CHARACTER_H

#include <VGAX.h>
#include <avr/pgmspace.h>
#include "entity.h"

class Character : public Entity {
public:
	byte prev_x;
	byte prev_y;

	byte vel_x;
	byte vel_y;

	inline void stop() {
		vel_x = 0;
		vel_y = 0;
	}

public:
	Character();
	inline void move_left() {
		--this->vel_x;
	};
	inline void move_right() {
		++this->vel_x;
	};
	inline void jump() {
		this->vel_y -= 2;
	};
	void update(Entity platforms[], byte amount);
	void draw();
};

#endif /* CHARACTER_H */
