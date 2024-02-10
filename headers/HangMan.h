#include "struct.h"
#include <stdbool.h>

void playHangMan(char word,int niveau);
bool is_word_guessed(char *word ,char guessed_letters[] );
bool is_letter_in_word(char *word ,char letter);
void draw_hangman(int lives);
char *initializeHangman();
char takeUserInput();
bool checkLetterInWord(tree *root, char letter);
void updateHangmanState(tree **root, char letter, char guessed_letters[], int *lives);
bool checkGameOverCondition(tree *root, char guessed_letters[], int lives);
void playHangMan(tree *root, int niveau);