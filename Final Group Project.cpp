#include <stdio.h>
#include <string.h>

char name[100];//nama pemain
int high_score = 0;
int score = 0;


struct Soal{//menampung pertanyaan
	char pertanyaan[1000];
	int tf; // true/false (1/2)
};

struct Leaderboard{
	char names[100];
	int highscores;
};

void intro(); //play/no
void mulai(); //start game
void rule(); // how to play - game rule
void printscore(); //score & high score
void finish();//play again?

void leaderboard_check();
void leaderboard_sort (Leaderboard board[]);
void leaderboard_rewrite(Leaderboard board[]);



void enter(){
	printf("\n");
}

void clean(){
	for(int a = 0; a < 60; a++){
		printf("\n");
	}
}

void delay(){
	for(int b = 0; b < 200000000; b++){
		;
	}
}

void longdelay(){
	for(int c = 0; c < 3000000000; c++){
		;
	}
}

int main(){
	intro();
					
	return 0;
}


void intro (){
	clean();
	int play;
	printf("Welcome to LinkLunk Game!!!\n");
	delay();
	printf("Before we start, please type your name: ");
	scanf("%[^\n]", name);
	delay();
	printf("Hello %s, to start the game please type '1', if you don't want to play type '0'.\n", name);
	scanf("%d", &play);
	
	
	while(play != 0 && play != 1 ){
		enter();
		printf("The number you type is not on the list.\n");
		printf("Please re-type the correct number.\n");
		scanf("%d", &play);
	}
	
		
	if(play == 1){
		clean();
		printf("Ok %s, let's start the game!!\n", name);
		enter();
		rule();
		mulai();
	}
	else {
		clean();
		printf("Thank you for playing with us, %s. See you next time.\n", name);
	}
}


void mulai(){
	Soal soal[25];
	FILE *fp = fopen("soal.txt", "r");
	int counter = 0;
	
	while(fscanf(fp, "%[^#]#%d\n", soal[counter].pertanyaan, &soal[counter].tf) != EOF){
		counter++;
	}
		
	
	printf("The high score you need to beat is %d\n", high_score);
	delay();
	enter();
			
	int nyawa = 3;
	score = 0;
	int printsoal = 0;
	
	while(nyawa != 0){ //gameplay
		delay();
		if(printsoal == counter){ //jika pertanyaan habis, break/game selesai
			printf("You've reached the end of this game.\n");
			break;
		}
		
		int jawabanbenar;
		int jawabansalah;
		int jawaban;
		
		printf("statement number %d\n", printsoal+1);
		printf("%s\n", soal[printsoal].pertanyaan);
		delay();
		enter();
		printf("1.True\n");
		printf("2.False\n");
		printf("Answer: ");
		scanf("%d", &jawaban);
				
		
		if(soal[printsoal].tf == 1){
			jawabanbenar = 1;
			jawabansalah = 2;
		}
		else{
			jawabanbenar = 2;
			jawabansalah = 1;
		}
				
		
		while (jawaban != 1 && jawaban != 2){ //jika jawaban yang di input bukan TRUE/FALSE (1/2)
			enter();
			printf("The answer you type is not on the list\n");
			printf("Please re-type your answer: ");
			scanf("%d", &jawaban);
		}
				
				
		if (jawaban == jawabanbenar){
			score += 1;
			printsoal += 1;
			printf("Your answer is correct.\n");
			longdelay();
			clean();
			
		}
		else if(jawaban == jawabansalah){
			score += 0;
			nyawa -= 1;
			printsoal += 1;
			printf("Your answer is wrong.\n");
			printf("You have %d lives now.\n", nyawa);
			longdelay();
			clean();
		}
						
	}
	
	
	printscore();
	enter();
	finish();
	
		
	fclose(fp);	
}


void rule(){
	delay();
	printf("How to Play:\n");
	enter();
	printf("You'll be given a statement, you need to check whether it's true or false.\n");
	printf("To answer, Type '1' for True and '2' for false.\n");
	printf("You have 3 lives to begin with, it will decrease if you type the wrong answer.\n");
	printf("If your live reaches 0, the game ends.\n");
	longdelay();
	enter();
	
}


void printscore(){
	printf("Your score is %d\n", score);
	if (score > high_score){
		high_score = score;
		printf("Congratulations you beat the previous high score!!\n");
		delay();
	}
	else {
		printf("Unfortunately you didn't beat the previous high score.\n");
		printf("previous high score: %d\n", high_score);
		delay();
	}
}


void finish(){
	int yes_no;
	printf("Do you want to play again?\n");
	printf("if yes please type '1', if no type '0'.\n");
	scanf ("%d", &yes_no);
	
	
	while (yes_no != 1 && yes_no != 0){
		printf("That number is not on the list\n");
		printf("Please re-type the correct number: ");
		scanf("%d", &yes_no);
	}	
	
	if(yes_no == 1){
		longdelay();
		clean();
		mulai();
	}
	else{
		clean();
		printf("Thank you for playing with us, %s. See you next time.\n", name);
		enter();
		leaderboard_check();
		longdelay();
		return;
	}
	
}



void leaderboard_check(){
	
	Leaderboard board[7];	
	
	FILE *file = fopen ("leaderboard", "r");
	int namescore = 0;
	
	while(fscanf(file, "%[^#]#%d\n", board[namescore].names, &board[namescore].highscores) != EOF){
		namescore += 1;
	}
	
	strcpy(board[namescore].names, name);//memasukan nama & high score ke array Leaderboard board
	board[namescore].highscores = high_score; 
	
	
	leaderboard_sort(board);//dari besar ke kecil
	
	
	//print leaderboard
	printf("Top 5 Leaderboard: \n");
	printf("------------------------\n");

	for (int i = 0; i<5 ; i++){
		printf("%s --------- %d\n", board[i].names, board[i].highscores);
	}
	
	fclose(file);
	
	leaderboard_rewrite(board);//menulis ulang di file leaderboard
	
	
}


void leaderboard_sort (Leaderboard board[]){
	
	Leaderboard temp;
	
	for(int m = 0; m < 5; m++){
		for(int n = 0; n < 5 - m; n++){
			if (board[n].highscores < board[n+1].highscores){
				temp = board[n];
				board[n] = board[n+1];
				board[n+1] = temp;
			}
		}
	}
	
}


void leaderboard_rewrite(Leaderboard board[]){
	FILE *fpp = fopen("leaderboard", "w");
	
	for(int i = 0; i<5; i++){
		fprintf(fpp, "%s#%d\n", board[i].names, board[i].highscores);
	}
	
	fclose(fpp);
}









