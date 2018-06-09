// #include <stdlib.h>
#include "platform.h"
#include "maps.h"

const PROGMEM byte map0[]  = {
	4, // map size (in number of platforms)
	10, 50, 20, 10, 2,
	30, 45, 30, 5, 2,
	65, 43, 20, 10, 2,
	80, 55, 40, 5, 4,
};

const PROGMEM byte map1[]  = {
	3, // map size (in number of platforms)
	10, 50, 20, 10, 2,
	65, 43, 20, 10, 2,
	80, 55, 40, 5, 4,
};

static byte * find_map(byte id) {
	switch (id) {
		case 0:
			return map0;
		case 1:
			return map1;
		default:
			return map0;
	}
}


byte load_map(byte id, Platform * * platforms_) {
	byte * settings = find_map(id);

	byte platform_amount = pgm_read_byte(settings);
	Platform * platforms = malloc(sizeof(Platform) * platform_amount);

	for (byte i = 0; i != platform_amount; ++i) {
		byte tmp_settings[5];
		for (byte j = 0; j != 5; ++j) {
			tmp_settings[j] = pgm_read_byte((i * 5) + j + settings + 1); // + 1 because the first byte is the map size
		}

		platforms[i] = Platform(tmp_settings);
	}

	*platforms_ = platforms;

	return platform_amount;
}
