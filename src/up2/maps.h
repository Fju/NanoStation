#ifndef MAPS_H
#define MAPS_H
#include "platform.h"

const PROGMEM byte map0[]  = {
	1, // map size (in number of platforms)
	0, 55, 120, 5, 2,
};

const PROGMEM byte map1[]  = {
	2, // map size (in number of platforms)
	65, 53, 2, 2, 64,
	0, 55, 120, 5, 2,
};

const PROGMEM byte map2[]  = {
	2, // map size (in number of platforms)
	65, 50, 5, 5, 8,
	0, 55, 120, 5, 2,
};

const PROGMEM byte map3[]  = {
	4, // map size (in number of platforms)
	10, 50, 20, 10, 2,
	30, 45, 30, 5, 2,
	65, 43, 20, 10, 2,
	80, 55, 40, 5, 4,
};

const short maps[] = {
	map0,
	map1,
	map2,
	map3,
};

const byte map_amount = sizeof(maps) / sizeof(short);

byte load_map(byte id, Platform * * platforms_);

#endif /* MAPS_H */
