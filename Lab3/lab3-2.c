/* 185 Lab 3 Template */

#include <stdio.h>
#include <math.h>

/* Put your function prototypes here */
/*double mag(double a, double b, double c);
int minutes(int ms);
int seconds(int ms);
int millis(int ms);*/
int numPress(int a,int b,int c,int d);

int main(void) {
    /* DO NOT MODIFY THESE VARIABLE DECLARATIONS */
    int t;
    double  ax, ay, az;     

	int a,b,c,d = 0;
    /* This while loop makes your code repeat. Don't get rid of it. */
    while (1) {
        scanf("%d,%d,%d,%d",&a, &b, &c, &d); 
		printf("%3d, %3d, %3d, %3d, %5d\n",a,b,c,d,numPress(a,b,c,d));
		fflush(stdout);
	}
}

/* CODE SECTION 0 

		double sec = t/1000.0;
		//double bx = ax % 0.0001;
		//double by = ay % 0.0001;
		//double bz = az % 0.0001;
        printf("Echoing output: %8.3lf, %7.4lf, %7.4lf, %7.4lf\n", sec, ax, ay, az);
	*/

/* CODE SECTION 1 
        printf("At %d ms, the acceleration's magnitude was: %lf\n", t, mag(ax, ay, az));  
            */
			
/* CODE SECTION 2 */
		/*
	  printf("At %d minutes, %d seconds, and %d milliseconds it was: %lf\n", 
        minutes(t), seconds(t), millis(t), mag(ax,ay,az)); 

    }
	

return 0;
}
*/

/* Put your functions here */
int numPress(int a, int b, int c, int d){
	return a+b+c+d;
}
/*double mag(double a, double b, double c){
	double m = sqrt((a * a) + (b * b) + (c * c));
	return m;
}
int minutes(int ms){
	int min = ms / 60000; // converts ms directly into mins (abuses int math, definitely a better way of doing this)
	return min;
}
int seconds(int ms){
	int sms = ms % 60000;
	int sec = sms / 1000;
	return sec;
}
int millis(int ms){
	int mss = ms % 1000;
	return mss;
}

*/