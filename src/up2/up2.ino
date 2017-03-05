#include <VGAX.h>
#include <avr/pgmspace.h>

#include "text.h"
#include "nanostation.h"

#include "entity.h"
#include "character.h"
#include "platform.h"

#define SENSIBILITY 200
#define PLATFORM_AMOUNT 3

Entity platforms[PLATFORM_AMOUNT] = {
	Entity(30, 30, 20, 20),
	Entity(70, 30, 20, 20),
	Entity(80, 0, 40, 20)
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

	if (sx > 512 - SENSIBILITY) character.move_right();
	if (sx < 512 + SENSIBILITY) character.move_left();
	if (sy < 512 - SENSIBILITY) character.jump();



	// drawing
	VGAX::fillrect(10, 10, 50, 20, COLOR_BLUE);
	drawInt(character.x, 10, 10, COLOR_YELLOW);
	drawInt(character.y, 10, 20, COLOR_YELLOW);
	drawInt(character.vel_x, 20, 10, COLOR_YELLOW);
	drawInt(character.vel_y, 20, 20, COLOR_YELLOW);

	character.update(platforms, PLATFORM_AMOUNT);

	character.draw();

	VGAX::delay(33);
}
