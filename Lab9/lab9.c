// Lab 9 DS4Talker Skeleton Code

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <ncurses.h>
#define MAXWORDS 100
#define WORDLEN 11
#define SENTENCE_LEN 81
#define DEBUG 0   // set to 0 to disable debug output

// reads words from the file
// into wl and trims the whitespace off of the end of each word
// DO NOT MODIFY THIS Prototype
int readWords(char* wl[MAXWORDS], char* filename); 

//modifies s to trim white space off the right side
// DO NOT MODIFY THIS Prototype
void trimws(char* s);

int drawWords(char* wl[MAXWORDS], int numWords);

int addSent(char sentence[SENTENCE_LEN], char add[WORDLEN]);

int main(int argc, char* argv[]) 
{
	char* wordlist[MAXWORDS];
	int wordCount;
	int i;

	wordCount = readWords(wordlist, argv[1]);

	if(DEBUG)
	{
		printf("Read %d words from %s \n",wordCount, argv[1]);
		// add code to print the words to the screen here for part 1 
		for(i = 0; i < wordCount; i++)
		{
			printf("%s\n", wordlist[i]);
		}
	}

// most of your code for part 2 goes here. Don't forget to include the ncurses library 

	int t, tri, circle, x, square;
	int rb, lb, bb;
	int lx, ly, rx, ry;
	
	initscr();
	refresh();
	
	char sent[81] = "";
	int capNext = 0;
	int curAt = 0;
	
	int changed = 0;
	
	mvaddch(0, 0, '*');
	int row = drawWords(wordlist, wordCount);
	int lastMov = 0;
	
	int undo[80] = {0};
	int undoAt = 0;
	
	do
	{
		scanf("%d, %d,%d,%d,%d, %d,%d,%d,%d,%d,%d,%d,%d, %d, %d, %d, %d", &t, &tri, &circle, &x, &square, &rb, &lb, &bb, &bb, &bb, &bb, &bb, &bb, &lx, &ly, &rx, &ry);

		int oldAt = curAt;

		if(changed == 0){
			changed = 1;
			if(tri == 1){
				int added = addSent(sent, "          "); // i am not sure why but it would give errors if this wasn't 11 spaces???? works fine though
				if(added > 0){
					undo[undoAt] = added;
					undoAt++;
			}}
			else if(x == 1){
				if(undoAt > 0){
					sent[strlen(sent) - undo[undoAt - 1]] = '\0';
					undoAt--;
			}}
			else if(square == 1){
				if(capNext == 1){
					wordlist[curAt][0] = toupper(wordlist[curAt][0]);
					int added = addSent(sent, wordlist[curAt]);
					if(added > 0){
						undo[undoAt] = added;
						undoAt++;
					}
					wordlist[curAt][0] = tolower(wordlist[curAt][0]);
					capNext = 0;
				}
				else{
					int added = addSent(sent, wordlist[curAt]);
					if(added > 0){
						undo[undoAt] = added;
						undoAt++;
					}
					undoAt++;
			}}
			else if(1 == lb){
				sent[0] = '\0';
			}
			else{
				changed = 0;
		}}
		else if(0 == tri && 0 == square && 0 == x && 0 == lb){
			changed = 0;
		}
		
		if(t - lastMov > 500){
			lastMov = t;
			if(lx > 100){
				if(curAt < wordCount - 1){
					curAt++;
					changed = 1; //set changed to  prevent double placement
			}}
			else if(lx < -100){
				if(curAt > 0){
					curAt--;
					changed = 1;//set changed to  prevent double placement
			}}
			else if(ly > 100){
				if(curAt < wordCount - 6){
					curAt += 5;
					changed = 1;//set changed to  prevent double placement
			}}
			else if(ly < -100){
				if(curAt > 4){
					curAt -= 5;
					changed = 1;//set changed to  prevent double placement
			}}
			else{
				t = 0;
		}}
		else if(lx > -100 && lx < 100 && ly > -100 && ly < 100){
			t = 0;
		}
		
		if(changed == 1){
			mvprintw(row, 0, "%s", "                                                                                ");
			mvprintw(row, 0, "%s", sent);
			
			if(oldAt != curAt){
				mvaddch(oldAt / 5, (oldAt % 5) * 15, ' ');
				mvaddch(curAt / 5, (curAt % 5) * 15, '*');
			}
			
			refresh();
	}}while(1); //keep looping while program is running
	
    return 0;
}

int addSent(char sentence[SENTENCE_LEN], char add[WORDLEN])
{
	if(strlen(sentence) + strlen(add) < SENTENCE_LEN - 1)
	{
		strcat(sentence, add);
		return strlen(add);
	}
	
	return 0;
}

int drawWords(char* wl[MAXWORDS], int numWords)
{
	int loc = 0;
	do{
		mvprintw(loc / 5, (loc % 5) * 15 + 1, "%s", wl[loc]);
		at++;
	}while(at < numWords)
	refresh();
	
	return loc / 5 + 1;
}

/*
Scans a word and buffers it
*/
int readWords(char* wl[MAXWORDS], char* file)
{
	FILE* f = fopen(file, "r");
	int loc = 0;
	char buffer[WORDLEN];
	while(1 == fscanf(f, "%s", buffer)){
		trimws(buffer);
		wl[loc] = malloc(strlen(buffer) + 1);
		strcpy(wl[loc], buffer);
		at++;
	}
	return at;
}

void trimws(char* s)
{
	int length = strlen(s);
	for (int i = length - 1; i >= 0; i--){
		s[i] = '\0';
		i--;
	}
}