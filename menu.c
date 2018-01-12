#include<ncurses.h>
#include<stdlib.h>
#include "menu.h"

int menu(WINDOW *orig){
	char list[4][50] = { "PLAY GAME", "HIGH SCORES", "ABOUT GAME", "EXIT"};
	char item[50];
	int ch, i = 0;
	int check = 0;
	/*char line[5][100] = {
	"|-------   |-------|   |-------|   |-------   |-------         |-------|   |-------   |-------",
	"|          |       |   |       |   |          |                |       |   |          |       ",
	"|------|   |-------|   |-------|   |          |-------   ---   |-------|   |          |-------",
	"       |   |           |       |   |          |                |       |   |          |       ", 
	"-------|   |           |       |   |-------   |-------         |       |   |-------   |-------"};*/
	char lineitem[100];
	int j = 0;
		
	WINDOW *w;
	w = newwin(15, 25, (LINES - 15) / 2, (COLS - 25) / 2 ); 
	box( w, 0, 0 ); 
	for( i=0; i<4; i++) {
		if( i == 0 ) 
			wattron( w, A_STANDOUT ); 
		else
			wattroff( w, A_STANDOUT );
			sprintf(item, "%s",  list[i]);
			mvwprintw( w, i+1, 2, "%s", item );
	}
	wrefresh(w);  
	
	i = 0;
	keypad( w, TRUE );
	while((ch = wgetch(w))) {
        	sprintf(item, "%-7s",  list[i]); 
        	mvwprintw( w, i+1, 2, "%s", item ); 
        	switch( ch ) {
                	case KEY_UP:
               			if(i == 0)
             	      		   	i = 3;
                    		else 
                        		i--;
                        	 
                		break;
                            
                	case KEY_DOWN:
                		if(i == 3)
                        		i = 0;   
                		else
        	                	i++;
	                	break; 
	
                	case 10:
				check = 1;
       				break;
        	}
            
		wattron( w, A_STANDOUT );
        	sprintf(item, "%-7s",  list[i]);
        	mvwprintw( w, i+1, 2, "%s", item);
        	wattroff( w, A_STANDOUT ); 
		if(check)
			break;
	}
	return i;
}


int levels(WINDOW *orig){
	char list[4][50] = { "LEVEL 1", "LEVEL 2", "LEVEL 3","LEVEL 4"};
	char item[50];
	int ch, i = 0;
	int check = 0;
	char lineitem[100];
	int j = 0;
		
	WINDOW *level;
	level = newwin(15, 25, (LINES - 15) / 2, (COLS - 25) / 2 ); 
	box(level, 0, 0 ); 
	for( i=0; i< 4; i++) {
		if( i == 0 ) 
			wattron(level, A_STANDOUT ); 
		else
			wattroff(level, A_STANDOUT );
			sprintf(item, "%s",  list[i]);
			mvwprintw(level, i+1, 2, "%s", item );
	}
	wrefresh(level);  
	
	i = 0;
	keypad(level, TRUE );
	while((ch = wgetch(level))) {
        	sprintf(item, "%-7s",  list[i]); 
        	mvwprintw(level, i+1, 2, "%s", item ); 
        	switch(ch){
                	case KEY_UP:
               			if(i == 0)
             	      		   	i = 3;
                    		else 
                        		i--;
                        	 
                		break;
                            
                	case KEY_DOWN:
                		if(i == 3)
                        		i = 0;   
                		else
        	                	i++;
	                	break; 
	
                	case 10:
				check = 1;
       				break;
        	}
            
		wattron(level, A_STANDOUT );
        	sprintf(item, "%-7s",  list[i]);
        	mvwprintw(level, i+1, 2, "%s", item);
        	wattroff(level, A_STANDOUT ); 
		if(check)
			break;
	}
	return i+1;
}

