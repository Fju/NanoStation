#include <VGAX.h>
#include <avr/pgmspace.h>

#include "nanostation.h"

#include "character.h"
#include "screen.h"
#include "text.h"
#include "platform.h"
#include "maps.h"


Character character = Character();
byte time = 0;

Platform * current_map;
byte platform_amount;

// logging
// VGAX::fillrect(10, 10, 50, 30, COLOR_BLUE);
// drawInt(color, 10, 10, COLOR_YELLOW);
// drawInt(platforms[i].should_update(time), 10, 20, COLOR_YELLOW);

void draw_platforms() {
	for (byte i = 0; i != platform_amount; ++i) {
		if (current_map[i].should_update(time)) {
			byte color = current_map[i].get_color(time);
			current_map[i].draw(color);
		}
	}
}

void clear() {
	clear_screen();
	draw_platforms();
	character = Character();
}

void setup() {
	// Serial.begin(9600);
	// while (!Serial);

	// map initialization
	load_map(0);
	current_map = get_map();
	platform_amount = get_amount();

	// screen initialization
	VGAX::begin();
	clear_screen();
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
