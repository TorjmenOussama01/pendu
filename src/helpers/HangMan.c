#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../../headers/tree.h"

char test[] = "test";

// initialization of the game : 
// Function to initialize the Hangman game
char *initializeHangman() {
    // Initialize the Hangman game state
    int lives = 6;
    char guessed_letters[26]; // Assuming only lowercase letters will be guessed
    memset(guessed_letters, '\0', sizeof(guessed_letters));

    // Select a random word from the dictionary
    //char *word = chooseWord("dictionary.txt"); // Adjust the filename as needed
        char *word ="test";
    // Print initial game state (optional)
    printf("Hangman Game Initialized.\n");
    printf("Word to guess: %s\n", word);
    printf("Number of lives: %d\n", lives);
    printf("\n");

    return word;
}




// functionality to take the user input , of guessing the letter
char takeUserInput() {
    char letter;
    printf("Enter a letter guess (a-z): ");
    scanf(" %c", &letter);

    // Validate the input to ensure it's a valid lowercase letter
    while ((letter < 'a' || letter > 'z')) {
        printf("Invalid input! Please enter a lowercase letter (a-z): ");
        scanf(" %c", &letter);
    }

    return letter;
}


bool checkLetterInWord(tree *root, char letter) {
    // Base case: If the root is NULL, the tree is empty
    if (root == NULL) {
        return false;
    }

    // If the current node's letter matches the guessed letter
    if (root->letter == letter) {
        return true;
    }

    // Recursively check in the left and right subtrees
    bool inLeftSubtree = checkLetterInWord(root->left, letter);
    bool inRightSubtree = checkLetterInWord(root->right, letter);

    // Return true if the letter is found in either subtree
    return inLeftSubtree || inRightSubtree;
}


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


// Helper function to traverse the binary tree and update guessed letters
void traverseInOrder(tree *root, char guessed_letters[], bool *letterGuessedCorrectly, char letter) {
    if (root != NULL) {
        traverseInOrder(root->left, guessed_letters, letterGuessedCorrectly, letter);

        // Check if the current node's letter matches the guessed letter
        if (root->letter == letter) {
            // Update the guessed letters array to reveal the occurrence of the guessed letter
            guessed_letters[letter - 'a'] = letter;
            *letterGuessedCorrectly = true;
        }

        traverseInOrder(root->right, guessed_letters, letterGuessedCorrectly, letter);
    }
}


void updateHangmanState(tree *root, char letter, char guessed_letters[], int *lives) {
    bool letterGuessedCorrectly = false;

    // Iterate through the word stored in the binary tree
    traverseInOrder(root, guessed_letters, &letterGuessedCorrectly, letter);

    if (!letterGuessedCorrectly) {
        // Decrement the number of lives if the letter is incorrect
        (*lives)--;
    }
}




bool checkGameOverCondition(tree *root, char guessed_letters[], int lives) {
    // Check if all the letters in the word have been guessed
    if (is_word_guessed_tree(root, guessed_letters)) {
        printf("Congratulations! You guessed the word!\n");
        return true;
    }
    
    // Check if the player runs out of lives
    if (lives == 0) {
        printf("Game over! You ran out of lives. The word was: ");
        printWord(root);
        printf("\n");
        return true;
    }
    
    // Game is not over yet
    return false;
}


void playHangMan(tree *root, int niveau) {
    // Initialize the game.
    int lives = 6;
    char guessed_letters[26]; // Assuming only lowercase letters will be guessed
    memset(guessed_letters, '\0', sizeof(guessed_letters));

    // Play the game.
    while (lives > 0 && !is_word_guessed_tree(root, guessed_letters)) {
        // Display current Hangman state
        printf("Hangman State:\n");
        draw_hangman(lives);
        printf("\n");

        // Display guessed letters
        printf("Guessed Letters: ");
        for (char c = 'a'; c <= 'z'; c++) {
            if (guessed_letters[c - 'a'] != '\0') {
                printf("%c ", c);
            }
        }
        printf("\n\n");

        // Get a letter from the user.
        char letter = takeUserInput();

        // Check if the letter is in the word.
        if (checkLetterInWord(root, letter)) {
            // Update the Hangman state based on the correctness of the guessed letter.
            updateHangmanState(&root, letter, guessed_letters, &lives);

            // Check if the word is guessed.
            if (is_word_guessed_tree(root, guessed_letters)) {
                printf("Congratulations! You guessed the word!\n");
                return;
            }
        } else {
            // Decrement the number of lives.
            lives--;

            printf("Incorrect guess! You have %d lives remaining.\n", lives);
        }
    }

    if (lives == 0) {
        printf("You lose! The word was: ");
        printWord(root);
        printf("\n");
    }
}

/*
Initialize Hangman Game:

initializeHangman: Function to initialize the Hangman game, including setting up the initial state of the Hangman (e.g., number of lives, empty guessed letters array) and selecting a random word from the dictionary.
Display Hangman State:

displayHangmanState: Function to display the current state of the Hangman, including the Hangman figure representing the number of lives remaining.
Take User Input:

takeUserInput: Function to prompt the user to input a letter guess and validate the input (e.g., check if it's a valid lowercase letter).
Check Letter in Word:

checkLetterInWord: Function to check if the guessed letter is present in the selected word.
Update Hangman State:

updateHangmanState: Function to update the Hangman state based on the correctness of the guessed letter.
If the letter is correct, update the guessed letters array and remove the letter from the binary tree representing the word.
If the letter is incorrect, decrement the number of lives remaining.
Check Game Over Condition:

isGameOver: Function to check if the game is over (either the word is guessed completely or the player runs out of lives).
Main Game Loop:

mainGameLoop: Main loop to repeatedly take user input, check the letter in the word, update the Hangman state, and check the game over condition until the game ends.
Display Game Outcome:

displayGameOutcome: Function to display the outcome of the game (e.g., if the player wins by guessing the word or loses by running out of lives).
Cleanup Resources:

cleanupResources: Function to clean up any resources used during the game (e.g., free memory allocated for the binary tree).
*/