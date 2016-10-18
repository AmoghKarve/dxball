#ifndef __STRUCTURES_H
#define __STRUCTURES_H
#include<ncurses.h>
#include<stdio.h>
#include<termios.h>
#include<unistd.h>
#include<fcntl.h>

typedef struct brick{
	WINDOW* localwindow;
        int xleft,xright,yup,ydown;
        int alive;
}brick;
#endif
