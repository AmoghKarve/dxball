#include "windows.h"

WINDOW *createwindow(WINDOW *orig,int y,int x,int h,int w){
	WINDOW *localwindow;
	localwindow = derwin(orig,h,w,y,x);
	wrefresh(localwindow);
	wrefresh(orig);
	sleep(0.1);
	return localwindow;
}


void deletewindow(WINDOW *localwindow){

	wborder(localwindow,' ',' ',' ',' ',' ',' ',' ',' ');
	sleep(0.1);
       	wrefresh(localwindow);
	return;
}

