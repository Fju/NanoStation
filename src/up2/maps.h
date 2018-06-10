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
	0, 55, 120, 5, 2, 0,
};

const PROGMEM byte obstacle[]  = {
	2, // map size (in number of platforms)
	30, 53, 2,   2, 64, 0,
	0,  55, 120, 5, 2,  0,
};

const PROGMEM byte big_obstacle[]  = {
	2, // map size (in number of platforms)
	30, 50, 5,   5, 16, 0,
	0,  55, 120, 5, 0,  0,
};

const PROGMEM byte fju[]  = { // this one is dedicated to you @Fju :D
	4, // map size (in number of platforms)
	10, 50, 20, 10, 2, 0,
	30, 45, 30, 5,  2, 0,
	65, 43, 20, 10, 2, 0,
	80, 55, 40, 5,  4, 0,
};

const PROGMEM byte origin[]  = {
	4, // map size (in number of platforms)
	10, 50, 22, 10, 4, 0,
	35, 50, 22, 10, 0, 0,
	60, 50, 22, 10, 4, 0,
	82, 55, 40, 5,  0, 0,
};

const PROGMEM byte blinking_origin[]  = {
	4, // map size (in number of platforms)
	10, 50, 22, 10, 4, 0,
	35, 50, 22, 10, 4, 64,
	60, 50, 22, 10, 4, 0,
	82, 55, 40, 5,  0, 0,
};

const PROGMEM byte stairs[]  = {
	6, // map size (in number of platforms)
	5,  45, 5,  5, 0, 0,
	10, 40, 5,  5, 0, 0,
	15, 35, 5,  5, 0, 0,
	20, 30, 5,  5, 0, 0,
	25, 25, 5,  5, 0, 0,
	44, 55, 76, 5, 0, 0,
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
