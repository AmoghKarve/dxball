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


#include<ncurses.h>
#include "bricks.h"
#include "windows.h"

void drawbricks(WINDOW *orig,brick **bricks,float y,int x,int i,int j,int *xstart,int *xend,int level){
	int l,m;
	int height = 2.5;
	int width = 7;
	int tempx,tempy;
	*xstart = x;
	tempy = y;
	start_color();
	init_pair(1,COLOR_WHITE,COLOR_YELLOW);
	init_pair(2,COLOR_WHITE,COLOR_BLUE);
	init_pair(3,COLOR_WHITE,COLOR_GREEN);
	for(l = 0;l < i;l++){
		tempx = x;
		for(m = 0;m < j;m++){
			bricks[l][m].localwindow = createwindow(orig,tempy,tempx,height,width);
			bricks[l][m].xleft = tempx;
			tempx = tempx + width;
			bricks[l][m].yup = tempy;
			bricks[l][m].ydown = tempy + height;
			bricks[l][m].xright = tempx;
			if( (l + m) % 2 == 0){
				wbkgd(bricks[l][m].localwindow,COLOR_PAIR(2));
				wrefresh(bricks[l][m].localwindow);
				refresh();
				bricks[l][m].alive = 2;
			}
			else{ 
				wbkgd(bricks[l][m].localwindow,COLOR_PAIR(1));
				wrefresh(bricks[l][m].localwindow);
				refresh();
				bricks[l][m].alive = 1;
			}
			switch(level){
				case 1:
					break;
				case 2:
					if(((l == 1 || l == 3) && (m == 2 || m == 5))){
						wbkgd(bricks[l][m].localwindow,COLOR_PAIR(3));
						wrefresh(bricks[l][m].localwindow);
						refresh();
						bricks[l][m].alive = 3;
					}
					break;
				case 3:
					if(((l == 1 || l == 3) && (m == 2 || m == 5)) || ((l == 0 || l == 4) && (m == 0 || m == 7))){
						wbkgd(bricks[l][m].localwindow,COLOR_PAIR(3));
						wrefresh(bricks[l][m].localwindow);
						refresh();
						bricks[l][m].alive = 3;
					}
					break;
			}
		}
		tempy = tempy + height;
	}
	*xend = tempx;
}
