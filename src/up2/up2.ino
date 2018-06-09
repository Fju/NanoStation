#include <VGAX.h>
#include <avr/pgmspace.h>

#include "nanostation.h"

#include "character.h"
#include "screen.h"
#include "text.h"
#include "maps.h"


Character character = Character();
byte time = 0;

Platform * current_map;
byte platform_amount;

// logging
// VGAX::fillrect(10, 10, 50, 30, COLOR_BLUE);
// drawInt(color, 10, 10, COLOR_YELLOW);
// drawInt(platforms[i].should_update(time), 10, 20, COLOR_YELLOW);


void clear() {
	clear_screen();
	force_draw_platforms(current_map, platform_amount, time);
	character = Character();
}

void setup() {
	// Serial.begin(9600);
	// while (!Serial);

	// map initialization
	platform_amount = load_map(0, &current_map);

	// screen initialization
	VGAX::begin();
	clear_screen();
}

void loop() {
	// platform color updates
	draw_platforms(current_map, platform_amount, time);

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
