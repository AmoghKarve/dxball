#include<ncurses.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include "windows.h"
#include "kbhit.h"
#include "bricks.h"
#include "structures.h"
#include "ball.h"
#include "menu.h"


void endgame(WINDOW *orig,int score){
	WINDOW *endgame;
	endgame = newwin(0,0,0,0);
	FILE *fp;
	fp = fopen("scores.txt","a");
	int ymax,xmax;
	char name[16];
	getmaxyx(endgame,ymax,xmax);
	mvwprintw(endgame,ymax/2,xmax/2 - 4,"GAME OVER");
	wrefresh(endgame);
	sleep(1);
	mvwprintw(endgame,ymax,xmax - 4,"         ");
	wrefresh(endgame);
	wmove(endgame,ymax/2,xmax/2 - 4);
	waddstr(endgame,"Enter your name:");
	wrefresh(endgame);
	wgetstr(endgame,name);
	fprintf(fp,"%s %d\n",name,score);
	fclose(fp);
	return;
}

void highscore(){
	WINDOW *highscores;
	highscores = newwin(0,0,0,0);
	int ymax,xmax;
	getmaxyx(highscores,ymax,xmax);
	box(highscores,0,0);
	wrefresh(highscores);
	FILE *fp,*ft;
	fp = fopen("scores.txt","r");
	if(fp == NULL){
		mvwprintw(highscores,ymax/2,xmax/2 - 8,"You are first to play!!!");
		wrefresh(highscores);
		sleep(2);
		wclear(highscores);
		wrefresh(highscores);
		delwin(highscores);
		return;
	}
	score s,temp;
	strcpy(temp.name,"anonymous");
	temp.value = 0;
	while(fscanf(fp,"%s %d",s.name,&s.value) != -1){
		if(s.value > temp.value){
			temp.value = s.value;
			strcpy(temp.name,s.name);
		}
	}
	mvwprintw(highscores,ymax/2,xmax/2 - 8,"%s : %d",temp.name,temp.value);
	wrefresh(highscores);
	fprintf(ft,"%s:%d",temp.name,temp.value);
	sleep(2);
	wclear(highscores);
	wrefresh(highscores);
	fclose(fp);
	return;
}


int main(){
	int ymax,xmax;
	int xstart,xend;
	int tempx,tempy;
	int height = 2.5;
	int width = 7;
	int crash = 0;
	int score = 0;
	int playgame = 0;
	int level;
	int DELAY_NORMAL,DELAY_BULLET;
	int delay_normal,delay_bullet;
	int BULLET,bullet;
	delay_n = 30000;
	initscr();
	cbreak;
	noecho();
	curs_set(0);
	start_color();
	init_pair(10,COLOR_WHITE,COLOR_WHITE);
	init_pair(12,COLOR_BLACK,COLOR_BLACK);
	init_pair(7,COLOR_WHITE,COLOR_RED);
	init_pair(8,COLOR_WHITE,COLOR_RED);
	init_pair(11,COLOR_BLACK,COLOR_WHITE);
	wbkgd(stdscr,COLOR_PAIR(10));
	wrefresh(stdscr);
	refresh();
	keypad(stdscr,TRUE);
	getmaxyx(stdscr,ymax,xmax);
	int i,a;
	while(1){	
		if(playgame)
			break;
		a = menu(stdscr);
		switch(a){
			case 0:
				playgame = 1;
				level = levels(stdscr);
				break;
			case 1:
				clear();
				refresh();
				bkgd(COLOR_PAIR(12));
				refresh();
				highscore();
				break;
			case 2:
				break;
			case 3:
				clear();
				refresh();
				endwin();
				exit(0);
				break;
		}
	}
	switch(level){
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
	}
	clear();
	bkgd(COLOR_PAIR(10));
	refresh();
	brick **bricks;
	bricks = (brick **)malloc(5 * sizeof(brick*));
	for(i = 0;i < 5;i++)
		bricks[i] = (brick*)malloc(8 * sizeof(brick));
	drawbricks(stdscr,bricks,ymax/3,xmax/3,5,8,&xstart,&xend);
	refresh();
	pthread_t tid;
	int dx,x,xf;
	float y,dy,yf;
	dx = 1;
	dy = -1;
	int xpaddle,ypaddle;
	int c;
	int feature_alive,feature;
	int bullet = 0;
	int dummy = 0;
	feature = 0;
	feature_alive = 0;
	x = xmax / 2;
	mvprintw(x,10,"O");
	refresh();
	sleep(2);
	WINDOW* window_paddle;
	window_paddle = createwindow(stdscr,ymax - 1,x - 5,1,16);
	wbkgd(window_paddle,COLOR_PAIR(7));
	wrefresh(window_paddle);
	refresh();
	xpaddle = xmax/2 - 8;
	ypaddle = ymax - 1;
	sleep(1);
	y = ymax - 2;
	srand(time(NULL));
	while(1){
		c = wgetch(stdscr);
		if(c == ' ')
		break;
		switch(c){
			case KEY_LEFT:
				if(xpaddle >= 0){
					mvprintw(y,x," ");
					refresh();
					deletewindow(window_paddle);
					wbkgd(window_paddle,COLOR_PAIR(10));
					wrefresh(window_paddle);
					refresh();
					xpaddle-=4;
					x -= 4;
					mvwin(window_paddle,ypaddle,xpaddle);
					wbkgd(window_paddle,COLOR_PAIR(7));
					wrefresh(window_paddle);
					mvprintw(y,x,"O");
					refresh();
				}
				break;
			case KEY_RIGHT:
				if(xpaddle <= xmax - 4){
					mvprintw(y,x," ");
					refresh();
					deletewindow(window_paddle);
					wbkgd(window_paddle,COLOR_PAIR(10));
					wrefresh(window_paddle);
					refresh();
					xpaddle+=4;
					x += 4;
					mvwin(window_paddle,ypaddle,xpaddle);	
					wbkgd(window_paddle,COLOR_PAIR(7));
					wrefresh(window_paddle);
					mvprintw(y,x,"O");
					refresh();
				}
				break;
			default:
				break;
		}
	}
		while(1){
			if(bullet == 1){
				crash = checkforcollision(bricks,yf,xf,&dy,&dx,xstart,xend,5,8,&bullet);
				if(crash == 1){
					attron(COLOR_PAIR(11));
					score = score + 25;
					mvprintw(2,xmax/2 - 4,"Score: %d",score);
					attroff(COLOR_PAIR(11));
					bullet = 0;
				}
				else if(crash == -1){
					clear();
					echo();
					bkgd(COLOR_PAIR(12));
					feature = 1;
					refresh();
					endgame(stdscr,score);
					clear();
					endwin();
					exit(0);
				}
			}
			if(rand()%50 == 0 && feature_alive == 0 && feature == 0){
				xf = rand()%xmax;
				yf = bricks[4][0].ydown;
				feature_alive = 1;
			}
			if(feature_alive){
				if(yf == ypaddle - 1){
					if(xf >= xpaddle && xf <= xpaddle + 16)
						feature = 1;
					feature_alive = 0;
				}
				attron(COLOR_PAIR(8));
				mvprintw(yf,xf," ");
				attroff(COLOR_PAIR(8));
				refresh();
				usleep(BULLET);
				mvprintw(yf,xf," ");
				usleep(bullet);
				refresh();
				yf++;
			}
			if(bullet == 1){
				attron(COLOR_PAIR(11));
				mvprintw(yf - 1,xf,"^");
				attroff(COLOR_PAIR(11));
				refresh();
				usleep(BULLET);
				mvprintw(yf - 1,xf," ");
				refresh();
				usleep(bullet);

				yf--;
				if(yf == 0)
					bullet = 0;
			}
			attron(COLOR_PAIR(11));
			mvprintw(y,x,"O");
			attroff(COLOR_PAIR(11));
			refresh();
			if(feature_alive == 1 || bullet == 1)
				usleep(DELAY_BULLET);
			else
				usleep(DELAY_NORMAL);
			mvprintw(y,x," ");
			if(feature_alive == 1 || bullet == 1)
				usleep(delay_bullet);
			else
				usleep(delay_normal);
			refresh();
			tempy = y;
			tempx = x;	
			crash = checkforcollision(bricks,tempy,tempx,&dy,&dx,xstart,xend,5,8,&dummy);
			if(crash == 1){
				attron(COLOR_PAIR(11));
				score = score + 25;
				mvprintw(2,xmax/2 - 4,"Score: %d",score);
				attroff(COLOR_PAIR(11));
			}
			else if(crash == -1){
				clear();
				echo();
				bkgd(COLOR_PAIR(12));
				feature = 1;
				refresh();
				endgame(stdscr,score);
				clear();
				endwin();
				exit(0);
			}

			y = y + dy;
			x = x + dx;
			if(y <= 0)
				dy = -dy;
			if(x <= 0 || x >= xmax)
				dx = -dx;
			if(y == ypaddle - 1){
				if(x >= xpaddle && x <= xpaddle + 16)
					dy = -dy;
				else{
					clear();
					echo();
					bkgd(COLOR_PAIR(12));
					feature = 1;
					refresh();
					endgame(stdscr,score);
					clear();
					endwin();
					exit(0);
				}
			}
			refresh();
			if(kbhit()){
				c = wgetch(stdscr);
				switch(c){
					case KEY_LEFT:
						if(xpaddle >= 0){
							deletewindow(window_paddle);
							wbkgd(window_paddle,COLOR_PAIR(10));
							wrefresh(window_paddle);
							refresh();
							xpaddle-=4;
							mvwin(window_paddle,ypaddle,xpaddle);
							wbkgd(window_paddle,COLOR_PAIR(7));
							wrefresh(window_paddle);
							refresh();
						}
						break;
					case KEY_RIGHT:
						if(xpaddle <= xmax - 4){
							deletewindow(window_paddle);
							wbkgd(window_paddle,COLOR_PAIR(10));
							wrefresh(window_paddle);
							refresh();
							xpaddle+=4;
							mvwin(window_paddle,ypaddle,xpaddle);	
							wbkgd(window_paddle,COLOR_PAIR(7));
							wrefresh(window_paddle);
							refresh();
						}
						break;
					case KEY_UP:
						if(feature == 0 || bullet == 1)
							break;
						else{
							bullet = 1;
							xf = xpaddle + 8;
							yf = ypaddle - 1;
							break;
						}
					default:
						break;
				}
			}
		}
	
}
