#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../headers/struct.h"
#include "../../headers/dictionary.h"

void printCharactere(char charactere, int number)
{
    if (charactere != ' ')
        printf("\n");

    for (int i = 0; i < number; i++)
    {
        printf("%c", charactere);
    }

    if (charactere != ' ')
        printf("\n");
}

void printSingleOption(const char *content, int firstSpacing, int secondSpacing, int last)
{
    printf("|");
    printCharactere(' ', firstSpacing);
    printf("%s", content);
    printCharactere(' ', secondSpacing);
    printf("|");
    if (last == 0)
        printf("\n");
}

void printOptions()
{
    printSingleOption("1. Ajouter des mots au dictionaires", 4, 29, 0);
    printSingleOption("2. Consulter le dictionaire", 4, 37, 0);
    printSingleOption("3. Chercher un mot", 4, 46, 0);
    printSingleOption("4. Supprimer un mot", 4, 45, 0);
    printSingleOption("5. Jeu de pendu", 4, 49, 0);
    printSingleOption("6. Vider l'arbre", 4, 48, 0);
    printSingleOption(" ", 4, 63, 0);
    printSingleOption("0. Quitter", 4, 54, 1);
}

void printHeader(const char *content, int spacing)
{
    printCharactere('-', 70);
    printf("|");
    printCharactere(' ', 25);
    printf("%s", content);
    printCharactere(' ', spacing);
    printf("|");
    printCharactere('-', 70);
}

void printFooter()
{
    printCharactere('-', 70);
}

void printToConsole()
{
    printHeader("Dictionary Management", 22);
    printOptions();
    printFooter();
}

void printDictionary(tree *dico, char path[], int wordLen)
{
    //system("clear");
    printHeader("Current Dictionary", 25);
    if (dico == NULL)
    {
        printCharactere(' ', 25);
        printf("\033[1;31mL'arbre est vide\033[0m");
    }
    else
    {
        dicoAfficher(dico, path, wordLen);
    }

    printFooter();

    int option;

    do
    {
        printCharactere(' ', 4);
        printf(" 0 pour retourner => ");
        scanf("%d", &option);
    } while (option != 0);

   // system("clear");
}

/*void printTotalWords(tree *dico)
{
    system("clear");
    printHeader("Dictionary Stats", 27);
    printCharactere(' ', 22);
    printf("Le nombre total de mot est:  \033[0;35m%d\033[0m", dicoNbMotsTotal(dico));
    printFooter();
}*/

tree *printRandomWord(tree *dico)
{
    char filename[100];
    char buffer[100];

    do
    {
        printCharactere(' ', 4);
        printf("Entrer le fichier => ");
        scanf("%s", filename);
    } while (strlen(filename) < 0 || strlen(filename) > 100);

    system("clear");
    printHeader("Random Word Picker", 25);
    printCharactere(' ', 18);
 /*   if (choisirMot(buffer, filename) == 1)
    {
        printf("\033[0;32mMot ajouté avec success, le mot est \033[0;35m%s\033[0m", buffer);
        printFooter();

        return dicoInsererMot(buffer, dico, 0);
    }


    printf("\033[1;31mVeuillez vérifier le nom de fichier\033[0m");
    printFooter();*/
    printf("\033[0;32mMot choisi: \033[0;35m%s\033[0m", choisirMot(filename,1));
    return dico;
}

void printEmptiedTree(tree *dico)
{
    system("clear");
    printHeader("Dictionary Management", 22);
    printCharactere(' ', 25);
    if (dico == NULL)
    {
        printf("\033[1;31mL'arbre est déja vide\033[0m");
    }
    else
    {
        printf("\033[0;32mArbre effacé avec succès\033[0m");
    }

    printFooter();
}

void printSubMenu()
{
    system("clear");
    printHeader("Insertion Options", 26);
    printSingleOption("1. Ajouter manuellement", 4, 41, 0);
    printSingleOption("2. Ajouter à partir d'une fichier", 4, 31, 0);
    printSingleOption(" ", 4, 63, 0);
    printSingleOption("0. Retourner", 4, 52, 1);
    printFooter();
}

tree *handleFile(tree *dico)
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
        line[strlen(line) - 1] = '\0';
        dico = dicoInsererMot(line, dico, 0);
    }

    fclose(file);

    printf("\033[0;32mMots ajouté avec success\033[0m");
    printFooter();

    return dico;
}

tree *HandleManual(tree *dico)
{
    char word[100];

    do
    {
        printCharactere(' ', 4);
        printf("Entrer mot => ");
        scanf("%s", word);
    } while (strlen(word) < 0 || strlen(word) > 100);

    system("clear");
    printHeader("Insertion Options", 25);
    printCharactere(' ', 23);

    printf("\033[0;32mMot ajouté avec success\033[0m");
    printFooter();

    return dicoInsererMot(word, dico, 0);
}

tree *fillTree(tree *dico)
{
    int option;

    printSubMenu();
    do
    {
        printCharactere(' ', 4);
        printf(" => ");
        scanf("%d", &option);
    } while (option < 0 || option > 2);

    switch (option)
    {
    case 0:
        system("clear");
        break;
    case 1:
        dico = HandleManual(dico);
        break;

    case 2:
        dico = handleFile(dico);
        break;

    default:
        break;
    }

    return dico;
}

void printHelp()
{
    printf("\033[0;32mUSAGE:\n\033[0m");
    printf("dictionary [--help]\n\n");

    printf("\033[0;32m--help:\n\033[0m");
    printf("\tImprime les informations d'aide.\n\n");

    printf("\033[0;32mGUIDE\n\033[0m");
    printf("\t1. L'insertion de mots peut se faire via deux options:\n");
    printf("\t\t1.1. Manuellement où l'utilisateur tapez le mot.\n");
    printf("\t\t1.2. Via des fichiers où le fichier doit être un fichier texte.\n\n");
    printf("\t2. L'option 'Piocher' sera un mot aléatoire provenant d'un fichier texte donné.\n\n");
    printf("\t3. Quelque soit l'option 'Insertion' ou 'Piocher' le fichier text doivent être dans \n");
    printf("\tle même répertoire que l'executable.\n\n");
}