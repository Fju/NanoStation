#include <VGAX.h>
#include <avr/pgmspace.h>
#include "text.h"

byte getWidth(const char* text, boolean progmem) {
	char *pstr = (char*)text;
	char c;

	byte width = 0;
	if (progmem){
	 while (c = pgm_read_byte(pstr++)) width += charWidth(c);
	} else {
		while (c = *pstr++) width += charWidth(c);
	}

	return width;
}

byte charWidth(char c) {
	if (c == 32) return 3;
	else {
		if (c >= 48 && c < 65) c -= 48;
		if (c >= 65 && c < 97) c -= 55;
		byte a = pgm_read_byte((byte*)fnt_data + (c + 1) * FNT_BYTE_LENGTH - 1);
		return 1 + (a & 7);
	}
}


byte drawCharacter(char c, byte x, byte y, byte colour) {
	if (c == 32) return 3;

	if (c >= 48 && c < 65) c -= 48; //char code 48 to index 0 in fnt_data
	if (c >= 65 && c < 97) c -= 55; //char code 65 to index 10 in fnt_data

	if (c >= 0 && c < FNT_SYMBOLS_COUNT) {
		unsigned long glyph = 0;
		byte bytelength = FNT_BYTE_LENGTH; //32 bit
		while (bytelength--) glyph |= (unsigned long)pgm_read_byte((byte*)fnt_data + c * FNT_BYTE_LENGTH + bytelength) << (8 * (FNT_BYTE_LENGTH - bytelength - 1));

		byte cwidth = glyph & 0b111; //byte is unsigned

		glyph >>= 7;

		byte gheight = FNT_HEIGHT, gwidth;
		while (gheight--) {
			gwidth = cwidth;
			while (gwidth--) {
				if (glyph >> (cwidth * gheight + gwidth) & 1) VGAX::putpixel(x + cwidth - gwidth - 1, y + FNT_HEIGHT - gheight - 1, colour);
			}
		}

		return cwidth + 1;
	}
	return 0;
}

void drawTextPROGMEM(const char* text, byte x, byte y, byte colour) {
	char *pstr = (char*)text;
	byte dx = x;
	char c;
	while (c = pgm_read_byte(pstr++)) dx += drawCharacter(c, dx, y, colour);
}

void drawText(const char* text, byte x, byte y, byte colour) {
	char *pstr = (char*)text;
	byte dx = x;
	char c;
	while (c = *pstr++) dx += drawCharacter(c, dx, y, colour);
}
