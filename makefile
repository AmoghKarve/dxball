project:	mainfinal.c kbhit.c kbhit.h ball.c ball.h windows.c windows.h structures.h menu.c menu.h paddle.h paddle.c bricks.h bricks.c
	gcc mainfinal.c kbhit.c ball.c bricks.c windows.c menu.c paddle.c -g -lncurses -o project
clean:	
		rm project
