#include "struct.h"
#include <stdbool.h>

bool is_word_guessed(char *word ,char guessed_letters[] );
bool is_letter_in_word(char *word ,char letter);
void draw_hangman(int lives);
char *initializeHangman();
char takeUserInput();
bool checkLetterInWord(tree *root, char letter);
void updateHangmanState(tree *root, char letter, char guessed_letters[], int *lives, const char *word);
bool checkGameOverCondition(tree *root, char guessed_letters[], int lives);
void playHangman();
void printWord(tree *root);
bool is_word_guessed_tree(tree *root, char guessed_letters[]); 
//void traverseInOrderWithinWord(tree *root, const char *word, char guessed_letters[], bool *letterGuessedCorrectly, char letter);