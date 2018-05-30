#include <VGAX.h>
#include "nanostation.h"
#include "text.h"

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
	VGAX::putpixel(107, 54, COLOR_WHITE);
}
