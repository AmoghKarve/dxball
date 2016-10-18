#include "ball.h"
#define totalbricks 40

int bricks_gone = 0;

void checkforcollision(brick bricks[][8],int y,int x,int dy,int dx,int xstart,int xend){
	int tempy,tempx;
	int i,j;
	int height = 2.5;
	int width = 7;
	start_color();
	init_pair(1,COLOR_RED,COLOR_BLACK);	
		/*Checking for collision*/
                if(x >= xstart && x <= xend){
                        j = (x - xstart)/width;
                        for(i = 0;i < 5;i++){
                                        if(y >= bricks[i][j].ydown && y <= bricks[i][j].yup && bricks[i][j].alive == 1){
                                        	wborder(bricks[i][j].localwindow,' ',' ',' ',' ',' ',' ',' ',' ');
                                        	wrefresh(bricks[i][j].localwindow);
                                        	refresh();
                                        	if(x == bricks[i][j].xleft || x == bricks[i][j].xright)
                                        	        dx = -dx;
                                        	else
                                        	        dy = -dy;
                                        	bricks[i][j].alive = 0;
                                        	bricks_gone++;
                                        	break;
                                }
                        }
                //terminate this while loop when all bricks are over or game is over.
                	if(bricks_gone == totalbricks)    //Find totalbricks
                        	printw(0,0,"GAME OVER");
        	}
}
