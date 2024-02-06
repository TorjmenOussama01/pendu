#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

  void playHangMan(char word,int niveau) {
    // Initialize the game.

    char lives = 6;
    char guessed_letters[] = (char*)malloc(sizeof(char) * 27);
    memset(guessed_letters, '\0', 27);

    // Play the game.

    while (lives > 0 && !is_word_guessed(word,guessed_letters)) {
      // Get a letter from the user.

      char letter;

      printf("Enter a letter: ");
      scanf(" %c", &letter);

      // Check if the letter is in the word.

      if (is_letter_in_word(word ,letter)) {
        // Add the letter to the list of guessed letters.

        guessed_letters[letter - 'a'] = letter;

        // Check if the word is guessed.

        if (is_word_guessed(word,guessed_letters)) {
          printf("You win!\n");
          return;
        }
      } else {
        // Decrement the number of lives.

        lives--;

        // Draw the hangman.

        draw_hangman();
      }
    }

    if (lives == 0) {
      printf("You lose!\n");
    }
  }


  bool is_word_guessed(char *word ,char guessed_letters[] ) {
    // Check if all the letters in the word have been guessed.

    for (int i = 0; word[i] != '\0'; i++) {
      if (guessed_letters[word[i] - 'a'] == '\0') {
        return false;
      }
    }

    return true;
  }

  bool is_letter_in_word(char *word ,char letter) {
    // Check if the letter is in the word.

    for (int i = 0; word[i] != '\0'; i++) {
      if (word[i] == letter) {
        return true;
      }
    }

    return false;
  }

  void draw_hangman(lives) {
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