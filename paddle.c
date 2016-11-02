#include<ncurses.h>
#include "paddle.h"
#include "structures.h"
void movepaddle(WINDOW *window_paddle,coordinate *paddle,int direction,int PaddleShift){
	start_color();
	init_pair(10,COLOR_WHITE,COLOR_WHITE);
	init_pair(7,COLOR_WHITE,COLOR_RED);
	deletewindow(window_paddle);
        wbkgd(window_paddle,COLOR_PAIR(10));
        wrefresh(window_paddle);
        refresh();
	if(direction == LEFT)
        	paddle->x-=PaddleShift;
	else
		paddle->x+=PaddleShift;
        mvwin(window_paddle,paddle->y,paddle->x);
        wbkgd(window_paddle,COLOR_PAIR(7));
        wrefresh(window_paddle);

}
