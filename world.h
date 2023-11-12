#include <SDL2/SDL.h> 
#ifndef WORLD_H
#define WORLD_H

/**
 * le nombre de sprites 
*/
#define SPRITE_SIZE 32

/**
 * la taille d'un sprites
*/
#define NOMBRE_TEXTURE 6

/**
 * la taille du joueur
*/
#define SIZE_OBJ 80

/**
 * le pas de deplacement 
*/
#define MOVE_STEP 2

/**
 * le hauteur du joueur
*/
#define MARIO_HEIGHT 24

/**
 * la largeur du joueur
*/
#define MARIO_WIDTH 16

/**
 * \brief structure des sprites
*/
typedef struct sprite_s{
    char caractere ;  
    SDL_Rect Src_Sprite ; /*!< ressource du sprites */
    SDL_Rect Dest_Sprite ; /*!< destination du sprites */

} sprite_t ;


/**
 * \brief Représentation du monde du jeu
*/
typedef struct{

    sprite_t player; /*!< Champ qui correspond au joueur dans le jeu */
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
    
} GameState ;



/**
* @param int n
* @param int m
* @return allouer un tableau de caractères de taille n × m, où n et m sont les nombres de lignes et de colonnes, 
* et initialiser ce tableau avec le caractère espace (’ ’).
*/
char** allouer_tab_2D(int n, int m);


/**
* @param int n
* @param int m
* libérer un tableau à deux dimensions, de n lignes.
*/
void desallouer_tab_2D(char** tab, int n);


/**
* @param 2D tableau char** tab
* @param int n
* @param int m
* afficherlecontenud’un tableau de caractères de taille n × m.
*/
void afficher_tab_2D(char** tab, int n, int m);

/**
* @param const char* nomFichier
* @param int* nbLig
* @param int* nbCol
* compter le nombre max de lignes (nbLig) et de colonnes (nbCol) dans le fichier dont le nom est nomFichier.
*/
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol);

/**
* @param const char* nomFichier
* @return lireunfichierdontlenom est nomFichier, et retourner le tableau qui contient les caractères du fichier tel qu’une ligne du tableau correspond à une ligne du fichier.
*/
char** lire_fichier(const char* nomFichier);


/**
* @param char** tab
* @param int n
* @param int m
* @param char ancien
* @param char nouveau
* @return un nouveau tableau, dans lequel toutes les occurrences du caractère ancien sont remplacées par le caractère nouveau.
*/
char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau);

/**
* @param char** tab
* @param int n
* @param int m
* @param const char* nomFichier
* Écrire le tableau tab de taille n × m dans un fichier dont le nom est nomFichier.
*/
void ecrire_fichier(const char* nomFichier, char** tab, int n, int m);



/**
* @param n le nombre de lignes
* @param m le nombre de colonne
* retourne le nombre de caracteres affichable ;
*/
int nbSpriteAffichage(int n, int m);

/**
* @param tab tableau de fichier
* @param n le nombre de lignes
* @param m le nombre de colonne
* retourne le tableau de sprites initialise selone le tableau fichier.txt;
*/
sprite_t* initialiser_tabSprite(char**tab, int n, int m);






#endif