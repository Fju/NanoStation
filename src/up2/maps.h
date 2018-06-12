#ifndef MAPS_H
#define MAPS_H
#include "platform.h"

// 6 platforms seems to be the limit the ram can handle

const PROGMEM byte tutorial[]  = {
	1, // map size (in number of platforms)
	0, 55, 120, 5, 0, 0,
};

const PROGMEM byte blink[]  = {
	1, // map size (in number of platforms)
	0, 55, 120, 5, 2, 96,
};

const PROGMEM byte obstacle[]  = {
	2, // map size (in number of platforms)
	30, 53, 2,   2, 64, 0,
	0,  55, 120, 5, 2,  112,
};

const PROGMEM byte big_obstacle[]  = {
	2, // map size (in number of platforms)
	30, 50, 5,   5, 16, 0,
	0,  55, 120, 5, 0,  0,
};

const PROGMEM byte fju[]  = { // this one is dedicated to you @Fju :D
	4, // map size (in number of platforms)
	10, 50, 20, 10, 2, 96,
	30, 45, 30, 5,  2, 96,
	65, 43, 20, 10, 2, 96,
	80, 55, 40, 5,  4, 96,
};

const PROGMEM byte origin[]  = {
	4, // map size (in number of platforms)
	10, 50, 22, 10, 4, 48,
	35, 50, 22, 10, 0, 0,
	60, 50, 22, 10, 4, 48,
	82, 55, 40, 5,  0, 0,
};

const PROGMEM byte blinking_origin[]  = {
	4, // map size (in number of platforms)
	10, 50, 22, 10, 4, 32,
	35, 50, 22, 10, 4, 224,
	60, 50, 22, 10, 4, 32,
	82, 55, 40, 5,  0, 0,
};

const PROGMEM byte stairs[]  = {
	6, // map size (in number of platforms)
	5,  45, 5,  5, 0, 0,
	10, 40, 5,  5, 0, 0,
	15, 35, 5,  5, 0, 0,
	20, 30, 5,  5, 0, 0,
	25, 25, 5,  5, 0, 0,
	49, 55, 80, 5, 0, 0,
};

const short maps[] = {
	tutorial,
	blink,
	obstacle,
	big_obstacle,
	fju,
	stairs,
	origin,
	blinking_origin,
};

const byte map_amount = sizeof(maps) / sizeof(short);

byte load_map(byte id, Platform * * platforms_);

#endif /* MAPS_H */
