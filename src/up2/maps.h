#ifndef MAPS_H
#define MAPS_H
#include "platform.h"

const PROGMEM byte tutorial[]  = {
	1, // map size (in number of platforms)
	0, 55, 120, 5, 0,
};

const PROGMEM byte blink[]  = {
	1, // map size (in number of platforms)
	0, 55, 120, 5, 2,
};

const PROGMEM byte obstacle[]  = {
	2, // map size (in number of platforms)
	65, 53, 2, 2, 64,
	0, 55, 120, 5, 2,
};

const PROGMEM byte big_obstacle[]  = {
	2, // map size (in number of platforms)
	30, 50, 5, 5, 16,
	0, 55, 120, 5, 0,
};

const PROGMEM byte fju[]  = { // this one is dedicated to you @Fju :D
	4, // map size (in number of platforms)
	10, 50, 20, 10, 2,
	30, 45, 30, 5, 2,
	65, 43, 20, 10, 2,
	80, 55, 40, 5, 4,
};

const short maps[] = {
	tutorial,
	blink,
	obstacle,
	big_obstacle,
	fju,
};

const byte map_amount = sizeof(maps) / sizeof(short);

byte load_map(byte id, Platform * * platforms_);

#endif /* MAPS_H */
