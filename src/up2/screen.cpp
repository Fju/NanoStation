#ifndef SCREEN_H
#define SCREEN_H

#include <VGAX.h>
#include "nanostation.h"
#include "text.h"
#include "platform.h"

const char str_game_over[] PROGMEM = "GAME OVER";
const char str_won[] PROGMEM = "CONGRATS YOU WON";
const char str_instructions[] PROGMEM = "PRESS A BUTTON TO RESTART";

void screen(char * line1, char * line2) {
	byte width_game_over = getWidth(line1, true);
	byte width_instr = getWidth(line2, true);

	VGAX::clear(COLOR_BLUE);
	drawTextPROGMEM(line1, (VGAX_WIDTH - width_game_over) / 2, 20, COLOR_WHITE);
	drawTextPROGMEM(line2, (VGAX_WIDTH - width_instr) / 2, 40, COLOR_WHITE);

	while (digitalRead(PIN_BUTTON_A) == LOW) {
		VGAX::delay(33);
	};
}

void gameover_screen() {
	screen(str_game_over, str_instructions);
}

void win_screen() {
	screen(str_won, str_instructions);
}

void clear_screen() {
	VGAX::clear(COLOR_BLUE);

	VGAX::fillrect(0, 50, 5, 2, COLOR_BLACK); // start platform
	VGAX::putpixel(107, 54, COLOR_WHITE);
}

void draw_platforms(Platform * platforms, byte platform_amount, byte time) {
	for (byte i = 0; i != platform_amount; ++i) {
		if (platforms[i].should_update(time)) {
			byte color = platforms[i].get_color(time);
			platforms[i].draw(color);
		}
	}
}
void force_draw_platforms(Platform * platforms, byte platform_amount, byte time) {
	for (byte i = 0; i != platform_amount; ++i) {
		byte color = platforms[i].get_color(time);
		platforms[i].draw(color);
	}
}

#endif /* SCREEN_H */
