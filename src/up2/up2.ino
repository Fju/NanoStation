#include <VGAX.h>
#include <avr/pgmspace.h>

#include "text.h"
#include "nanostation.h"

#include "platform.h"
#include "character.h"

#define PLATFORM_AMOUNT 4
#define BLINK_INTERVAL 100

#define INIT_POS_X 10
#define INIT_POS_Y 48

Platform platforms[PLATFORM_AMOUNT] = {
	Platform(0, 50, 20, 5),
	Platform(30, 30, 20, 20),
	Platform(70, 30, 20, 20),
	Platform(80, 0, 40, 20),
};

const char str_game_over[] PROGMEM = "GAME OVER";
const char str_instructions[] PROGMEM = "PRESS A BUTTON TO START";
byte width_game_over = getWidth(str_game_over, true);
byte width_instr = getWidth(str_instructions, true);

Character character = Character(INIT_POS_X, INIT_POS_Y);

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

void gameover_screen() {
	VGAX::clear(COLOR_BLUE);
	drawTextPROGMEM(str_game_over, (VGAX_WIDTH - width_game_over) / 2, 20, COLOR_WHITE);
	drawTextPROGMEM(str_instructions, (VGAX_WIDTH - width_instr) / 2, 40, COLOR_WHITE);

	while (digitalRead(PIN_BUTTON_A) == LOW) {
		VGAX::delay(33);
	};
	VGAX::clear(COLOR_BLUE);
	draw_platforms(platform_color);
	character = Character(INIT_POS_X, INIT_POS_Y);
}

void loop() {
	// platform color updates
	if (platform_blink_counter == BLINK_INTERVAL) {
		platform_color = platform_color == COLOR_BLACK ? COLOR_YELLOW : COLOR_BLACK;
		draw_platforms(platform_color);
	}
	platform_blink_counter = (platform_blink_counter + 1) % BLINK_INTERVAL + 1;

	// character pos updates
	bool died = character.update();
	if (died) gameover_screen();

	// paints
	character.draw();

	VGAX::delay(33);
}
