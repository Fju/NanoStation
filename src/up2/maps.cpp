// #include <stdlib.h>
#include "platform.h"
#include "maps.h"

#define SERIALIZED_PLATFORM_SIZE 6

byte load_map(byte id, Platform * * platforms_) {
	byte * settings = maps[id];

	byte platform_amount = pgm_read_byte(settings);
	Platform * platforms = malloc(sizeof(Platform) * platform_amount);

	for (byte i = 0; i != platform_amount; ++i) {
		byte tmp_settings[SERIALIZED_PLATFORM_SIZE];
		for (byte j = 0; j != SERIALIZED_PLATFORM_SIZE; ++j) {
			tmp_settings[j] = pgm_read_byte((i * SERIALIZED_PLATFORM_SIZE) + j + settings + 1); // + 1 because the first byte is the map size
		}

		platforms[i] = Platform(tmp_settings);
	}

	*platforms_ = platforms;

	return platform_amount;
}
