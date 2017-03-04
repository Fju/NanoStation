#include <VGAX.h>
#include <avr/pgmspace.h>
#include <stdlib.h>

#include "text.h"

#define COLOR_WHITE   3
#define COLOR_BLUE    2
#define COLOR_YELLOW  1
#define COLOR_BLACK   0

void setup() {
	randomSeed(analogRead(A0)); //generate random seed
	VGAX::begin();
	VGAX::clear(COLOR_BLUE);
}

void loop() {
	byte x = 0,
		 y = 0;

	char buf[12] = "99999999999";
	itoa(65535, buf, 10);

	drawText(buf, 10, 10, COLOR_BLACK);
}
