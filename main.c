/*****************************************************************************************
*Copyright (C) Amogh Karve amogh.karve@gmail.com
*This program is a free software; you can redistribute it and/or modify it
*under the terms of the GNU Lesser General Public License as published by
*the Free Software Foundation; either version 2.1 of the License, or
*(at your option) any later version.
*
*This program is distributed in the hope taht it will be useful,
*but WITHOUT ANY WRRANTY; without even implied warranty of
*MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*GNU Lesser Public License for more details.
*You should have received a copy of the GNU Lesser General Public License
*along with this program; if not write to the Free Software Foundation,
*INC., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
********************************************************************************************/


#include<ncurses.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>
#include "windows.h"
#include "kbhit.h"
#include "bricks.h"
#include "structures.h"
#include "ball.h"
#include "menu.h"
#include "paddle.h"

#define NoRows 5
#define NoColumns 8
#define LEFT -1
#define RIGHT 1
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
	FILE *fp;
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
	sleep(2);
	wclear(highscores);
	wrefresh(highscores);
	fclose(fp);
	return;
}

void display(WINDOW *orig,object temp,int color,char a[2]){
	start_color();
	init_pair(8,COLOR_WHITE,COLOR_RED);
	init_pair(11,COLOR_BLACK,COLOR_WHITE);
	wattron(orig,COLOR_PAIR(color));
	mvwprintw(orig,temp.r.y,temp.r.x,"%s",a);
	wattroff(orig,COLOR_PAIR(color));
	wrefresh(orig);
	return;
}

void aboutgame(WINDOW *orig){
	WINDOW *aboutgame;
	int xmax,ymax;
	getmaxyx(orig,ymax,xmax);
	aboutgame = newwin(28,52,ymax/5,xmax/3);
	wrefresh(aboutgame);	
	FILE *fp;
	start_color();
	fp = fopen("aboutgame.txt","r");
	char ch[2];
	int i = 0;
	int j;
	getmaxyx(aboutgame,ymax,xmax);
	mvwprintw(aboutgame,1,xmax/2 - 5,"ABOUT GAME\n\n\n");
	while(fscanf(fp,"%c",&ch[0]) != -1){
		ch[1] = '\0';
		wprintw(aboutgame,"%s",ch);
		wrefresh(aboutgame);
	}
	fclose(fp);
	ch[0] = wgetch(aboutgame);
	wclear(aboutgame);
	wclear(aboutgame);
	return;
}


int main(){
	int ymax,xmax;
	int xstart,xend;
	int crash = 0;
	int score = 0;
	int playgame = 0;
	int level;
	int DELAY_NORMAL,DELAY_BULLET;
	int delay_normal,delay_bullet;
	int BULLET,bullet;
	delay_normal = 30000;
	int PaddleWidth;
	PaddleWidth = 16;
	int PaddleShift;
	int frequency;
	initscr();
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
	int i,menu_select;
	while(1){	
		bkgd(COLOR_PAIR(10));
		refresh();
		if(playgame)
			break;
		menu_select = menu(stdscr);
		switch(menu_select){
			case 0:               //PLAY GAME
				playgame = 1;
				level = levels(stdscr);
				break;
			case 1:               //HIGHSCORES
				clear();
				refresh();
				bkgd(COLOR_PAIR(12));
				refresh();
				highscore();
				break;
			case 2:               //ABOUT GAME
				clear();
				refresh();
				bkgd(COLOR_PAIR(12));
				aboutgame(stdscr);
				break;
			case 3:               //EXIT
				clear();
				refresh();
				endwin();
				exit(0);
				break;
		}
	}
	switch(level){
		case 1:
			DELAY_NORMAL = 40000;
			delay_normal = 40000;
			DELAY_BULLET = 30000;
			delay_bullet = 10000;
			BULLET = 30000;
			bullet = 10000;
			PaddleShift = 4;
			break;
		case 2:
			DELAY_NORMAL = 30000;
			delay_normal = 30000;
			DELAY_BULLET = 15000;
			delay_bullet = 10000;
			BULLET = 25000;
			bullet = 10000;
			PaddleShift = 6;
			break;
		case 3:
			DELAY_NORMAL = 25000;
			delay_normal = 25000;
			DELAY_BULLET = 10000;
			delay_bullet = 10000;
			BULLET = 20000;
			bullet = 10000;
			PaddleShift = 7;
			break;
		case 4:
			DELAY_NORMAL = 22000;
			delay_normal = 22000;
			DELAY_BULLET = 10000;
			delay_bullet = 10000;
			BULLET = 20000;
			bullet = 10000;
			PaddleShift = 7;
			break;
		default:
			break;
	}
	clear();
	bkgd(COLOR_PAIR(10));
	refresh();
	brick **bricks;
	bricks = (brick **)malloc(NoRows * sizeof(brick*));              //brick array of 5*8
	for(i = 0;i < NoRows;i++)
		bricks[i] = (brick*)malloc(NoColumns * sizeof(brick));
	drawbricks(stdscr,bricks,ymax/3,xmax/3,NoRows,NoColumns,&xstart,&xend,level);
	refresh();
	object ball;
	ball.r.x = xmax/2;
	ball.r.y = ymax - 2;
	ball.v.x = 1;
	ball.v.y = -1;
	object powerup;
	powerup.v.x = 0;
	powerup.v.y = 1;
	coordinate paddle;
	paddle.x = xmax/2 - PaddleWidth/2;
	paddle.y = ymax - 1;
	int c;
	int feature_alive,feature;
	int powerups = 0;
	int dummy = 0;
	feature = 0;
	feature_alive = 0;
	mvprintw(xmax/2,10,"O");
	refresh();
	attron(COLOR_PAIR(11));
	mvprintw(ymax/2 + 8,xmax/2 - 19,"Adjust Paddle and press SPACE to start");
	attroff(COLOR_PAIR(11));
	refresh();
	sleep(1);
	mvprintw(ymax/2 + 8,xmax/2 - 19,"                                      ");
	WINDOW* window_paddle;
	window_paddle = createwindow(stdscr,ymax - 1,xmax/2 - 5,1,PaddleWidth);
	wbkgd(window_paddle,COLOR_PAIR(7));
	wrefresh(window_paddle);
	refresh();
	sleep(1);
	srand(time(NULL));
	while(1){
		c = wgetch(stdscr);
		if(c == ' ')
		break;
		switch(c){
			case KEY_LEFT:
				if(paddle.x >= 0){
					movepaddle(window_paddle,&paddle,LEFT,PaddleShift);
					ball.r.x -= PaddleShift;
					refresh();
				}
				break;
			case KEY_RIGHT:
				if(paddle.x <= xmax - 4){
					movepaddle(window_paddle,&paddle,RIGHT,PaddleShift);
					ball.r.x += PaddleShift;
					refresh();
				}
				break;
			default:
				break;
		}
	}
		while(1){
			attron(COLOR_PAIR(11));
			mvprintw(2,2,"Level: %d",level);
			attroff(COLOR_PAIR(11));
			refresh();
			if(powerups == 1){
				crash = checkforcollision(bricks,&powerup,xstart,xend,NoRows,NoColumns,&bullet,level);
				if(crash == 1){
					attron(COLOR_PAIR(11));
					score = score + 25;      //Score increases by 25 for each brick collision
					mvprintw(2,xmax/2 - 4,"Score: %d",score);
					attroff(COLOR_PAIR(11));
					powerups = 0;
				}
				else if(crash == 2)
					powerups = 0;
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
			if(feature_alive == 0 && feature == 0 && rand()%54321){      //rand()%frequency last argument as it is most expensive
				powerup.r.x = rand()%xmax;                           //54321 is some random number
				powerup.r.y = bricks[NoRows - 1][0].ydown;
				if(powerup.r.x >= xstart && powerup.r.x <= xend)
					feature_alive = 1;
			}
			if(feature_alive){
				if(powerup.r.y == paddle.y - 1){
					if(powerup.r.x >= paddle.x && powerup.r.x <= paddle.x + PaddleWidth)
						feature = 1;
					feature_alive = 0;
				}
				display(stdscr,powerup,8," ");
				usleep(BULLET);
				mvprintw(powerup.r.y,powerup.r.x," ");
				usleep(bullet);
				refresh();
				powerup.r.y = powerup.r.y + powerup.v.y;
			}
			if(powerups == 1){
				display(stdscr,powerup,11,"^");
				usleep(BULLET);
				mvprintw(powerup.r.y,powerup.r.x," ");
				refresh();
				usleep(bullet);
				powerup.r.y = powerup.r.y - powerup.v.y;
				if(powerup.r.y == 0)
					powerups = 0;
			}
			display(stdscr,ball,11,"O");
			if(feature_alive == 1 || powerups == 1)
				usleep(DELAY_BULLET);
			else
				usleep(DELAY_NORMAL);
			mvprintw(ball.r.y,ball.r.x," ");
			if(feature_alive == 1 || powerups == 1)
				usleep(delay_bullet);
			else
				usleep(delay_normal);
			refresh();
			crash = checkforcollision(bricks,&ball,xstart,xend,NoRows,NoColumns,&dummy,level);
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

			ball.r.y = ball.r.y + ball.v.y;
			ball.r.x = ball.r.x + ball.v.x;
			if(ball.r.y <= 0)
				ball.v.y = -ball.v.y;
			if(ball.r.x <= 0 || ball.r.x >= xmax)
				ball.v.x = -ball.v.x;
			if(ball.r.y == paddle.y - 1){
				if(ball.r.x >= paddle.x && ball.r.x <= paddle.x + PaddleWidth)
					ball.v.y = -ball.v.y;
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
						if(paddle.x >= 0){
							movepaddle(window_paddle,&paddle,LEFT,PaddleShift);
							refresh();
						}
						break;
					case KEY_RIGHT:
						if(paddle.x <= xmax - 4){
							movepaddle(window_paddle,&paddle,RIGHT,PaddleShift);
							refresh();
						}
						break;
					case KEY_UP:
						if(feature == 0 || powerups == 1)
							break;
						else{
							powerups = 1;
							powerup.r.x = paddle.x + PaddleWidth/2;
							powerup.r.y = paddle.y - 1;
							break;
						}
					default:
						break;
				}
			}
		}
	
}
