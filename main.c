#include<ncurses.h>
#include<stdio.h>
#include<termios.h>
#include<unistd.h>
#include<fcntl.h>
WINDOW* create_window(WINDOW *orig,int height,int width,int y,int x){
	WINDOW *local_window;
	local_window = subwin(orig,height,width,y,x);
//	box(local_window,0,0);
	wprintw(local_window,"test");
	wrefresh(local_window);
	return local_window;
}
void delete_window(WINDOW *local_window){
	wborder(local_window, ' ', ' ', ' ',' ',' ',' ',' ',' ');
//	wrefresh(local_window);
//	delwin(local_window);
	clear();	
	wrefresh(local_window);
	return;
}
int main(){
	int height = 2.5,width = 6.5;
	int starty,startx,ch;
	initscr();
	cbreak;
	curs_set(0);
	getmaxyx(stdscr,starty,startx);
	box(stdscr,0,0);
	int h,w;
	h = starty/2;
	w = startx/2;
	WINDOW *window1;
	WINDOW *window2;
	WINDOW *window_paddle;
	start_color();			/* Start color 			*/
	init_pair(1, COLOR_RED, COLOR_BLACK);
	window1 = derwin(stdscr,height,width,h,w);
	wattron(window1,COLOR_PAIR(1));
	box(window1,0,0);
	wrefresh(window1);
	wattroff(window1,COLOR_PAIR(1));
//	usleep(3000000);
	refresh();
	//h = h + height;
	w = w + width;
	window2 = derwin(stdscr,height,width,h,w);
	box(window2,0,0);
	wrefresh(window2);
	refresh();
	window_paddle = derwin(stdscr,1,10,starty - 1,startx/2);
	box(window_paddle,0,0);
	wrefresh(window_paddle);
	refresh();
	int y = starty-3;;
	int dx ;
	int dy;
	int x;
	x = startx/2;
	dx = -1;
	dy = -dx;
	int alive = 1;
	int tempx,tempy;
	while(1){
		if( y <= (starty+height)/2 && alive == 1 ){
			wborder(window1, ' ', ' ', ' ',' ',' ',' ',' ',' ');
			wrefresh(window1);
			//wclear(window1);
			//delwin(window1);
			//printw("Brick Gone");
			refresh();
			//usleep(100000);
			dx = 1;
			alive = 0;
			//dy = -dy;
		//	break;
			/*wborder(window_paddle, ' ', ' ', ' ',' ',' ',' ',' ',' ');
			wrefresh(window_paddle);
			refresh();
			mvwin(window_paddle,starty-1,startx/2 + 10);
			box(window_paddle,0,0);
			wrefresh(window_paddle);*/
			refresh();
		}
		if(y == (starty-3)){
			//mvaddch(y - 5,startx + 5,'A');
			//refresh();
			dx = -1;
			//break;
		}
		tempx = x;
		tempy = y;
		attron(COLOR_PAIR(1));
		mvprintw(y,x,"O");
		attroff(COLOR_PAIR(1));
		refresh();
		usleep(100000);
		move(tempy,tempx);
		printw(" ");
		y = y + dx;
		//x = x + 1;
		if(khbit()){
			ch = getch();
			if(ch == KEY_LEFT){
			wborder(window_paddle, ' ', ' ', ' ',' ',' ',' ',' ',' ');
			wrefresh(window_paddle);
			refresh();
			mvwin(window_paddle,starty-1,startx/2 + 10);
			box(window_paddle,0,0);
			wrefresh(window_paddle);
			refresh();
			endwin();
		}
		}
		refresh();
	}
	//mvaddch(y - 5,startx + 5,'A');
	refresh();
	//getchar();
	//usleep(3000000);
	endwin();
}
