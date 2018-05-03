#include <VGAX.h>
#include <avr/pgmspace.h>

#include "text.h"
#include "nanostation.h"

#include "platform.h"
#include "character.h"

#define PLATFORM_AMOUNT 4
#define BLINK_INTERVAL 20

Platform platforms[PLATFORM_AMOUNT] = {
	Platform(30, 30, 20, 20),
	Platform(70, 30, 20, 20),
	Platform(80, 0, 40, 20),
	Platform(0, 50, 20, 5)
};

Character character = Character(0, 0);

void draw_platforms(byte color) {
	platforms[0].draw(COLOR_BLACK); // the first platform doesn't blink
	for (byte i = 1; i != PLATFORM_AMOUNT; ++i) {
		platforms[i].draw(color);
	}
}

bool platform_color = 0;
byte platform_blink_counter = 0;

void setup() {
	VGAX::begin();
	VGAX::clear(COLOR_BLUE);
	draw_platforms(platform_color);
}


void loop() {
	if (platform_blink_counter == BLINK_INTERVAL) platform_color = !platform_color;
	platform_blink_counter = (platform_blink_counter + 1) % BLINK_INTERVAL + 1;

	// logging
	// VGAX::fillrect(10, 10, 50, 30, COLOR_BLUE);
	// drawInt(character.x, 10, 10, COLOR_YELLOW);
	// drawInt(character.y, 10, 20, COLOR_YELLOW);

	// updates
	character.update();

	draw_platforms(platform_color);
	character.draw();

	VGAX::delay(33);
}
