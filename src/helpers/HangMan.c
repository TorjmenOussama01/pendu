#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <tree.h>

// tree + word 
// decomposing that word into  keys nodes in the tree 

// taking input from the user, letter , 
//  if the letter, is in the word, then, showcase the letter in all the positions , and delete that letter , from the world 
// else , draw the part of the hangman 

char test[] = "test";



bool is_word_guessed(char *word, char guessed_letters[]) {
    // Check if all the letters in the word have been guessed.
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] != ' ' && guessed_letters[word[i] - 'a'] == '\0') {
            return false;
        }
    }
    return true;
}

bool is_letter_in_word(char *word, char letter) {
    // Check if the letter is in the word.
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] == letter) {
            return true;
        }
    }
    return false;
}

void draw_hangman(int lives) {
    // Draw the hangman.
    switch (lives) {
        case 6:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            break;
        case 5:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            break;
        case 4:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf("  |   |\n");
            printf("      |\n");
            printf("      |\n");
            break;
        case 3:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|   |\n");
            printf("      |\n");
            printf("      |\n");
            break;
        case 2:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf("      |\n");
            printf("      |\n");
            break;
        case 1:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf(" /    |\n");
            printf("      |\n");
            break;
        case 0:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf(" / \\  |\n");
            printf("      |\n");
            break;
    }
}

void playHangMan(char word, int niveau) {
    // Initialize the game.
    int lives = 6;
    char guessed_letters[26]; // Assuming only lowercase letters will be guessed
    memset(guessed_letters, '\0', sizeof(guessed_letters));

    // Play the game.
    while (lives > 0 && !is_word_guessed(word, guessed_letters)) {
        // Get a letter from the user.
        char letter;
        printf("Enter a letter: ");
        scanf(" %c", &letter);

        // Check if the letter is in the word.
        if (is_letter_in_word(word, letter)) {
            // Add the letter to the list of guessed letters.
            guessed_letters[letter - 'a'] = letter;

            // Check if the word is guessed.
            if (is_word_guessed(word, guessed_letters)) {
                printf("You win!\n");
                return;
            }
        } else {
            // Decrement the number of lives.
            lives--;

            // Draw the hangman.
            draw_hangman(lives);
        }
    }

    if (lives == 0) {
        printf("You lose! The word was: %s\n", word);
    }
  }


/*

functionality protoype 
void playGame(struct TreeNode* root, char *word);
char getInput();
void deleteLetterFromTree(struct TreeNode** root, char letter);

// Function to play the game
void playGame(struct TreeNode* root, char *word) {
    // Initialize the game state
    int lives = 6;
    char guessed_letters[26]; // Assuming only lowercase letters will be guessed
    memset(guessed_letters, '\0', sizeof(guessed_letters));

    // Play the game
    while (lives > 0) {
        // Get a letter from the user
        char letter = getInput();

        // Check if the letter is in the word
        if (strchr(word, letter) != NULL) {
            // Letter is in the word, delete it from the binary tree
            deleteLetterFromTree(&root, letter);
            
            // Print the updated binary tree
            // Your code to print the binary tree here

            // Add the letter to the list of guessed letters
            guessed_letters[letter - 'a'] = letter;

            // Check if the word is guessed
            if (strspn(word, guessed_letters) == strlen(word)) {
                printf("You win!\n");
                return;
            }
        } else {
            // Letter is not in the word, decrement the number of lives
            lives--;

            // Draw the hangman
            // Your code to draw the hangman here
        }
    }

    // Ran out of lives
    printf("You lose! The word was: %s\n", word);
}

// Function to get input from the user
char getInput() {
    char input;
    printf("Enter a letter: ");
    scanf(" %c", &input);
    return input;
}

// Function to delete a letter from the binary tree
void deleteLetterFromTree(struct TreeNode** root, char letter) {
    // Your code to delete the letter from the binary tree here
}



*/