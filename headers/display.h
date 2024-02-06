#include "struct.h"

void printCharactere(char charactere, int number);
void printSingleOption(const char *content, int firstSpacing, int secondSpacing, int last);
void printOptions();
void printToConsole();
void printDictionary(tree *dico, char path[], int wordLen);
void printDifferentWords(tree *dico);
void printTotalWords(tree *dico);
void printOccurrences(tree *dico);
tree *printRandomWord(tree *dico);
void printEmptiedTree(tree *dico);
tree *fillTree(tree *dico);
void printHelp();