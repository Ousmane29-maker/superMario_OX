#include <stdlib.h>
#include <stdio.h>
#include "fonctions_fichiers.h"

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

//SDL2

SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer* renderer){
    // Charger l'image depuis le fichier
    SDL_Surface* surface = SDL_LoadBMP(nomfichier);
    
    if (surface == NULL) {
        // Gérer les erreurs si la surface n'a pas pu être chargée
        fprintf(stderr,"Erreur de chargement de l'image : %s\n", SDL_GetError());
        return NULL;
    }
    
    // Convertir la surface en texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    if (texture == NULL) {
        // Gérer les erreurs si la texture n'a pas pu être créée
        fprintf(stderr,"Erreur de création de la texture : %s\n", SDL_GetError());
    }
    
    // Libérer la mémoire de la surface, car nous n'en avons plus besoin
    SDL_FreeSurface(surface);
    
    return texture;
}



SDL_Texture* charger_image_transparente(const char* nomfichier, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b) {
    // Charger l'image depuis le fichier
    SDL_Surface* surface = SDL_LoadBMP(nomfichier);
    
    if (surface == NULL) {
        // Gérer les erreurs si la surface n'a pas pu être chargée
        fprintf(stderr,"Erreur de chargement de l'image : %s\n", SDL_GetError());
        return NULL;
    }
    
    // Définir la couleur transparente en utilisant SDL_MapRGB avec le format de la surface
    Uint32 colorkey = SDL_MapRGB(surface->format, r, g, b);
    
    SDL_SetColorKey(surface, SDL_TRUE, colorkey);
    // Appliquer la couleur transparente à la surface
    if (SDL_SetColorKey(surface, SDL_TRUE, colorkey) != 0) {
        // Gérer les erreurs si la couleur transparente n'a pas pu être définie
        fprintf(stderr,"Erreur de configuration de la couleur transparente : %s\n", SDL_GetError());
    }
    
    // Convertir la surface en texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    if (texture == NULL) {
        // Gérer les erreurs si la texture n'a pas pu être créée
        fprintf(stderr,"Erreur de création de la texture : %s\n", SDL_GetError());
    }
    
    // Libérer la mémoire de la surface, car nous n'en avons plus besoin
    SDL_FreeSurface(surface);
    
    return texture;
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



void SDL_RenderCopySprites(sprite_t* tabSprite, SDL_Renderer* ecran, SDL_Texture* pavage, SDL_Rect* tableau_Src_Sprites,int nbSpriteAffichage){
    for(int i = 0; i < nbSpriteAffichage; i++){
        switch (tabSprite[i].caractere)
        {
            case '0':
                SDL_RenderCopy(ecran,pavage,&tableau_Src_Sprites[0], &tabSprite[i].Dest_Sprite) ;
                break;
            case '1':
                SDL_RenderCopy(ecran,pavage,&tableau_Src_Sprites[1], &tabSprite[i].Dest_Sprite) ;
                break;
            case '2':
                SDL_RenderCopy(ecran,pavage,&tableau_Src_Sprites[2], &tabSprite[i].Dest_Sprite) ;
                break;
            case '3':
                SDL_RenderCopy(ecran,pavage,&tableau_Src_Sprites[3], &tabSprite[i].Dest_Sprite) ;
                break;
            case '4':
                SDL_RenderCopy(ecran,pavage,&tableau_Src_Sprites[4], &tabSprite[i].Dest_Sprite) ;
                break;    
        }
    }
}







