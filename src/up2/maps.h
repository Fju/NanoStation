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
	0, 55, 120, 5, 1, 224,
};

const PROGMEM byte obstacle[]  = {
	2, // map size (in number of platforms)
	30, 53, 2,   2, 6, 0,
	0,  55, 120, 5, 1, 240,
};

const PROGMEM byte big_obstacle[]  = {
	2, // map size (in number of platforms)
	30, 50, 5,   5, 4, 128,
	0,  55, 120, 5, 0,  0,
};

const PROGMEM byte fju[]  = { // this one is dedicated to you @Fju :D
	4, // map size (in number of platforms)
	10, 50, 20, 10, 1, 224,
	30, 45, 30, 5,  1, 224,
	65, 43, 20, 10, 1, 224,
	80, 55, 40, 5,  2, 160,
};

const PROGMEM byte origin[]  = {
	4, // map size (in number of platforms)
	10, 50, 22, 10, 2, 112,
	35, 50, 22, 10, 0, 0,
	60, 50, 22, 10, 2, 112,
	82, 55, 40, 5,  0, 0,
};

const PROGMEM byte blinking_origin[]  = {
	4, // map size (in number of platforms)
	10, 50, 22, 10, 2, 96,
	35, 50, 22, 10, 2, 32,
	60, 50, 22, 10, 2, 96,
	82, 55, 40, 5,  0, 0,
};

const PROGMEM byte stairs[]  = {
	8, // map size (in number of platforms)
	5,  45, 4,  4, 0, 0,
	10, 40, 4,  4, 0, 0,
	15, 35, 4,  4, 0, 0,
	20, 30, 4,  4, 0, 0,
	25, 25, 4,  4, 0, 0,
	30, 20, 4,  4, 0, 0,
	35, 15, 4,  4, 0, 0,
	62, 55, 58, 5, 0, 0,
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
