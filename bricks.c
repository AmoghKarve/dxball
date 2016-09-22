#include<ncurses.h>
int height=2;
int width = 7;
typedef struct brick{
	WINDOW* localwindow;
	int xleft,xright,yup,ydown;	
	int alive = 1;
}brick;
void drawbricks(WINDOW *orig,int ymax,int xmax);
int main(){
	int xmax,ymax,i,j,x,y;
	int xstart,xend;
	initscr();
	cbreak();
	//int xmax,ymax,i,x,y;
	getmaxyx(stdscr,ymax,xmax);
	box(stdscr,0,0);
	refresh();
	//printw("test");
	refresh();
	usleep(100000);
	brick bricks[8][5];
	y = ymax/3;
	x = xmax/4;
	(bricks[0][0]).localwindow = derwin(stdscr,height,width,y,x);
	//temp = localwindow;
	for(i = 0;i<5;i++){
		x = xmax/4;
		for(j = 0;j<10;j++){
			bricks[i][j].localwindow = derwin(stdscr,height,width,y,x);
			box(bricks[i][j].localwindow,0,0);
			wrefresh(bricks[i][j].localwindow);
			refresh();
			x = x + width;
		}
		y = y + height;
	}

	//drawbricks(stdscr,ymax,xmax);
	refresh();
	usleep(5000000);
	i = 3;
	//generalised clearing on collision
	while(1){
		if(x >= xstart && x <= xend){
			i = (x - xstart)/width;
			for(j = 0;j<5;j++){
					if(y >= bricks[i][j]->ydown && y <= bricks[x][j]->yup && bricks[i][j]->alive == 1){
					wclear(bricks[i][j]);
					delwin(bricks[i][j]);
					refresh();
					if(x == bricks[i][j]->xleft || x == bricks[i][j]->xright)
						dx = -dx;
					else
					dy = -dy;
					alive = 0;
					break;
				}
			}
		//terminate this while loop when all bricks are over or game is over.
	}
	usleep(5000000);
	endwin();
}

void drawbricks(WINDOW *orig,int ymax,int xmax){
	int i = 0;
	int x,y;
	x = xmax;
	y = ymax;
	WINDOW *localwindow;
	for(i = 0;i<8;i++){
		localwindow = derwin(orig,height,width,y,x);
		box(localwindow,0,0);
		wrefresh(localwindow);
		refresh();
		x = x + width;
	}
	return;
}

