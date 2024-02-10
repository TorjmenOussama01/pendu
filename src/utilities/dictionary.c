#include <stdio.h>
#include <stdlib.h>
#include "../../headers/struct.h"
#include "../../headers/display.h"

// ? START HELPERS

// * Créer un noeud intermédiaire
tree *append(char letter)
{
    tree *node = (tree *)malloc(sizeof(tree));

    node->letter = letter;
    node->left = NULL;
    node->right = NULL;
    node->occurrences = 0;

    return node;
}

// * Créer un noeud pour marquer la fin d'un mot
tree *markEndOfWord()
{
    tree *node = (tree *)malloc(sizeof(tree));

    node->letter = '\0';
    node->left = NULL;
    node->right = NULL;
    node->occurrences = 1;

    return node;
}

// * Afficher le mot à partir d'un tableau de caractères pour un indice donné
void printArray(char letters[], int len)
{
    int index;

    printCharactere(' ', 5);

    for (index = 0; index < len; index++)
        printf("%c", letters[index]);

    printf("\n");
}

// ? END HELPERS

// * Afficher tous les mots d'un arbre donné
void dicoAfficher(tree *node, char word[], int wordLen)
{
    if (node == NULL)
        return;

    // * Si le noeud a comme lettre \0, on a arrivé à la fin du mot
    // * et on doit l'afficher
    if (node->letter == '\0')
        printArray(word, wordLen);

    // * Sinon, on ajoute la lettre dans un tableau et on incémente son indice
    if (node->letter != '\0')
    {
        word[wordLen] = node->letter;
        wordLen++;
    }

    // * On passe au noeud droite suivant avec le nouveau tableau
    dicoAfficher(node->left, word, wordLen);

    // * On passe au noeud gauche mais on décremente l'indice pour
    // * que le nouveau mot prenne place (on écrase l'anciennes valeurs)
    if (node->letter != '\0')
        wordLen--;

    dicoAfficher(node->right, word, wordLen);
}

// * On insère un mot dans un arbre donné, si le mot existe on incremente le nombre d'occurence
// * du mot
tree *dicoInsererMot(char word[50], tree *root, int wordIndex)
{
    tree *temp;

    // * Si l'arbre est intialement vide, on va insérer le mot
    if (root == NULL)
    {
        // * Si le mot est n'est pas vide, on procced
        if (word[wordIndex] != '\0')
        {
            // * La creation du racine
            root = append(word[wordIndex]);
            temp = root;
            wordIndex++;

            // * L'ajout du mot dans l'arbre on utilisation la fonction 'append'
            while (word[wordIndex] != '\0')
            {
                temp->left = append(word[wordIndex]);
                temp = temp->left;
                wordIndex++;
            }

            // * On marque la fin du mot par un noeud qui contient le nombre d'occurence 1
            temp->left = markEndOfWord();

            return root;
        }
    }
    else
    {
        // * Sinon l'arbre n'est pas vide
        // * On test si la lettre existe
        if (root->letter == word[wordIndex])
        {
            // * Si la lettre existe déja on test le reste de mot
            // * pour savoir si on va incrementer le nombre
            // * d'occurence.
            if (root->left == NULL && root->letter == '\0')
            {
                root->occurrences++;
            }
            else
            {
                root->left = dicoInsererMot(word, root->left, wordIndex + 1);
            }

            return root;
        }
        // * La lettre n'existe pas ce qui indique que cette une nouveau mot a inserer
        // * on passe alors au sous arbre droite

        root->right = dicoInsererMot(word, root->right, wordIndex);
        return root;
    }
}

// * Afficher le nombre d'occurence d'un mot donné
int dicoNbOcc(char *word, int wordIndex, tree *root)
{
    // * Si la premiere lettre du mot donné est égale a celle de la racine
    // * on passe au sous arbre gauche
    if (word[wordIndex] == root->letter)
    {
        // * Si le caractere est \0, le mot est vérifier et on
        // * retourne le nombre d'occurence.
        if (root->left == NULL && root->letter == '\0')
            return root->occurrences;

        // * Sinon on passe au noeud suivant pour vérfier le reste du mot
        return dicoNbOcc(word, wordIndex + 1, root->left);
    }

    if (root->right == NULL)
        return 0;

    // * Si la premiere lettre du mot donné est differente de celle
    // * de la racine on vérifie les sous arbres droites.
    return dicoNbOcc(word, wordIndex, root->right);
}

// * Afficher le nombre des mots différents
int dicoNbMotsDifferents(tree *root)
{
    if (root != NULL)
    {
        // * Si le noeud marque la fin d'un mot, on retourne
        // * 1  et on passe aux sous arbre gauche et droite
        if (root->letter == '\0')
            return 1 + (dicoNbMotsDifferents(root->left) + dicoNbMotsDifferents(root->right));

        // * Sinon on passe aux sous arbres gauche et droite
        return dicoNbMotsDifferents(root->left) + dicoNbMotsDifferents(root->right);
    }

    return 0;
}

// * Afficher le nombre total des mots
int dicoNbMotsTotal(tree *root)
{
    if (root != NULL)
    {
        // * Si le noeud marque la fin d'un mot, on retourne
        // * le nombre d'occurence de ce mot, et on passe
        // * aux sous arbre gauche et droite
        if (root->letter == '\0')
            return root->occurrences + (dicoNbMotsTotal(root->left) + dicoNbMotsTotal(root->right));

        // * Sinon on passe aux sous arbres gauche et droite
        return dicoNbMotsTotal(root->left) + dicoNbMotsTotal(root->right);
    }

    return 0;
}
int nombreAleatoire(int nombreMax)
{
    srand(time(NULL));
    return (rand() % nombreMax);
}

char* choisirMot(char *filename, int level) {
    FILE *dico = NULL;
    char mot[100];
    int min_length, max_length;
    int line_count = 0, chosen_line;
    dico = fopen(filename, "r");
    
    if (dico == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        return NULL;
    }
    
    switch(level) {
        case 1:
            min_length = 2;
            max_length = 6;
            break;
        case 2:
            min_length = 6;
            max_length = 8;
            break;
        case 3:
            min_length = 9;
            max_length = 100; // Assuming maximum word length is 100
            break;
        default:
            printf("Niveau non valide\n");
            fclose(dico);
            return NULL;
    }
    
    srand(time(NULL)); // Seed random number generator
    
    while (fgets(mot, sizeof(mot), dico) != NULL) {
        line_count++;
        if (strlen(mot) >= min_length && strlen(mot) <= max_length) {
            if (rand() % line_count == 0) {
                chosen_line = line_count;
            }
        }
    }
    
    rewind(dico);
    line_count = 0;
    
    while (fgets(mot, sizeof(mot), dico) != NULL) {
        line_count++;
        if (line_count == chosen_line) {
            mot[strlen(mot) - 1] = '\0'; // Remove newline character
            fclose(dico);
            return strdup(mot); // Return dynamically allocated copy of the word
        }
    }
    
    fclose(dico);
    return 1;
}
// Function to delete a word from the binary tree
tree* deleteWord(tree* root, char word[], int wordIndex) {
    if (root == NULL) {
        // Word not found, return NULL
        return NULL;
    }

    // If the current node's letter matches the current character of the word
    if (root->letter == word[wordIndex]) {
        // If it's the end of the word
        if (word[wordIndex + 1] == '\0') {
            // Mark the end of word node for deletion
            root->left = NULL;
        } else {
            // Recursively delete next character in the word
            root->left = deleteWord(root->left, word, wordIndex + 1);
        }
    }

    // Recursively delete from left and right subtrees
    root->left = deleteWord(root->left, word, wordIndex);
    root->right = deleteWord(root->right, word, wordIndex);

    // Check if current node has no children and it's not the end of a word
    if (root->left == NULL && root->right == NULL && root->letter != '\0') {
        // Free the memory and return NULL (deleting this node)
        free(root);
        return NULL;
    }

    return root;
}


void removeWordFromFile(const char *wordToRemove) {
    char filename[100];
    printf("Enter the name of the file: ");
    if (scanf("%99s", filename) != 1) {
        printf("Error reading filename.\n");
        return;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    char word[100]; // Adjust the size as per your need
    int wordFound = 0;
    while (fscanf(file, "%99s", word) != EOF) {
        printf("Word read: %s\n", word); // Print the word read
        if (strcmp(word, wordToRemove) != 0) {
            fprintf(tempFile, "%s\n", word); // Write word to temp file followed by newline
        } else {
            wordFound = 1;
        }
    }

    fclose(file); // Close the input file
    fclose(tempFile); // Close the temporary file

    // Remove the original file
    if (remove(filename) != 0) {
        perror("Error deleting file");
        return;
    }

    // Rename the temporary file to the original filename
    if (rename("temp.txt", filename) != 0) {
        perror("Error renaming file");
        return;
    }

    // Notify if the word was not found in the file
    if (!wordFound) {
        printf("Word '%s' not found in file.\n", wordToRemove);
    }
}



void removeWordFromTreeAndFile(tree **root) {
    int choice;
    printf("Enter 1 to delete from binary tree, 2 to delete from file, 3 to delete from both: ");
    scanf("%d", &choice);

    char wordToDelete[15]; // Assuming MAX_WORD_LENGTH is defined somewhere
    printf("Enter the word you want to delete: ");
    scanf("%s", wordToDelete);

    switch (choice) {
        case 1:
            // Delete from binary tree only
            *root = deleteWord(*root, wordToDelete, 0);
            printf("Word '%s' deleted from binary tree.\n", wordToDelete);
            break;
        case 2:
            // Delete from file only
            removeWordFromFile(wordToDelete);
            break;
        case 3:
            // Delete from both binary tree and file
            *root = deleteWord(*root, wordToDelete, 0);
            removeWordFromFile(wordToDelete);
            printf("Word '%s' deleted from binary tree and file.\n", wordToDelete);
            break;
        default:
            printf("Invalid choice\n");
    }
}


// Function to choose a random word from the tree
void chooseRandomWord(tree *node) {
    if (node == NULL)
        return;

    srand(time(NULL));
    char word[100];
    int wordLen = 0;
    
    while (node != NULL && node->letter != '\0') {
        int random = rand() % 2;
        if (random == 0 && node->left != NULL && node->letter != '\0') {
            word[wordLen] = node->letter;
            wordLen++;
            node = node->left;
        } else if(random != 0 && node->right != NULL && node->letter != '\0'){
            node = node->right;
        }
    }

    // Print the chosen random word
    if (wordLen > 0) {
        word[wordLen] = '\0';
        printf("Random Word: %s\n", word);
    } else {
        printf("No word found.\n");
    }
}



tree *createTreeByLevel(tree *dico,int level)
{
    char filename[100];

    do
    {
        printCharactere(' ', 4);
        printf("Entrer nom fichier => ");
        scanf("%s", filename);
    } while (strlen(filename) < 0 || strlen(filename) > 100);

    FILE *file = fopen(filename, "r");

    system("clear");
    printHeader("Insertion Options", 25);
    printCharactere(' ', 18);

    if (!file)
    {
        printf("\033[1;31mVeuillez vérifier le nom de fichier\033[0m");
        printFooter();

        return dico;
    }

    char line[500];

    while (fgets(line, sizeof(line), file))
    {
        int wordLen = strlen(line);
        if ((level == 1 && wordLen >= 2 && wordLen <= 5) ||
            (level == 2 && wordLen >= 6 && wordLen <= 8) ||
            (level == 3 && (wordLen > 8))) {
        line[strlen(line) - 1] = '\0';
        dico = dicoInsererMot(line, dico, 0);                

        }
    }

    fclose(file);

    printf("\033[0;32mMots ajouté avec success\033[0m");
    printFooter();
            char path[100];
            printDictionary(dico, path, 0);  
    
    return dico;
}




///* commented functionality above 

// Function to choose a random word from the tree
/*void chooseRandomWord(tree *node)
    /*{
    char word[100];
    int wordLen=0;
    if (node == NULL)
        return;
    // * Sinon, on ajoute la lettre dans un tableau et on incémente son indice
    while (node->letter != '\0')
    {
        int random= rand() % 2;
        if (node->letter != '\0' && random == 0)
        {
        word[wordLen] = node->letter;
        wordLen++;
        node=node->left;
        }
        else if (node->letter != '\0' && random != 0)
        {
        wordLen--;
        node=node->right;
        }
    }

    printArray(word, wordLen);
    return word;
}*/


// old commentede functionalit of create tree by level 
//* tree *createTreeByLevel(tree *dico,int level)
  /*  {
    char filename[100];

    do
    {
        printCharactere(' ', 4);
        printf("Entrer nom fichier => ");
        scanf("%s", filename);
    } while (strlen(filename) < 0 || strlen(filename) > 100);

    FILE *file = fopen(filename, "r");

    system("clear");
    printHeader("Insertion Options", 25);
    printCharactere(' ', 18);

    if (!file)
    {
        printf("\033[1;31mVeuillez vérifier le nom de fichier\033[0m");
        printFooter();

        return dico;
    }

    char line[500];

    while (fgets(line, sizeof(line), file))
    {
        int wordLen = strlen(line);
        if ((level == 1 && wordLen >= 2 && wordLen <= 5) ||
            (level == 2 && wordLen >= 6 && wordLen <= 8) ||
            (level == 3 && (wordLen > 8))) {
        line[strlen(line) - 1] = '\0';
        dico = dicoInsererMot(line, dico, 0);                

        }
    }

    fclose(file);

    printf("\033[0;32mMots ajouté avec success\033[0m");
    printFooter();
            char path[100];
            printDictionary(dico, path, 0);  
    /*
    // Print the random word
    if (randomWord != NULL)
        printf("Random Word: %s\n", randomWord);
    else
        printf("The tree is empty.\n");

    // Free memory allocated for the random word
    free(randomWord);  

    return dico;
}*/

