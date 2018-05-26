#include <VGAX.h>
#include <avr/pgmspace.h>

#include "text.h"
#include "nanostation.h"

#include "platform.h"
#include "character.h"

#define PLATFORM_AMOUNT 4
#define BLINK_INTERVAL 20

Platform platforms[PLATFORM_AMOUNT] = {
	Platform(0, 50, 20, 5),
	Platform(30, 30, 20, 20),
	Platform(70, 30, 20, 20),
	Platform(80, 0, 40, 20),
};

Character character = Character(10, 48);

void draw_platforms(byte color) {
	platforms[0].draw(COLOR_BLACK); // the first platform doesn't blink
	for (byte i = 1; i != PLATFORM_AMOUNT; ++i) {
		platforms[i].draw(color);
	}
}

bool platform_color = COLOR_BLACK;
byte platform_blink_counter = BLINK_INTERVAL; // so that it triggers the first paint

void setup() {
	VGAX::begin();
	VGAX::clear(COLOR_BLUE);
}


void loop() {
	VGAX::clear(COLOR_BLUE);

	// platform color updates
	if (platform_blink_counter == BLINK_INTERVAL) {
		platform_color = platform_color == COLOR_BLACK ? COLOR_YELLOW : COLOR_BLACK;
	}
	draw_platforms(platform_color); // TODO: only when there is an update
	platform_blink_counter = (platform_blink_counter + 1) % BLINK_INTERVAL + 1;

	// character pos updates
	character.update();

	// paints
	character.draw();

	VGAX::delay(33);
}
