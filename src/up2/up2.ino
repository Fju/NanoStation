#include <VGAX.h>
#include <avr/pgmspace.h>

#include "nanostation.h"

#include "character.h"
#include "screen.h"
#include "text.h"
#include "maps.h"


Character character = Character();
byte time = 0;

byte map_id = 0;
Platform * current_map;
byte platform_amount;

// logging
// VGAX::fillrect(10, 10, 50, 30, COLOR_BLUE);
// drawInt(platforms[i].should_update(time), 10, 20, COLOR_YELLOW);


void reset() {
	// screen init
	clear_screen();
	force_draw_platforms(current_map, platform_amount, time);
	drawInt(map_id, 1, 1, COLOR_BLACK);

	character = Character();
}

void setup() {
	// Serial.begin(9600);
	// while (!Serial);

	VGAX::begin();

	// map initialization
	platform_amount = load_map(map_id, &current_map);

	reset();
}

void loop() {
	// platform color updates
	draw_platforms(current_map, platform_amount, time);

	// character pos updates
	byte char_flag = character.update();
	switch(char_flag) {
		case FLAG_DIED:
			gameover_screen();
			reset();
			break;
		case FLAG_WON:
			if (map_id >= 1) { // finished the game
				win_screen();

				map_id = 0;
			} else {
				level_screen();

				++map_id;
			}

			free(current_map);
			platform_amount = load_map(map_id, &current_map);

			reset();
			break;
	}

	// paints
	character.draw();

	time += 1;
	VGAX::delay(33);
}
