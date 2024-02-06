#include "struct.h"

void playHangMan(char word,int niveau);
bool is_word_guessed(char *word ,char guessed_letters[] );
bool is_letter_in_word(char *word ,char letter);
void draw_hangman(lives);