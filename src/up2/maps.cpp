// #include <stdlib.h>
#include "platform.h"
#include "maps.h"

const PROGMEM byte settings[]  = {
	4, // map size (in number of platforms)
	10, 50, 20, 10, 2,
	30, 45, 30, 5, 2,
	65, 43, 20, 10, 2,
	80, 55, 40, 5, 4,
};


byte load_map(byte id, Platform * * platforms_) {
	byte platform_amount = pgm_read_byte(settings);
	Platform * platforms = malloc(sizeof(Platform) * platform_amount);

	for (byte i = 0; i != platform_amount; ++i) {
		byte tmp_settings[5];
		for (byte j = 0; j != 5; ++j) {
			tmp_settings[j] = pgm_read_byte((i * 5) + j + settings + 1); // + 1 because the first byte is the map size
		}

		platforms[i] = Platform(tmp_settings[0], tmp_settings[1], tmp_settings[2], tmp_settings[3], tmp_settings[4]);
	}

	*platforms_ = platforms;

	return platform_amount;
}
