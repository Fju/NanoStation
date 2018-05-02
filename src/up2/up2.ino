#include <VGAX.h>
#include <avr/pgmspace.h>

#include "text.h"
#include "nanostation.h"

#include "entity.h"
#include "character.h"

#define SENSIBILITY 200
#define PLATFORM_AMOUNT 1

Entity platforms[PLATFORM_AMOUNT] = {
	/*Entity(30, 30, 20, 20),
	Entity(70, 30, 20, 20),
	Entity(80, 0, 40, 20),*/
	Entity(0, 50, 20, 5)
};

Character character = Character();

void draw_platforms(byte color) {
	for (byte i = 0; i != PLATFORM_AMOUNT; ++i) {
		platforms[i].draw(color);
	}
}

void setup() {
	VGAX::begin();
	VGAX::clear(COLOR_BLUE);
	draw_platforms(COLOR_BLACK);
}

void loop() {
	// calculations

	int sx = analogRead(PIN_STICK_X);
	int sy = analogRead(PIN_STICK_Y);

	character.vel.x += sx - 512 >> 7;
	if (sy < 512 - SENSIBILITY) character.vel.y -= 3;

	if (character.vel.y < 6) ++character.vel.y;


	// drawing
	//VGAX::fillrect(10, 10, 50, 30, COLOR_BLUE);
	/*drawInt(character.x, 10, 10, COLOR_YELLOW);
	drawInt(character.y, 10, 20, COLOR_YELLOW);
	drawInt(character.get_max_x(), 25, 10, COLOR_YELLOW);
	drawInt(character.get_max_y(), 25, 20, COLOR_YELLOW);*/

	character.update(platforms, PLATFORM_AMOUNT);

	character.draw();

	VGAX::delay(33);
}
