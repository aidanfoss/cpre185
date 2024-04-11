/*-----------------------------------------------------------------------------
-					         SE/CprE 185 Lab 04
-             Developed for 185-Rursch by T.Tran and K.Wang
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
-	                            Includes
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>


/*-----------------------------------------------------------------------------
-	                            Defines
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
-	                            Prototypes
-----------------------------------------------------------------------------*/
int close_to(double tolerance, double point, double value);
double mag(double a, double b, double c);

/*-----------------------------------------------------------------------------
-							  Implementation
-----------------------------------------------------------------------------*/
int main(void) {
    int t, b1, b2, b3, b4;
    double ax, ay, az, gx, gy, gz;
	int lastOutput;

	//printf("%d", close_to(0.25,1.0,0.8)); prints 1
	//printf("%d", close_to(0.25,1.0,1.5)); prints 0
	
	//return 0;
    while (1) {
        scanf("%d, %lf, %lf, %lf, %lf, %lf, %lf, %d, %d, %d, %d", &t, &ax, &ay, &az, &gx, &gy, &gz, &b1, &b2, &b3, &b4 );

        /* printf for observing values scanned in from ds4rd.exe, be sure to comment or remove in final program */
        //printf("Echoing output: %d, %lf, %lf, %lf, %lf, %lf, %lf, %d, %d, %d, %d", t, ax, ay, az, gx, gy, gz, b1, b2, b3, b4);
		//printf("%lf \n", mag(ax,ay,az));
		if (b1) {return 0;}
		if (close_to(0.2,0,mag(ax,ay,az))){
			if ((close_to(0.15, 1, gy))&& (lastOutput != 1)){ 
				lastOutput =1; 
				printf("Sticks Facing Up\n");
			}
			if ((close_to(0.15, -1, gy))&& (lastOutput != 2)){ 
				lastOutput =2;
				printf("Sticks Facing Down\n");
			}
			if ((close_to(0.15, 1, gx))&& (lastOutput != 3)){ 
				lastOutput =3;
				printf("Right Side Up\n");
			}
			if ((close_to(0.15, -1, gx))&& (lastOutput != 4)){ 
				lastOutput =4;
				printf("Left Side Up\n");
			}
			if ((close_to(0.15, -1, gz))&& (lastOutput != 5)){ 
				lastOutput =5;
				printf("Lights Up\n");
			}
			if ((close_to(0.15, 1, gz))&& (lastOutput != 6)){ 
				lastOutput =6;
				printf("Aux Port Up\n");
			}
		}
        /* It would be wise (mainly save time) if you copy your code to calculate the magnitude from last week
         (lab 3).  You will also need to copy your prototypes and functions to the appropriate sections
         in this program. */
		 //The only 3 vars that matter for which face is facing up is ax ay and az
		 

        //printf("At %d ms, the acceleration's magnitude was: %f\n", t, mag(ax, ay, az));

	
    
	}
	return 0;
}

/* Put your functions here */
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