//Author: Gareth Frehner
//Date: 05/05/2025
//Purpose: "we have wordle at home"

#include <stdio.h>
#include <stdbool.h>

#define FILENAME "word.txt"
#define NUM_GUESSES 6
#define WORD_LENGTH 5
#define BUFFER 30

int strLength(char* string);
bool isAlphabet(char* string);
bool readFile(char* filename, char* word);
void getGuess(char* guess, int index);
bool isValidGuess(char* guess);
bool stringEqual(char* guess, char* word);
bool checkGuess(char* guess, char* word, char* result);



int main(){
	
	char word[WORD_LENGTH + 1], guess[BUFFER], guesses[NUM_GUESSES * 2][WORD_LENGTH + 1], result[WORD_LENGTH + 1];	
	if(readFile(FILENAME, word) == 0){return 0;}
	
	for(int index = 0; index<NUM_GUESSES; index++){
		getGuess(guess, index);
		printf("================================\n");
		
		if(checkGuess(guess, word, result)){
			printf("%s\n", guess);
			printf("You won in %d guesses!\n", index + 1);
			return 0;
		}
		
		for(int i = 0; i < WORD_LENGTH; i++){
			guesses[index * 2][i] = guess[i];
			guesses[index * 2 + 1][i] = result[i];
		}
		
		for(int i = 0; i <= index * 2 + 1; i++){
			printf("%s\n", guesses[i]);
		}
	}
	
	printf("You lose :(\n");
	
	return 0;
}

int strLength(char* string){
	int length = 0;
	while(string[length] != '\0'){length++;}
	return length;
}

bool isAlphabet(char* string){
	int i = 0;
	while(string[i] != '\0'){
		if(string[i] >= 'A' && string[i] <= 'Z'){string[i] += 32;}
		else if(string[i] < 'a' || string[i] > 'z'){return false;}
		i++;
	}
	return true;
}

bool readFile(char* filename, char* word){
	FILE* fptr= fopen(filename, "r");
	if(fptr == NULL){
		printf("Failed to open file.\n");
		return 0;
	}
	fscanf(fptr, "%s", word);
	return 1;
}

void getGuess(char* guess, int index){
	printf("GUESS %d! Enter your guess: ", index + 1);
	scanf("%s", guess);
	while(!isValidGuess(guess)){
		printf("Please try again: ");
		scanf("%s", guess);
	}
}

bool isValidGuess(char* guess){
	if(strLength(guess) != WORD_LENGTH && !isAlphabet(guess)){
		printf("Your guess must be 5 letters long. Your guess must contain only letters.\n");
		return false;
	}
	else if(strLength(guess) != WORD_LENGTH){
		printf("Your guess must be 5 letters long.\n");
		return false;
	}
	else if(!isAlphabet(guess)){
		printf("Your guess must contain only letters.\n");
		return false;
	}
	else{return true;}
}

bool stringEqual(char* guess, char* word){
	bool result = true;
	for(int i = 0; i < WORD_LENGTH; i++){
		if(guess[i] == word[i]){guess[i] -= 32;}
		else{result = false;}
	}
	return result;
}

bool checkGuess(char* guess, char* word, char* result){
	if(stringEqual(guess, word)){return true;}
	for(int i = 0; i < WORD_LENGTH; i++){
		for(int j = 0; j < WORD_LENGTH; j++){
			if(guess[i] == word[j]){
				result[i] = '^';
				break;
				}
			else{result[i] = ' ';}
		}
	}
	return false;
}
