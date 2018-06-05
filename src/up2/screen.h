#ifndef SCREEN_H
#define SCREEN_H

#include <VGAX.h>
#include "nanostation.h"
#include "platform.h"


void screen(char * line1, char * line2);

void gameover_screen();

void win_screen();

void clear_screen(Platform * platform);

#endif /* SCREEN_H */
