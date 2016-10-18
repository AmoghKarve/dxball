#include<ncurses.h>
#include "bricks.h"
#include "windows.h"

void drawbricks(WINDOW *orig,brick bricks[][8],int y,int x,int i,int j,int *xstart,int *xend){
	int l,m;
	int height = 2.5;
	int width = 7;
	int tempx,tempy;
	*xstart = x;
	tempy = y;
	for(l = 0;l < 5;l++){
		tempx = x;
		for(m = 0;m < 8;m++){
			bricks[i][j].localwindow = createwindow(orig,tempy,tempx,height,width);
			box(bricks[i][j].localwindow,0,0);
			wrefresh(bricks[i][j].localwindow);
			refresh();
			bricks[i][j].xleft = tempx;
			tempx = tempx + width;
			bricks[i][j].yup = y;
			bricks[i][j].ydown = y + height;
			bricks[i][j].xright = tempx; 
		}
		tempy = tempy + height;
	}
	*xend = tempx + width;
}
