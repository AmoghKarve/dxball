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

typedef struct coordinate{
	int x,y;
}coordinate; 

typedef struct velocity{
	int x,y;
}velocity;

typedef struct object{
	coordinate r;
	velocity v;
}object;

typedef struct score{
	int value;
	char name[16];
}score;

#define NoRows 5
#define NoColumns 8
#define LEFT -1
#define RIGHT 1


#endif
