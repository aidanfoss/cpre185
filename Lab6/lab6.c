// 185 lab6.c
//
// This is the outline for your program
// Please implement the functions given by the prototypes below and
// complete the main function to make the program complete.
// You must implement the functions which are prototyped below exactly
//  as they are requested.

#include <stdio.h>
#include <math.h>
#define PI 3.141592653589

//gcc lab6.c | -o lab6

//NO GLOBAL VARIABLES ALLOWED

/*-----------------------------------------------------------------------------
-	                           Old Prototypes
-----------------------------------------------------------------------------*/
int close_to(double tolerance, double point, double value);
double mag(double a, double b, double c);

/*-----------------------------------------------------------------------------
-	                           New Prototypes
-----------------------------------------------------------------------------*/

//PRE: Arguments must point to double variables or int variables as appropriate
//This function scans a line of DS4 data, and returns
//  True when the square button is pressed
//  False Otherwise
//This function is the ONLY place scanf is allowed to be used
//POST: it modifies its arguments to return values read from the input line.
int read_line(double* g_x, double* g_y, double* g_z, int* time, int* Button_T, int* Button_X, int* Button_S, int* Button_C);

// PRE: -1.0 <= x_mag <= 1.0
// This function computes the roll of the DS4 in radians
// if x_mag outside of -1 to 1, treat it as if it were -1 or 1
// POST: -PI/2 <= return value <= PI/2
double roll(double x_mag);

// PRE: -1.0 <= y_mag <= 1.0
// This function computes the pitch of the DS4 in radians
// if y_mag outside of -1 to 1, treat it as if it were -1 or 1
// POST: -PI/2 <= return value <= PI/2
double pitch(double y_mag);


// PRE: -PI/2 <= rad <= PI/2
// This function scales the roll value to fit on the screen
// POST: -39 <= return value <= 39
int scaleRadsForScreen(double rad);

// PRE: num >= 0
// This function prints the character use to the screen num times
// This function is the ONLY place printf is allowed to be used
// POST: nothing is returned, but use has been printed num times
void print_chars(char use, int num);

//PRE: -39 <= number <=39
// Uses print_chars to graph a number from -39 to 39 on the screen.
// You may assume that the screen is 80 characters wide.
void graph_line(int number);

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

int main()
{
	int time;
	double x, y, z;                             // magnitude values of x, y, and z
	int b_Triangle, b_X, b_Square, b_Circle;    // variables to hold the button statuses
	double roll_rad, pitch_rad;                 // value of the roll measured in radians
	int scaled_value;                           // value of the roll adjusted to fit screen display

	//insert any beginning needed code here
	int setting = 0; //changes output, defaults to roll
	
	
	do
	{
		// Get line of input
		read_line(&x, &y, &z, &time, &b_Triangle, &b_X, &b_Square, &b_Circle);
		
		// calculate roll and pitch.  Use the buttons to set the condition for roll and pitch
		roll_rad = roll(x);
		pitch_rad = pitch(y);
		// switch between roll and pitch(up vs. down button)
		if (b_Triangle == 1){
			printf("triangle pressed");
			//would print but cant, maybe clear screen?
			switch (setting){
			case 0:
				setting = 1;
			case 1:
				setting = 0;
			default:
				setting = 0; //i have no clue how it would end up here but this doesnt hurt
			}
		}
		// Scale your output value
		switch (setting){
			case 0:
				scaled_value = scaleRadsForScreen(roll_rad);
			case 1:
				scaled_value = scaleRadsForScreen(pitch_rad);
			default:
				setting = 0; //i have no clue how it would end up here but this doesnt hurt
		}
		graph_line(scaled_value);
		fflush(stdout);
	} while (b_Triangle != 1); // Modify to stop when the square button is pressed
	
	return 0;
}

//---------------------------------------------------------------------------

int read_line(double* g_x, double* g_y, double* g_z, int* time, int* Button_T, int* Button_X, int* Button_S, int* Button_C){
	scanf("%lf, %lf, %lf, %d, %d, %d, %d, %d", g_x, g_y, g_z, time, Button_T, Button_X, Button_S, Button_C );
	//gx gy gz t Tri X Squ Cir
}
double roll(double x_mag){
	if (x_mag>1){x_mag = 1;}
	if (x_mag<-1) {x_mag = -1;}
	return (asin(x_mag));
}
double pitch(double y_mag){
	if (y_mag >= 1){y_mag = 1;}
	if (y_mag <= -1) {y_mag = -1;}
	return (asin(y_mag));
}
int scaleRadsForScreen(double rad){
		int screen = (rad * (39*2))/3.14;
		return screen;
}
void print_chars(char use, int num){
	for (int i = 0; i < num; i++)
	{printf("%c", use);}
}
void graph_line(int num){
	//printf("%d", num);
	int left_side = 39;
	num *= -1; // fixes left v right issue
	if (num == 0){
		printf("num == %d", num);
		print_chars(' ', left_side);
		print_chars('0', 1);
		print_chars('\n', 1);
	}
	else if (num < 0){
		printf("num == %d", num);
		int numnew = num * -1;
		left_side -= numnew; //reduces how many spaces are in front 
		print_chars(' ', left_side);
		print_chars('l', numnew);
		print_chars('\n', 1);
	}
	else if (num > 0){
		printf("num == %d", num);
		print_chars(' ', left_side);
		print_chars('r', num);
		print_chars('\n', 1);
	}
	
}
	
	
	
	
	
	
//OLD FUNCTIONS, likely wont use these, delete/ignore if unused
int close_to(double tolerance, double point, double value){
	double upTol = tolerance+point;
	double downTol = point-tolerance;
	if ((value > downTol) && (value < upTol)){
		return 1;
	}
	else {return 0;}
}

double mag(double a, double b, double c){
	double m = sqrt((a * a) + (b * b) + (c * c));
	return m;
}