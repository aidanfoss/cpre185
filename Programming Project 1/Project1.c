/* 
Aidan Foss
awfoss@iastate.edu
CPRE 185 Section 3

Programming Practice 1

         <Reflection 1 What were you trying to learn or achieve?>

                If I could properly implement Rock Paper Scissors using mostly switch statements.
				I wanted to improve my knowledge on switch statements as i have never properly learned them in any of my previous computer science classes.
			
        <Reflection 2 Were you successful? Why or Why not?>

				Yes. This works better than i have made other ones in the past, and i was able to do so with only minor difficulty, even using switch statements.

		<Reflection 3 Would you do anything differently if starting this program over?  If so, explain what.>

				I would try to find some other way of evaluating who won, as having 3 switch statements in a switch statement seems like a brute force way of going about this.

		<Reflection 4 Think about the most important thing you learned when writing this piece of code.  What was it and explain why it was significant.>

				Switch statements are easier than I thought they were. Its nice to make what is essentially a grouping of if elses with such a small amount of clutter, 
				and they even have default cases in case you miss something, which makes reading someone elses work easier if theres an error resulting in a default output

		<Other questions/comments for Instructors>

				I was unable to check if my scanf was implemented correctly on ideone.com. Everything compiles I just dont seem to be able to input or use scanf on that site, so hopefully it works. 
				Everything else ive checked over using pseudocode, and there isnt any issues that would cause any error as far as I can see.

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
/*-----------------------------------------------------------------------------
-	                            Prototypes
-----------------------------------------------------------------------------*/
char randRPS(); //generates a random r p or s character for rock paper scissors
int playRPS(char a, char b); //compares two inputs as player 1 and player 2 to determine who wins. 
void playBot(); //starts a game of rock paper scissors against a bot. Player can decide when to quit whenever
/*-----------------------------------------------------------------------------
-							  Implementation
-----------------------------------------------------------------------------*/
int main(void) {
	int a;
	a = playRPS(randRPS(), randRPS());
	printf("%d", a);//prints if a random game of rock paper scissors is 0: a loss, 1: a win, 2: a tie, or 3:an error
	playBot();//begins a player controlled game of rock paper scissors.
}

/* Put your functions here */
char randRPS(){ //outputs a random rock paper or scissors char
	time_t t;
	srand((unsigned) time(&t)); //initializes random number
	int num = rand()%3;
	switch(num) { //switch statements are significantly faster than if elses, and I hate them, ngl.
		case 0:
			return 'r';
		case 1:
			return 'p';
		case 2:
			return 's';
	}
	return 'e'; //just in case, theoretically should never output this.
}

int playRPS(char a, char b){//outputs if player 1 (a) wins as a 1 or a 0, or a 2 if a tie 3 if an error
	//in other words, 0 is a win for player 2, 1 is a win for player 1, and a 2 is a tie, with 3 being an error
	switch(a){
		case 'r':
			switch(b){
				case 'r':
					return 2;
				case 'p':
					return 0;
				case 's':
					return 1;
			}
		case 'p':
			switch(b){
				case 'r':
					return 1;
				case 'p':
					return 2;
				case 's':
					return 0;
			}
		case 's':
			switch(b){
				case 'r':
					return 0;
				case 'p':
					return 1;
				case 's':
					return 2;
			}
	
	default:
		return 3; //returns 3 on an error
	}
}

void playBot(){
	int continuee = 1; //continue is not a valid variable name, i think it does something else. its like naming an int "int"
	char input;
	int play;
	while(continuee == 1){
		printf("type r, p, or s for rock paper scissors\n Type q to quit\n");
		scanf("%c", &input);
		if (input == 'r' || input == 'p' || input == 's'){
			play = playRPS(input, randRPS());
			switch(play){
				case 0:
					printf("you lost!\n play again:\n");
				case 1:
					printf("you won!\n play again:\n");
				case 2:
					printf("you tied!\n play again:\n");
				case 3: //should never print, edge case in case i did the % statement wrong
					printf("Error!\n play again:\n");
			}
		}
		else if (input == 'q') {
			printf("quitting");
			continuee = 0;
			} //stops loop if they want to quit
		else {
			printf("unknown input, try again\n");
		}
	}
}
