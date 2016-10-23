#include "ball.h"
#define totalbricks 40

int bricks_gone = 0;

void checkforcollision(brick **bricks,int y,int x,int *dy,int *dx,int xstart,int xend,int p,int q){
	int tempy,tempx;
	int i,j;
	int height = 2.5;
	int width = 7;
	/*if(y == bricks[4][0].ydown){
		wborder(bricks[3][2].localwindow,' ',' ',' ',' ',' ',' ',' ',' ');
		wrefresh(bricks[3][2].localwindow);
	}*/

	if(x >= xstart && x <= xend){
	        j = (x - xstart)/width;
		if(y >= bricks[0][0].yup && y <= bricks[4][0].ydown){
			i = (y - bricks[0][0].yup)/height;
			if(i > 4)
				return;
			if(bricks[i][j].alive == 0)
				return;
			if(x == bricks[i][j].xleft || x == bricks[i][j].xright)
				*dx = -*dx;
			else
				*dy = -*dy;
			wborder(bricks[i][j].localwindow,' ',' ',' ',' ',' ',' ',' ',' ');
			wrefresh(bricks[i][j].localwindow);
			refresh();
			bricks[i][j].alive = 0;
		}
	}

	start_color();
	init_pair(1,COLOR_RED,COLOR_BLACK);	
	/*	Checking for collision
                if(x >= xstart && x <= xend){
                        j = (x - xstart)/width;
                        for(i = 0;i < p;i++){
                                        if(y >= bricks[i][j].ydown && y <= bricks[i][j].yup && bricks[i][j].alive == 1){
                                        	wborder(bricks[i][j].localwindow,' ',' ',' ',' ',' ',' ',' ',' ');
                                        	wrefresh(bricks[i][j].localwindow);
                                        	refresh();
                                        	if(x == bricks[i][j].xleft || x == bricks[i][j].xright)
                                        	        *dx = -*dx;
                                        	else
                                        	        *dy = -*dy;
                                        	bricks[i][j].alive = 0;
                                        	bricks_gone++;
                                        	break;
                               		}
                        }
                //terminate this while loop when all bricks are over or game is over.
                	if(bricks_gone == totalbricks)    //Find totalbricks
                        	printw(0,0,"GAME OVER");
        	}*/
	
}
