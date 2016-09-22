#include<ncurses.h>
int main(){
	int xmax,ymax,tempx,tempy;
	float dx,dy,x,y;
	initscr();
	cbreak();
	curs_set(0);
	start_color();
	init_pair(1,COLOR_RED,COLOR_BLACK);
	getmaxyx(stdscr,ymax,xmax);
	x = 4*xmax/5;
	//y = ymax/2;
	dx = 1;
	dy = 0.9*dx;
	while(1){
		tempx = x;
		tempy = y;
		attron(COLOR_PAIR(1));
		mvprintw(y,x,"O");
		refresh();
		attroff(COLOR_PAIR(1));
		usleep(100000);
		mvprintw(tempy,tempx," ");
		refresh();
		usleep(20000);
		y = y + dy;
		x = x + dx;
		if(y >= ymax)
			break;
		if(x == xmax)
			dx = -dx;
	}
	endwin();
}
