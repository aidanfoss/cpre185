// WII-MAZE Skeleton code written by Jason Erbskorn 2007
// Edited for ncurses 2008 Tom Daniels
// Updated for Esplora 2013 TeamRursch185
// Updated for DualShock 4 2016 Rursch


// Headers
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncurses/ncurses.h>
#include <unistd.h>
//#include <string.h>

// Mathematical constants
#define PI 3.14159

// Screen geometry
// Use ROWS and COLS for the screen height and width (set by system)
// MAXIMUMS
#define NUMCOLS 100
#define NUMROWS 72

// Character definitions taken from the ASCII table
#define AVATAR 'A'
#define WALL '*'
#define EMPTY_SPACE ' '


// 2D character array which the maze is mapped into
char MAZE[NUMROWS][NUMCOLS];

int close_to(double tolerance, double point, double value);

// POST: Generates a random maze structure into MAZE[][]
//You will want to use the rand() function and maybe use the output %100.  
//You will have to use the argument to the command line to determine how 
//difficult the maze is (how many maze characters are on the screen).
void generate_maze(int difficulty);

// PRE: MAZE[][] has been initialized by generate_maze()
// POST: Draws the maze to the screen 
void draw_maze(void);

// PRE: 0 < x < COLS, 0 < y < ROWS, 0 < use < 255
// POST: Draws character use to the screen and position x,y
void draw_character(int x, int y, char use);

// PRE: -1.0 < x_mag < 1.0
// POST: Returns tilt magnitude scaled to -1.0 -> 1.0
// You may want to reuse the roll function written in previous labs.  
float calc_roll(float x_mag);

// Main - Run with './ds4rd.exe -t -g -b' piped into STDIN
int main(int argc, char* argv[])
{
	if (argc <2) { printf("You forgot the difficulty\n"); return 1;}
	int difficulty = atoi(argv[1]); // get difficulty from first command line arg
	// setup screen    
	initscr();
	refresh();

	// Generate and draw the maze, with initial avatar
	generate_maze(difficulty);
	draw_maze();
	// Read gyroscope data to get ready for using moving averages.    
	double gx, gy, gz;
	int t, button_T, button_C, button_S, button_X;
	//scanf("%lf, %lf, %lf, %d, %d, %d, %d", &gx, &gy, &gz, &t, &button_T, &button_C, &button_X, &button_S);
	
	//starter values
	int curx = NUMCOLS/2;
	int	cury = 0;
	int nextx = curx;
	int win = -1; //win condition check, -1 is error output at the end
	/*Unneeded variables
	//int nexty = cury+1; //we can always assume wanting to go down. therefore this is not needed
	//int prevx = -999; //should get overwritten before first use
	//int prevy = -999; //should get overwritten before first use
	
	//int first = 1; maybe needed for initializing the avatar
	*/
	int failCount = 0;
	int nextT =1000;
	int first =1;
	int count = 0;
	
	
	
	do // Event loop
	{
		if (first){
			draw_character(curx,cury,AVATAR);
			first =0;
		}
		// Read data, update average
		scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d", &t, &gx, &gy, &gz, &button_T, &button_C, &button_X, &button_S);

		/* PSEUDOCODE IN CONTAINER, CHECK FOR LEAN, UPDATE NEXTX ACCORDINGLY
		scan data
		check if not leaning or leaning left or right
		if not leaning{
			nextx = curx;
		}
		else if leaning left{
			nextx = curx-1;
		}
		else if leaning right{
			nextx =curx+1;
		}
		 END PSEUDOCODE */					
		if (gx > 0.25){
			nextx = curx+1;
		} else if (gx < -0.25){
			nextx = curx-1;
		} else { //close_to(0.25, 0, ax) dont need an if statement if i check for the only 2 other options, left and right
			nextx = curx;
		}
		
		
		
		
		// Is it time to move?  if so, then move avatar
		if (t % 10 == 0){
			printf("%d test", cury);
			if (cury+1 >= 71) { //win condition
				win = 1;
			}
			else if (MAZE[nextx][cury+1] == EMPTY_SPACE){ //check if space we want to go is empty
				draw_character(nextx, cury+1, AVATAR);
				draw_character(curx, cury, EMPTY_SPACE);
				//update position values
				curx = nextx;
				cury = cury+1;
				failCount =0;
			}
			/*a Check here if the previous statement fails, ie: we want to go right but cant because a wall is there, so it should 
			check if it can go down and not right*/
			else if(MAZE[curx][cury+1] == EMPTY_SPACE){
				draw_character(curx,cury+1, AVATAR);
				draw_character(curx,cury, EMPTY_SPACE);
				//update position values
				cury = cury+1;
				failCount=0;
			}
			/*a Check here if the previous statement fails AGAIN, check if they can move horizontally */
			else if (MAZE[nextx][cury] == EMPTY_SPACE){
				draw_character(nextx,cury, AVATAR);
				draw_character(curx,cury, WALL);
				//update position values
				curx = nextx;
				failCount=0;
			}
			else if (failCount == 5){ //allows them to try to move another direction
				win = 0;
				//break;
			}
			//else {failCount++;}
		}

	} while(cury > 71); //ends if character reaches the end
	



	//a Check if win or lose
	if (win == -1){ //check for error
		printf("ERROR. YOU DIDNT WIN OR LOSE\n");
	}
	else if (win == 1){ //Print the win message
		printf("YOU WIN!\n");
	}
	else { //no if needed because theres only 3 possible outcomes, -1 for error, 0 for loss, and 1 for win
		printf("YOU LOSE!\n");
	}
	return 0;
}

void draw_maze(void){
	for(int i=0;i<NUMROWS;i++) {
		for(int j=0;j<NUMCOLS;j++) {
			draw_character(j, i, MAZE[i][j]);
		}
	}
	refresh();
}

void generate_maze(int difficulty){
	//srand(time(NULL));
	for(int i=0;i<NUMROWS;i++) {
		for(int j=0;j<NUMCOLS;j++) {
			int rnd = rand() % 100;
			if(rnd < difficulty) {
				MAZE[i][j] = WALL;
			} else {
				MAZE[i][j] = EMPTY_SPACE;
			}
		}
	}
}

int close_to(double tolerance, double point, double value){
	double upTol = tolerance+point;
	double downTol = point-tolerance;
	if ((value > downTol) && (value < upTol)){
		return 1;
	}
	else {return 0;}
}



// PRE: 0 < x < COLS, 0 < y < ROWS, 0 < use < 255
// POST: Draws character use to the screen and position x,y
//THIS CODE FUNCTIONS FOR PLACING THE AVATAR AS PROVIDED.
//
//    >>>>DO NOT CHANGE THIS FUNCTION.<<<<
void draw_character(int x, int y, char use)
{
	mvaddch(y,x,use);    
	refresh();
}


