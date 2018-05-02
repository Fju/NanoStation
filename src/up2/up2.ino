#include <VGAX.h>
#include <avr/pgmspace.h>

#include "text.h"
#include "nanostation.h"

#include "platform.h"
#include "character.h"

#define SENSIBILITY 200
#define PLATFORM_AMOUNT 4

Platform platforms[PLATFORM_AMOUNT] = {
	Platform(30, 30, 20, 20),
	Platform(70, 30, 20, 20),
	Platform(80, 0, 40, 20),
	Platform(0, 50, 20, 5)
};

Character character = Character(0, 0);

void draw_platforms() {
	for (byte i = 0; i != PLATFORM_AMOUNT; ++i) {
		platforms[i].draw(COLOR_BLACK);
	}
}

void setup() {
	VGAX::begin();
	VGAX::clear(COLOR_BLUE);
	draw_platforms();
}

void loop() {
	int sx = analogRead(PIN_STICK_X);
	int sy = analogRead(PIN_STICK_Y);

	character.vel.x += sx - 512 >> 7;
	if (sy < 512 - SENSIBILITY) character.vel.y -= 3;

	if (character.vel.y < 6) ++character.vel.y;


	// logging
	// VGAX::fillrect(10, 10, 50, 30, COLOR_BLUE);
	// drawInt(character.x, 10, 10, COLOR_YELLOW);
	// drawInt(character.y, 10, 20, COLOR_YELLOW);

	/* character.update(platforms, PLATFORM_AMOUNT); */

	/* draw_platforms(); */
	character.draw();

	VGAX::delay(33);
}
