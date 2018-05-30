#include <VGAX.h>
#include <avr/pgmspace.h>

#include "text.h"
#include "nanostation.h"

#include "platform.h"
#include "character.h"
#include "screen.h"

#define BLINK_INTERVAL 100

#define INIT_POS_X 10
#define INIT_POS_Y 49

Platform platforms[] = {
	Platform(0, 50, 20, 5),
	Platform(30, 50, 30, 20),
	Platform(70, 40, 20, 10),
	Platform(80, 55, 40, 5),
};

Character character = Character(INIT_POS_X, INIT_POS_Y);

void draw_platforms(byte color) {
	platforms[0].draw(COLOR_BLACK); // the first platform doesn't blink
	for (byte i = 1; i != sizeof(platforms) / sizeof(Platform); ++i) {
		platforms[i].draw(color);
	}
}

bool platform_color = COLOR_BLACK;
byte platform_blink_counter = BLINK_INTERVAL; // so that it triggers the first paint

void clear() {
	clear_screen();
	draw_platforms(platform_color);
	character = Character(INIT_POS_X, INIT_POS_Y);
}

void setup() {
	VGAX::begin();
	clear_screen();
}

void loop() {
	// platform color updates
	if (platform_blink_counter == BLINK_INTERVAL) {
		platform_color = platform_color == COLOR_BLACK ? COLOR_YELLOW : COLOR_BLACK;
		draw_platforms(platform_color);
	}
	platform_blink_counter = (platform_blink_counter + 1) % BLINK_INTERVAL + 1;

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

	VGAX::delay(33);
}
