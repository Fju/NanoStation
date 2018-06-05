#include <VGAX.h>
#include <avr/pgmspace.h>

#include "nanostation.h"

#include "platform.h"
#include "character.h"
#include "screen.h"

#define INIT_POS_X 10
#define INIT_POS_Y 49

Platform start_platform = Platform(0,  50, 20, 5,  32); // frequency is whatever, TODO: inherit from a base class
Platform platforms[] = {
	Platform(30, 50, 30, 20, 32),
	Platform(70, 40, 20, 10, 32),
	Platform(80, 55, 40, 5, 64),
	Platform(30, 10, 5,  5, 64),
	Platform(50, 10, 5,  5, 16),
	Platform(60, 10, 5,  5, 32),
	Platform(80, 10, 5,  5, 8),
};

Character character = Character(INIT_POS_X, INIT_POS_Y);
byte time = 0;

// logging
// VGAX::fillrect(10, 10, 50, 30, COLOR_BLUE);
// drawInt(color, 10, 10, COLOR_YELLOW);
// drawInt(platforms[i].should_update(time), 10, 20, COLOR_YELLOW);

void draw_platforms() {
	for (byte i = 0; i != sizeof(platforms) / sizeof(Platform); ++i) {
		if (platforms[i].should_update(time)) {
			byte color = platforms[i].get_color(time);
			platforms[i].draw(color);
		}
	}
}

void clear() {
	clear_screen(&start_platform);
	draw_platforms();
	character = Character(INIT_POS_X, INIT_POS_Y);
}

void setup() {
	VGAX::begin();
	clear_screen(&start_platform);
}

void loop() {
	// platform color updates
	draw_platforms();

	// character pos updates
	byte char_flag = character.update();
	switch(char_flag) {
		case FLAG_DIED:
			gameover_screen();
			clear();
			break;
		case FLAG_WON:
			win_screen();
			clear();
			break;
	}

	// paints
	character.draw();

	time += 1;
	VGAX::delay(33);
}
