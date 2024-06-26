#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "headers/struct.h"
#include "headers/display.h"
#include "headers/tree.h"
#include "headers/dictionary.h"

// * Pointeur Global, utiliser pour la manipulation de l'arbre
tree *dico;
char filename[100];
void handleInput()
{
    // * Ne fonctionnera que sur des systèmes Linux, en cas de Windows
    // * veuillez mettre à jour la ligne comme suit system("cls") dans toutes les occurrences.
    system("clear");

    while (1)
    {
        int option;
        int counts = 0;

        printToConsole();

        printf("\n");
        do
        {
            printCharactere(' ', 4);
            if (counts > 0)
            {
                printf("\033[1;31mOption invalide.\033[0m\n");
                printCharactere(' ', 4);
            }

            printf("Enter Option => ");
            scanf("%d", &option);
            counts++;
        } while (option < 0 || option > 12);

        switch (option)
        {
        case 1:
            dico = fillTree(dico);
            break;
        case 2:
            char path[100];
            printDictionary(dico, path, 0);
            break;
        case 3:
            char word[100];

            do
            {
                printCharactere(' ', 4);
                printf("Entrer mot => ");
                scanf("%s", word);
            } while (strlen(word) < 0 || strlen(word) > 100);            
            if (searchWord(word,0,dico))
                printf("Mot trouvé");
            else
                printf("Mot n'éxiste pas");   
            break;         
        case 4:       
            char wordToDelete[50]; // Assuming MAX_WORD_LENGTH is defined somewhere
            removeWordFromTreeAndFile(&dico);
            break;    
        case 5:
            playHangman();
            break; 
        case 6:
            playHangman2players();
            break;
        case 7:
            printEmptiedTree(dico);
            arbreSuppr(dico);
            dico = arbreConsVide();
            break;
        case 0:
            exit(0);

        default:
            break;
        }
    }
}

// ! Si vous utilisez Windows, l'executable <dictionary> ne fonctionnera pas,
// ! vous devrez mettre à jour quelques lignes de code et le recompiler.
// ! system("clear") => system("cls")
int main(int argc, char *argv[])
{
    srand(time(NULL));
    dico = arbreConsVide();
    handleInput();

    return 0;
}
