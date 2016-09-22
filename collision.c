#include<ncurses.h>
#define RED 1
int main(){
	initscr();
	cbreak();
	start_color();
	int xmax,ymax;
	getmaxyx(stdscr,ymax,xmax);
	init_pair(1,COLOR_RED,COLOR_BLACK);
	init_pair(2,COLOR_BLUE,COLOR_BLACK);
	init_pair(3,COLOR_GREEN,COLOR_BLACK);
	short i = 1;
	int height,width;
	height = 2;
	width = 7;
	refresh();
	WINDOW *window1;
	window1 = derwin(stdscr,height,width,(ymax-height)/2,(xmax-width)/2);
	box(window1,0,0);
	wrefresh(window1);
	refresh();
	usleep(500000);
	endwin();
}
