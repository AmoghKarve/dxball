#ifndef __WINDOWS_H
#define __WINDOWS_H
#include<ncurses.h>
#include "structures.h"

WINDOW *createwindow(WINDOW *orig,int y,int x,int h,int w);

void deletewindow(WINDOW *localwindow);
#endif
