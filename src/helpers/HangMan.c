#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../../headers/tree.h"
#include "../../headers/dictionary.h"

const MAX_WORD_LENGTH = 10 ; 
const MAX_LIVES = 6 ;
char test[] = "test";

// initialization of the game : 
// Function to initialize the Hangman game
char* initializeHangman(tree **treeRoot) {
    // Prompt the user to choose the level
    int level;
    do {
        printf("Choose the level (1, 2, or 3): ");
        scanf("%d", &level);
    } while (level < 1 || level > 3);

    // Construct the binary tree based on the chosen level
    *treeRoot = createTreeByLevel(NULL, level);

    // Select a random word from the constructed tree
    char *randomWord = chooseRandomWord(*treeRoot);
    if (randomWord == NULL) {
        printf("Error: Failed to choose a random word.\n");
        return NULL;
    }

    // Print initial game state
    printf("Hangman Game Initialized.\n");
    printf("Word to guess: %s\n", randomWord);
    printf("Number of lives: %d\n", MAX_LIVES);
    printf("\n");

    return randomWord;
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


bool is_word_guessed_tree(tree *root, char guessed_letters[]) {
    // Base case: If the root is NULL, the tree is empty
    if (root == NULL) {
        return true; // An empty tree is considered guessed
    }

    // If the current node's letter is not guessed, return false
    if (root->letter != ' ' && guessed_letters[root->letter - 'a'] == '\0') {
        return false;
    }

    // Recursively check in the left and right subtrees
    return is_word_guessed_tree(root->left, guessed_letters) &&
           is_word_guessed_tree(root->right, guessed_letters);
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


void updateHangmanState(tree *root, char letter, char guessed_letters[], int *lives, const char *word) {
    // Mark the guessed letter as already guessed
    guessed_letters[letter - 'a'] = letter;

    // Display all occurrences of the guessed letter in the word
    printf("Occurrences of '%c' in the word: ", letter);
    bool letterGuessedCorrectly = false;
    traverseInOrder(root, guessed_letters, &letterGuessedCorrectly, letter);
    printf("\n");

    // Display the word with guessed letters and asterisks for unguessed letters
    printf("Word: ");
    for (int i = 0; word[i] != '\0'; i++) {
        if (guessed_letters[word[i] - 'a'] != '\0') {
            printf("%c", word[i]); // Guessed letter
        } else {
            printf("*"); // Unguessed letter
        }
    }
    printf("\n");

    // Check if the guessed letter is in the word
    if (!letterGuessedCorrectly) {
        // Decrement lives if the guessed letter is incorrect
        (*lives)--;
        printf("Incorrect guess! You have %d lives remaining.\n", *lives);
    } else {
        printf("Correct guess!\n");
    }
}


void displayOccurrences(tree *root, char letter) {
    if (root == NULL) {
        return;
    }

    displayOccurrences(root->left, letter);

    if (root->letter == letter) {
        printf("%c ", root->letter);
    }

    displayOccurrences(root->right, letter);
}



bool checkGameOverCondition(tree *root, char guessed_letters[], int lives, const char *word) {
    int guessedWordLength = strlen(word);

    // Check if all the different guessed letters are in the word
    for (int i = 0; word[i] != '\0'; i++) {
        if (guessed_letters[word[i] - 'a'] != '\0') {
            guessedWordLength--;
        }
    }

    // If the length of the guessed word is zero, all letters are found
    if (guessedWordLength == 0) {
        printf("Congratulations! You guessed the word!\n");
        return true;
    }

    // Check if the player runs out of lives
    if (lives == 0) {
        printf("Game over! You ran out of lives. The word was: %s\n", word);
        return true;
    }

    // Game is not over yet
    return false;
}



void printWord(tree *root) {
    if (root == NULL) {
        return;
    }

    // Traverse the binary tree in-order to print the word
    printWord(root->left);
    printf("%c", root->letter);
    printWord(root->right);
}



void playHangman() {
    int playAgain;
    do {
        // Initialize the Hangman game state
        tree *root;
        char *word = initializeHangman(&root);
        if (word == NULL) {
            printf("Error: Failed to initialize Hangman game.\n");
            return;
        }

        int lives = MAX_LIVES;
        char guessed_letters[26];
        memset(guessed_letters, '\0', sizeof(guessed_letters));

        // Convert the word to lowercase for consistency
        char *lowercaseWord = strdup(word);
        for (int i = 0; lowercaseWord[i] != '\0'; i++) {
            lowercaseWord[i] = tolower(lowercaseWord[i]);
        }
        printf("Randomly chosen word: %s\n", lowercaseWord);

        // Main game loop
        while (lives > 0) {
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

            // Get user input for a letter guess
            char letter = takeUserInput();

            // Update Hangman state based on the correctness of the guessed letter
            updateHangmanState(root, letter, guessed_letters, &lives, lowercaseWord);

            // Check if the game is over (word guessed completely)
            if (checkGameOverCondition(root, guessed_letters, lives, lowercaseWord)) {
                break;
            }
        }

        // Free memory allocated for the tree and word
        arbreSuppr(root);
        free(word);
        free(lowercaseWord);

        // Ask if the player wants to play again
        printf("Do you want to play again? (1 for yes, 0 for no): ");
        scanf("%d", &playAgain);
        while (getchar() != '\n'); // Clear input buffer

    } while (playAgain == 1);
}
