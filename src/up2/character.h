#ifndef CHARACTER_H
#define CHARACTER_H

#include <VGAX.h>
#include "entity.h"
#include "vector.h"

class Character : public Entity {
public:
	byte prev_x;
	byte prev_y;

	Vector vel;

public:
	Character();
	void update(Entity platforms[], byte amount);
	void draw();
};

#endif /* CHARACTER_H */
