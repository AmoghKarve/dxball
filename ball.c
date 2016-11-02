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
*
*You should have received a copy of the GNU Lesser General Public License
*along with this program; if not write to the Free Software Foundation,
*INC., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
********************************************************************************************/



#include "ball.h"

int bricks_gone = 0;

int checkforcollision(brick **bricks,object *ball,int xstart,int xend,int p,int q,int *feature,int level){
	int x;
	float y;
	int i,j;
	int totalbricks;
	int crash = 0;
	int height = 2.5;
	int width = 7;
	y = ball->r.y + ball->v.y;
	x = ball->r.x + ball->v.x;
	start_color();
	init_pair(1,COLOR_WHITE,COLOR_YELLOW);
	init_pair(10,COLOR_WHITE,COLOR_WHITE);
	if(x >= xstart && x <= xend){
	        j = (x - xstart)/width;
		if(y >= bricks[0][0].yup && y <= bricks[4][0].ydown){
			i = (y - bricks[0][0].yup)/height;
			if(i >= NoRows)
				return 0;
			crash = 1;
			if(bricks[i][j].alive == 0)
				return 0;
			if(bricks[i][j].alive == 3){
				wbkgd(bricks[i][j].localwindow,COLOR_PAIR(3));
				wrefresh(bricks[i][j].localwindow);
				wrefresh(bricks[i][j].localwindow);
				bricks[i][j].alive = 3;	
				crash = 0;
			}
			if(bricks[i][j].alive == 2){
				wbkgd(bricks[i][j].localwindow,COLOR_PAIR(1));
				wrefresh(bricks[i][j].localwindow);
				refresh();
				bricks[i][j].alive = 1;	
				crash = 1;
				bricks_gone++;
			}
			else if(bricks[i][j].alive == 1){
				wbkgd(bricks[i][j].localwindow,COLOR_PAIR(10));
				wrefresh(bricks[i][j].localwindow);
				refresh();
				crash = 1;
				bricks[i][j].alive = 0;
				bricks_gone++;
			}
			if(*feature == 0){
				if(x == bricks[i][j].xleft || x == bricks[i][j].xright){
					ball->v.x = -(ball->v.x);
				}
				else
					ball->v.y = -(ball->v.y);
			}
		}
	}
	switch(level){
		case 1:
			totalbricks = 40;
			break;
		case 2:
			totalbricks = 54;
			break;
		case 3:
			totalbricks = 48;
			break;
	}
                //terminate this while loop when all bricks are over or game is over.
                	if(bricks_gone == totalbricks){
				return -1;
			}
	return crash;
}
