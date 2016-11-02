#include "ball.h"
#define totalbricks 40

int bricks_gone = 0;

int checkforcollision(brick **bricks,object *ball,int xstart,int xend,int p,int q,int *feature){
	int x;
	float y;
	int i,j;
	int crash = 0;
	int height = 2.5;
	int width = 7;
	if(*feature == 0){
		y = ball->r.y + ball->v.y;
		x = ball->r.x + ball->v.x;
	}
	else{
		x = ball->r.x;
		y = ball->r.y + ball->v.y;
	}
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
			if(bricks[i][j].alive == 3)
				crash = 0;
			if(bricks[i][j].alive == 2){
				wbkgd(bricks[i][j].localwindow,COLOR_PAIR(1));
				wrefresh(bricks[i][j].localwindow);
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
					if(y == bricks[i][j].yup || y == bricks[i][j].ydown)
						ball->v.y = -(ball->v.y);
					else
						ball->v.x = -(ball->v.x);
				}
				else
					ball->v.y = -(ball->v.y);
			}
		}
	}

                //terminate this while loop when all bricks are over or game is over.
                	if(bricks_gone == 60){
				return -1;
			}
	return crash;
}