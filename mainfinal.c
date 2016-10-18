#include<ncurses.h>
#include<pthread.h>
#include<unistd.h>
#include "windows.h"
#include "kbhit.h"
#include "bricks.h"
#include "structures.h"
#include "ball.h"

int main(){
	int ymax,xmax;
	int xstart,xend;
	int height = 2.5;
	int width = 7;
	initscr();
	cbreak;
	noecho();
	curs_set(0);
	start_color();
	//init_pair(5,COLOR_BLACK,COLOR_WHITE);
	//bkgdset(COLOR_PAIR(5));
	//box(stdscr,0,0);
	sleep(1);
	refresh();
	keypad(stdscr,TRUE);
	getmaxyx(stdscr,ymax,xmax);
	brick bricks[5][8];
	drawbricks(stdscr,bricks,ymax/3,xmax/3,5,8,&xstart,&xend);
	refresh();
	//init ball
	int dx,dy,x,y;
	dx = 1;
	dy = -1;
	int tempy,tempx;
	int xpaddle,ypaddle;
	int c;
	x = xmax / 2;
	mvprintw(x,10,"O");
	refresh();
	sleep(2);
	WINDOW* window_paddle;
	window_paddle = createwindow(stdscr,ymax - 1,x - 5,1,16);
	box(window_paddle,0,0);
	wrefresh(window_paddle);
	refresh();
	xpaddle = xmax/2 - 8;
	ypaddle = ymax - 1;
	mvprintw(ymax - 2,xmax/2,"O");
	refresh();
	sleep(1);
	mvprintw(ymax-4,xmax/2," ");
	refresh();
	sleep(1);
	y = ymax - 2;
	while(1){
		checkforcollision(bricks,y,x,dy,dx,xstart,xend);
		mvprintw(y,x,"O");
		refresh();
		usleep(100000);
		mvprintw(y,x," ");
		usleep(100000);
		refresh();
		y = y + dy;
		x = x + dx;
		if(kbhit()){
			c = wgetch(stdscr);
			switch(c){
				case KEY_LEFT:
					deletewindow(window_paddle);
					xpaddle--;
					mvwin(window_paddle,ypaddle,xpaddle);
					box(window_paddle,0,0);
					wrefresh(window_paddle);
					refresh();
					break;
				case KEY_RIGHT:
					deletewindow(window_paddle);
					xpaddle++;
					mvwin(window_paddle,ypaddle,xpaddle);	
					box(window_paddle,0,0);
					wrefresh(window_paddle);
					refresh();
					break;
				default:
					break;
			}
		}	
	}
}
