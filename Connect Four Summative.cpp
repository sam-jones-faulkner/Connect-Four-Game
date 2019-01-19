//Sam Faulkner May/June 2016 Connect Four Summative Game Ms. Cullum ICS3U

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//prototyping
bool isWinnerRow();
bool isWinnerCol();
bool isWinnerDiagonal();
bool isTie();
void instructions();
void drawGameBoard();
int placeTile(int col);
int calcAge(struct User person[]);
int convertMonth(struct User human);
int highScoreWinner(int countPlayWin, int &scoreWin);
int highScoreLoser(int countPlayLose, int &scoreLose);

//globals
char board[5][5];
char piece = 'X';
int row[5] = {4, 4, 4, 4, 4};

//structures
struct Date {

	int dies;
	char mensis[10];
	int anni;
};

struct User {

	char nomen[20];
	Date age;
	Date hodie;
} player[2];


/*In this function, user input will be collected and most of the printing will occur. 
It was also run most of the functions and is responsible for the title page and most of the user interface.
Loops inside the function ensure continuous game play until otherwise indicated by the user.*/

int main() {
	
	//variable declaration
	int start;
	int column;
	int winAge = 0;
	int turnCounter;
	int totalScoreWin = 0;
	int totalScoreLose = 0;
	int totalWin = 0;
	int totalLose = 0;
	int getScore;
	int doItAgain;
	bool playAgain = true;
	bool vale1 = false;
	bool vale2 = false;
	bool vale3 = false;
	bool vale4 = false;
	FILE *accessScore;
	
	//continue running game until the users want to exit or there is an invalid command
	while (playAgain == true) {
	
		//title screen
		printf("\n*****************************************\n");
		printf("Welcome to Colossal Connect Four Classic.\n");
		printf("Press 1 for instructions.\nPress 2 to start.\nPress 3 to access the high score.\nPress 4 for references.\nPress 5 to exit.\n");
		printf("*****************************************\n\n");
		scanf("%d", &start);

		turnCounter = 0; 

		//initialize board[5][5]
		for(int i = 0; i < 5; i++) {

			for(int j = 0; j < 5; j++) {

				board[i][j] = '\0';
			}
		}

		//initialize the row global
		for(int i = 0; i < 4; i ++) {

			row[i] = 4;
		}
		
		//initialize the win check functions
		vale1 = false;
		vale2 = false;
		vale3 = false;
		vale4 = false;

		//run instructions function
		if(start == 1) {

			instructions();
		}

		//run the actual game
		else if(start == 2) { 

			//acquiring information for user1
			printf("User1: Please enter the following information: first name, birthday (day, month, year), and today's date (all lowercase).\nExample:\nname\n22 may 2016\n\n");
			
			scanf("%s", player[0].nomen); 
			
			scanf("%d %s %d", &player[0].age.dies, player[0].age.mensis, &player[0].age.anni); 
			
			scanf("%d %s %d", &player[0].hodie.dies, player[0].hodie.mensis, &player[0].hodie.anni); 

			//acquiring information for user2
			printf("\nUser2: Please enter the following: first name and birthday (all lowercase).\nExample:\nname\n22 may 2016\n\n");
			
			scanf("%s", player[1].nomen); 

			scanf("%d %s %d", &player[1].age.dies,player[1].age.mensis, &player[1].age.anni); 

			printf("\nLet's begin!\n\n");
			
			system("clear"); 
			drawGameBoard();

			//continue running the game until there is a win
			while (vale1 == false && vale2 == false && vale3 == false && vale4 == false) { 
				
				//USER : alternate user turns and output where they placed their letter
				printf("\n%s: Please enter which column you would like to place your X.\n", player[0].nomen); 
				scanf("%d", &column); 

				turnCounter++; 

				if(column > 4) { 

					printf("That is an invalid entry.\n");
				}

				else {

					piece = 'X'; 

					if(placeTile(column) == 1) { 
						
						printf("The column is full. You broke the world.\n");
					}

					else { 

						drawGameBoard(); 

						//Run all the win check functions
						vale1 = isWinnerCol();
						vale2 = isWinnerRow(); 
						vale3 = isWinnerDiagonal(); 
						vale4 = isTie(); 

						if(vale1 == true || vale2 == true || vale3 == true) {

							printf("\nCongratulations, %s you are the winner.\n\n", player[0].nomen); 
							printf("You won on %d %s %d:)\n", player[0].hodie.dies, player[0].hodie.mensis, player[0].hodie.anni);

							winAge = calcAge(player); 

							totalWin = highScoreWinner(turnCounter, totalScoreWin);

							totalLose = highScoreLoser(turnCounter, totalScoreLose);

							if(totalWin == 0) {

								printf("%s, your score is %d.\n", player[0].nomen, totalScoreWin);
							}

							if(totalWin == 1) {

								printf("%s, your score is %d.\n", player[0].nomen, totalScoreWin);
								printf("You have achieved the high score!\n");
							}

							if(totalLose == 0) {

								printf("%s, you have lost. Your final score is %d\n", player[1].nomen, totalScoreLose); 
							} 

							if(winAge == 1) { 

								printf("The oldest person won!\n\n");
							}

							else if(winAge == 0) {

								printf("The youngest person won!\n\n");
							}

							else {

								printf("You have the same birthday.\n\n");
							}

							printf("Would you like to play again? 5 = yes, 6 = no\n");
							scanf("%d", &doItAgain);

							if(doItAgain == 5) {

								playAgain = true;
							}

							else if(doItAgain == 6) {

								playAgain = false; 
							}

							else {

								playAgain = false; 
							}

							break; 
						}

						if(vale4 == true) {

							printf("This game has ended in a tie.\n");
							printf("%s and %s are both winners on %d %s %d:)\n", player[0].nomen, player[1].nomen, player[0].hodie.dies, player[0].hodie.mensis, player[0].hodie.anni);
							
							printf("Would you like to play again? 5 = yes, 6 = no\n");
							scanf("%d", &doItAgain);

							if(doItAgain == 5) {

								playAgain = true;
							}

							else if(doItAgain == 6) {

								playAgain = false; 
							}

							else {

								playAgain = false; 
							}
							
							break; 
						} 
					}
				}
				
				//USER 2: alternate user turns and output where they placed their letter
				printf("\n%s: Please enter which column you would like to place your O.\n", player[1].nomen);
				scanf("%d", &column); 

				if(column > 4) { 

					printf("That is an invalid entry.\n");
				}

				else {

					piece = 'O'; 

					if(placeTile(column) == 1) { 

						printf("The column is full. You broke the world.\n");
					}

					else {

						drawGameBoard(); 
						
						//Run the win check functions
						vale1 = isWinnerCol(); 
						vale2 = isWinnerRow(); 
						vale3 = isWinnerDiagonal(); 
						vale4 = isTie(); 

						if(vale1 == true || vale2 == true || vale3 == true) {

							printf("\nCongratulations, %s you are the winner.\n\n", player[1].nomen); 
							printf("You won on %d %s %d:)\n", player[0].hodie.dies, player[0].hodie.mensis, player[0].hodie.anni);
					
							winAge = calcAge(player); 

							totalWin = highScoreWinner(turnCounter, totalScoreWin);

							totalLose = highScoreLoser(turnCounter, totalScoreLose);

							if(totalWin == 0) {

								printf("%s, your score is %d.\n", player[1].nomen, totalScoreWin);
							}

							if(totalWin == 1) {

								printf("%s, your score is %d.\n", player[1].nomen, totalScoreWin);
								printf("You have achieved the high score!\n");
							}

							if(totalLose == 0) {

								printf("%s, you have lost. Your final score is %d\n", player[0].nomen, totalScoreLose); 
							} 

							if(winAge == 0) { 

								printf("The oldest person won!\n\n");
							}

							else if (winAge == 1) {

								printf("The youngest person won!\n\n");
							}

							else {

								printf("You have the same birthday.\n\n");
							}

							printf("Would you like to play again? 5 = yes, 6 = no\n");
							scanf("%d", &doItAgain);

							if(doItAgain == 5) {

								playAgain = true;
							}

							else if(doItAgain == 6) {

								playAgain = false; 
							}

							else {

								playAgain = false; 
							}

							break; 
						}

						if(vale4 == true) {

							printf("This game has ended in a tie.\n");
							
							printf("%s and %s are both winners on %d %s %d:)\n", player[0].nomen, player[1].nomen, player[0].hodie.dies, player[0].hodie.mensis, player[0].hodie.anni);

							printf("Would you like to play again? 5 = yes, 6 = no\n");
							scanf("%d", &doItAgain);

							if(doItAgain == 5) {

								playAgain = true;
							}

							else if(doItAgain == 6) {

								playAgain = false; 
							}

							else {

								playAgain = false; 
							}
						
							break; 
						} 
					}
				}	
			}
		}

		//High score check
		else if(start == 3) {

			accessScore = fopen("/Users/samfaulkner/Desktop/Sam Da Coding Master/highscore.txt", "r");

			if(accessScore == NULL) { 

				printf("Error. The file did not open.\n");
			}

			fscanf(accessScore, "%d", &getScore);

			printf("The current high score is %d.\n\n", getScore);

			fclose(accessScore);

		}

		//References
		else if(start == 4) {

			printf("Thank you to:\n");
			printf("Charles Zhang, Miasya Bulger, Arsheya Jain, Hasbro games\n\n");

		}

		//Exit the game
		else if(start == 5) {

			printf("Thanks for playing.\n\n");

			playAgain = false; 
		} 
	
		else {

			printf("Sorry, but this command is invalid.\n\n");

			playAgain = false; 
		}			
	}	
		
		return 0;
}

/* This function is reponsible for printing out the game board. 
It receives information from the placeTile function and prints the determined character onto the game board.
The first for loop prints the first line of the game board, the next for loops are responsible for the rest of the board*/

void drawGameBoard(){

		//header for the game board
		printf("	0 		1 		2 		3 		4\n"); 

		for(int i = 0; i < 40; i ++) { 

			printf("**");
	
		}

		printf("\n");

		for(int i = 0; i < 5; i++) { 
			
			for(int j = 0; j < 5; j++) { 
		
				printf("* 	%c	", board[i][j]);

			}
			
			printf("*\n"); 
			
			for(int k = 0; k < 5; k++) { 

				printf("* 		");
			}

			printf("*\n"); 

			for(int l = 0; l < 40; l ++) { 

				printf("**");
	
			}

			printf("\n");
		}
}

/*This function takes the column that the user wants to place their piece in and determines where in that column it can go (or if it can't go into the column at all).
It checks to see if the place in the game array is empty, and it if is then it puts piece in that spot.*/

int placeTile(int col) {

	if(row[col] == -1) {

		return 1; 
	}

	else if(board[row[col]][col] == '\0') { 
		
		board[row[col]][col] = piece; 

		row[col]--; 

		return 0;
	}

	else {

		return 1;
	}
} 

/*This function prints out the instructions for the game.
It also gives the users an option to clear the game board if they would like.*/

void instructions() {

	int commence;

	printf("Objective: To get four of your letters in a row, either horizontally, vertically, or diagonally. ");
	printf("To begin the game, press 2 to start and enter the information required. ");
	printf("Next, enter the number of the column where you want your piece. The piece will automatically go to the lowest blank square on the grid. ");
	printf("Exchange turns between players until one player has connected four of their letters in a row, where they will be deemed the winner.\n\n");
	
	printf("Press 1 if you want to clear the screen. Press any other number to continue.\n");
	scanf("%d", &commence);

	if(commence == 1) {

		system("clear"); 
	}	
}

/* This function is responsible for scanning through the rows in the array to check for four in a row (which is a win).
It scans through the entire array while checking for the same piece and adds to the counter for every piece that is the same (and resets when two pieces are different).
*/
bool isWinnerRow(){

	int counter = 0;

	//checking for each row for the first four columns (0, 1, 2, 3)
	for(int i = 0; i < 5; i ++) { 

		for(int j = 0; j < 5; j ++) { 

			if(board[i][j] == piece) {

				counter++; 

				if(counter == 4) { 

					return true;
				}
			}

			else {

				counter = 0; 
			}
		}
	}

	return false;	
}

/* This function is responsible for determining a win for the columns.
It checks to see if four of the same piece are in a row.
It scans through the entire array and adds to the counter when it encounters a piece that is the same (and resets it when it's not).
This is essentially the same as the isWinnerRow function except it is inverted to check the columns instead of rows.*/

bool isWinnerCol() {

	int counter = 0;

	//checking for each row for the first four columns (0, 1, 2, 3)
	for(int i = 0; i < 5; i ++) { 

		for(int j = 0; j < 5; j ++) { 

			if(board[j][i] == piece) {

				counter++; 

				if(counter == 4) { 

					return true;
				}
			}

			else {

				counter = 0; 
			}
		}
	}

	return false;	
} 

/* This function checks for four pieces in a row diagonally. 
The two sets of nested while loops are responsible for different directions on the game board.
This function uses the line equation y = mx+b to check to see if there are four of the same piece in a row.
Like the other isWinner functions, it uses a counter to add determine whether there are four in a row, and resets the counter when one that isn't in a row is encountered.
*/

bool isWinnerDiagonal() {

	int count;
	int y; //row
	int m;
	int x; //column
	int b; //y intersect

	for(int b = -1; b < 2; b ++) {

		count = 0;

		for(int x = 0; x < 5; x ++) { 

			y = x + b;

			if(y >= 0 && y <= 4) { 
				
				if(board[y][x] == piece) { 

					count++;	

					if(count == 4) {

						return true;
					}
				}	
				
				else {

					count = 0;
				}
			}
		}
	} 

	for(int b = 3; b < 6; b ++) {

		count = 0;

		for(int x = 0; x < 5; x ++) { 

			//negative slope
			y = -x + b; 

			if(y >= 0 && y <= 4) { 
				
				if(board[y][x] == piece) { 

					count ++;	

					if(count == 4) {

						return true;
					}
				}
				
				else {

					count = 0;
				}
			
			}
		}	
	}

	return false;
}

/*This function converts the characters which indicate month into the appropriate number.
It does this by usng string compare, and users are told to only enter lower case so this can work.*/

int convertMonth(struct User human) { 

	if(strcmp(human.age.mensis, "january") == 0) {

		return 1;

	} 

	if(strcmp(human.age.mensis, "february") == 0) {

		return 2;

	} 

	if(strcmp(human.age.mensis, "march") == 0) {

		return 3;

	} 

	if(strcmp(human.age.mensis, "april") == 0) {

		return 4;

	} 

	if(strcmp(human.age.mensis, "may") == 0) {

		return 5;

	} 

	if(strcmp(human.age.mensis, "june") == 0) {

		return 6;

	} 

	if(strcmp(human.age.mensis, "july") == 0) {

		return 7;

	} 

	if(strcmp(human.age.mensis, "august") == 0) {

		return 8;

	} 

	if(strcmp(human.age.mensis, "september") == 0) {

		return 9;

	} 

	if(strcmp(human.age.mensis, "october") == 0) {

		return 10;

	} 

	if(strcmp(human.age.mensis, "november") == 0) {

		return 11;

	} 
	
	else {

		return 12;
	}	

} 

/* This function uses the information the users entered at the beginning of the game to calculate the age difference and determine which player is older.
It begins the comparison with years, and then it converts the months into integers and compares those and then finally compares days if that is necessary.*/

int calcAge(struct User person[]) {

	int day;
	int month1;
	int month2;
	int finalMonth;
	int year;

	if(person[0].age.anni != person[1].age.anni) {

		//if user1 is older 
		if(person[0].age.anni < person[1].age.anni) { 

			return 1;
		}

		else { 

			return 0;
		}
	}

	else { 

		month1 = convertMonth(person[0]); 

		month2 = convertMonth(person[1]); 

		//if user1 is older
		if(month1 < month2) { 

			return 1; 
		}

		else if (month2 < month1) { 

			return 0;
		}

		else { 

			//if user1 is older
			if(person[0].age.dies < person[1].age.dies) { 

				return 1; 
			}

			else if (person[1].age.dies < person[0].age.dies) { 

				return 0;
			}

			//if the users have the same birth date
			else { 

				return 2;

			}
		}
	}
}

/*This function calculates the high score for the winner.
It scans through the entire array and adds points based on the scoring system, and adds a bonus for being the winner.
The function also checks to see what the ultime high score is and writes to a file if the user has topped the score.*/

int highScoreWinner(int countPlayWin, int &scoreWin) {

	FILE *fptr;
	int addEmpty = 0;
	int pieceBonus = 0;
	int readScore;

	for(int i = 0; i < 4; i ++) { 

		for(int j = 0; j < 4; j ++) {

			//calculate number of empty places in the game board
			if(board[i][j] == '\0') { 

				addEmpty++;
			}

			//add bonus for number of their pieces on the board
			if(board[i][j] == piece) { 

				pieceBonus++;
			}
		}
	}

	addEmpty = addEmpty * 20;

	pieceBonus = pieceBonus * 10;

	countPlayWin = countPlayWin * 8;

	scoreWin = addEmpty + pieceBonus + 1000 - countPlayWin; 

	fptr = fopen("/Users/samfaulkner/Desktop/Sam Da Coding Master/highscore.txt", "r");

	if(fptr == NULL) { 

		printf("Error. The file did not open.\n");
	}

	fscanf(fptr, "%d", &readScore);

	fclose(fptr);

	if(scoreWin > readScore) { 

		fptr = fopen("/Users/samfaulkner/Desktop/Sam Da Coding Master/highscore.txt", "w");

		if(fptr == NULL) { 

			printf("Error. The file did not open.\n");
		}

		fprintf(fptr, "%d", scoreWin);

		fclose(fptr);

		return 1; 
	}

	return 0; 
}

/* This function calculates the high score for the losing user. 
It scans through the array and adds points based on the scoring system.*/

int highScoreLoser(int countPlayLose, int &scoreLose) {

	int minusEmpty = 0;	
	int empathy = 0;

	for(int i = 0; i < 4; i ++) { 

		for(int j = 0; j < 4; j ++) {

			//calculate number of empty places in the game board
			if(board[i][j] == '\0') { 

				minusEmpty++;
			}

			//bonus points for having a certain number of your pieces on the board
			if(board[i][j] == piece) { 

				empathy++;
			}
		}
	}

	minusEmpty = minusEmpty * 10;

	empathy = empathy * 5;

	countPlayLose = countPlayLose * 4;

	scoreLose = empathy + minusEmpty + countPlayLose; 

	return 0; 
}

/* This function checks to see if there is a tie.
It scans through the whole array checking for blank spaces. 
This function is run after all the win functions to see if the game is over with no win.*/

bool isTie() {

	int tieCounter = 0;

	for(int i = 0; i < 5; i ++) { 

		for(int j = 0; j < 5; j ++) {		

			if(board[j][i] != '\0') {

				tieCounter++;
			}		
		} 
	}
	
	if(tieCounter == 25) {

		return true;
	}

	else {

		return false;
	}
}