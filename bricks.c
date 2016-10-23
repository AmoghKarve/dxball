#include<ncurses.h>
#include "bricks.h"
#include "windows.h"

void drawbricks(WINDOW *orig,brick **bricks,int y,int x,int i,int j,int *xstart,int *xend){
	int l,m;
	int height = 2.5;
	int width = 7;
	int tempx,tempy;
	*xstart = x;
	tempy = y;
	start_color();
	init_pair(1,COLOR_RED,COLOR_WHITE);
	for(l = 0;l < i;l++){
		tempx = x;
		for(m = 0;m < j;m++){
			bricks[l][m].localwindow = createwindow(orig,tempy,tempx,height,width);
			box(bricks[l][m].localwindow,0,0);
			wbkgd(bricks[l][m].localwindow,COLOR_PAIR(1));
			wrefresh(bricks[l][m].localwindow);
			refresh();
			bricks[l][m].xleft = tempx;
			tempx = tempx + width;
			bricks[l][m].yup = tempy;
			bricks[l][m].ydown = tempy + height;
			bricks[l][m].xright = tempx; 
			bricks[l][m].alive = 1;
		}
		tempy = tempy + height;
	}
	*xend = tempx;
}
