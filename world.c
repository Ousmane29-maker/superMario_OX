#include <stdlib.h>
#include <stdio.h>
#include "world.h"

/**
* @param int n
* @param int m
* @return allouer un tableau de caractères de taille n × m, où n et m sont les nombres de lignes et de colonnes, 
* et initialiser ce tableau avec le caractère espace (’ ’).
*/
char** allouer_tab_2D(int n, int m){

    char** tab = malloc(n * sizeof(char*));
    if(tab == NULL){
        exit(EXIT_FAILURE);
    }
    for(int i= 0; i < n; i++){
        tab[i] = malloc(m * sizeof(char));
    }
    for(int j = 0; j < n; j++){
        for(int k = 0; k < m; k++){
            tab[j][k] = ' ';
        }
    }
    return tab;

}

/**
* @param int n
* @param int m
* libérer un tableau à deux dimensions, de n lignes.
*/
void desallouer_tab_2D(char** tab, int n){
    for(int i = 0; i < n; i++){
        free(tab[i]);
    }
    free(tab);
    tab = NULL;
}

/**
* @param 2D tableau char** tab
* @param int n
* @param int m
* afficherlecontenud’un tableau de caractères de taille n × m.
*/
void afficher_tab_2D(char** tab, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            printf("%c ", tab[i][j]);
        }
        printf("\n");
    }
}

/**
* @param const char* nomFichier
* @param int* nbLig
* @param int* nbCol
* compter le nombre max de lignes (nbLig) et de colonnes (nbCol) dans le fichier dont le nom est nomFichier.
*/
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        exit(EXIT_FAILURE);
    }

    int ligne = 0;
    int colonne = 0;
    int maxColonne = 0; // Track the maximum column count
    int c;

    while ((c = fgetc(fichier)) != EOF) {
        if (c == '\n') {
            ligne++;
            maxColonne = (colonne > maxColonne) ? colonne : maxColonne; // Update maxColonne if needed
            colonne = 0;
        } else {
            colonne++;
        }
    }

    // After the loop, make sure to check the last line for maximum columns
    maxColonne = (colonne > maxColonne) ? colonne : maxColonne;

    fclose(fichier);
    *nbLig = ligne;
    *nbCol = maxColonne; // Set nbCol to the maximum column count
}



/**
* @param const char* nomFichier
* @return lire un fichier dont le nom est nomFichier, et retourner le tableau qui contient les caractères du fichier tel qu’une ligne du tableau correspond à une ligne du fichier.
*/

char** lire_fichier(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", nomFichier);
        return NULL;
    }
    
    int nbLig, nbCol;
    taille_fichier(nomFichier, &nbLig, &nbCol);
    char** tab = allouer_tab_2D(nbLig, nbCol);

    if (tab == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation du tableau.\n");
        fclose(fichier);
        return NULL;
    }
    
    int ligne = 0;
    int colonne = 0;
    char c;

    while ((c = fgetc(fichier)) != EOF) {
        
        if (c == '\n' || c == '\r') {
            if(colonne!=0){
                ligne++;
                colonne = 0;
            }
        } else {
            tab[ligne][colonne] = c;
            colonne++;
        }
    }
    fclose(fichier);
    return tab;
}


/**
* @param char** tab
* @param int n
* @param int m
* @param char ancien
* @param char nouveau
* @return un nouveau tableau, dans lequel toutes les occurrences du caractère ancien sont remplacées par le caractère nouveau.
*/
char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau){
    char** T = allouer_tab_2D(n, m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(tab[i][j] == ancien){

                T[i][j] = nouveau;
            }
            else{
                T[i][j] = tab[i][j];
            }
        }
    }
    return T;
    
}


/**
* @param char** tab
* @param int n
* @param int m
* @param const char* nomFichier
* Écrire le tableau tab de taille n × m dans un fichier dont le nom est nomFichier.
*/
void ecrire_fichier(const char* nomFichier, char** tab, int n, int m){
    FILE* fichier = NULL;
    fichier = fopen(nomFichier, "w");
    if(fichier != NULL){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                fputc(tab[i][j], fichier);
            }
            fputc('\n', fichier);
        }
        
        fclose(fichier);
        
    }
}


int nbSpriteAffichage(int n, int m){
    int compteur = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){

            compteur++;
        }
    }
    return compteur;
}

sprite_t* initialiser_tabSprite(char**tab, int n, int m){
    sprite_t* tabSprites = (sprite_t*)malloc(nbSpriteAffichage(n, m) * sizeof(sprite_t));
    int x, y, indiceSprite;
    y = 0;
    indiceSprite = 0;
    for(int i = 0; i < n; i++){
        x = 0;
        for(int j = 0; j < m; j++){
            //savegarde de 0 a 4 a caractere
            tabSprites[indiceSprite].caractere = tab[i][j];
            tabSprites[indiceSprite].Dest_Sprite.x = x;
            tabSprites[indiceSprite].Dest_Sprite.y = y;
            tabSprites[indiceSprite].Dest_Sprite.w = SPRITE_SIZE;
            tabSprites[indiceSprite].Dest_Sprite.h = SPRITE_SIZE;
            indiceSprite++;
            x += SPRITE_SIZE;
        }
        y += SPRITE_SIZE;    
    }

    return tabSprites;
}



