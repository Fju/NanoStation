// #include <stdlib.h>
#include "platform.h"
#include "maps.h"

byte load_map(byte id, Platform * * platforms_) {
	byte * settings = maps[id];

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
