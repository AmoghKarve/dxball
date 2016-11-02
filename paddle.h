#ifndef __PADDLE_H
#define __PADDLE_H

#include<ncurses.h>
#include "structures.h"
#include "windows.h"

void movepaddle(WINDOW *window_paddle,coordinate *paddle,int direction,int PaddleShift);

#endif
