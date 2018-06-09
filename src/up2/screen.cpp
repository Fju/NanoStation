#ifndef SCREEN_H
#define SCREEN_H

#include <VGAX.h>
#include "nanostation.h"
#include "text.h"
#include "platform.h"

const char str_next_level[] PROGMEM = "NEXT LEVEL";
const char str_won[] PROGMEM = "CONGRATS YOU WON";
const char str_restart[] PROGMEM = "PRESS BUTTON TO RESTART";
const char str_continue[] PROGMEM = "PRESS BUTTON TO CONTINUE";

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

void level_screen() {
	screen(str_next_level, str_continue);
}

void win_screen() {
	screen(str_won, str_restart);
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
