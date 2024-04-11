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
	int still=1;
	int stopped = 0;
	int tStart,tEnd;
	int count = 0;
	
	printf("Aidan Foss\n Netid: awfoss\nOk, I'm now recieving data.\n");
	printf("I'm Waiting.");
    while (1) {
		scanf("%d, %lf, %lf, %lf", &t, &ax, &ay, &az);
		if (close_to(25,0,t%1000)){
			printf(".");
		}
		
		if(close_to(0.5,0,mag(ax,ay,az))){
			printf("\n\t\t Help me! I'm falling!");

			count = 0;
			
			tPrev = t;
			while(close_to(0.5,0,mag(ax,ay,az))){
				scanf("%d, %lf, %lf, %lf", &t, &ax, &ay, &az);
				

				printf("%d  ",t);
				if (close_to(25,0,t%100)){
					printf("!");
				}
				fflush(stdout);
			}
			
			double tTotal = (tEnd - tStart)/1000.0;
			double distance = 0.5 * 9.81 * (tTotal*tTotal);
			printf("\n\t\t\tOuch! I fell %lf meters in %lf seconds" , distance, tTotal);
			printf("\n %d - %d = %lf", tEnd, tStart, tTotal);
			break;
		}
		fflush(stdout);
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