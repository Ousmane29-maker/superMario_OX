#include <SDL2/SDL.h>

#ifndef FONCTIONS_FICHIERS_H
#define FONCTIONS_FICHIERS_H

/**
 * le nombre de sprites 
*/
#define SPRITE_SIZE 32

/**
 * la taille d'un sprites
*/
#define NOMBRE_TEXTURE 5

/**
 * la taille du joueur
*/
#define SIZE_OBJ 80

/**
 * le pas de deplacement 
*/
#define MOVE_STEP 5

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
 * @brief structure des sprites
*/
typedef struct sprite_s{
    char caractere ;  
    SDL_Rect Dest_Sprite ; /*!< destination du sprites */
} sprite_t ;

/**
*@param nomfichier le nom du fichier
*@param renderer le renderer
* charger une image et retourner la surface de texture associée.
*/
SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer* renderer);

/**
*@param nomfichier le nom du fichier
*@param renderer le renderer
*@param r la couleur rouge 
*@param g la couleur vert 
*@param b la couleur bleu
* charger une image avec la transparence.
*/
SDL_Texture* charger_image_transparente(const char* nomfichier,SDL_Renderer* renderer,Uint8 r, Uint8 g, Uint8 b) ;

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

/**
 * @param tabSprite le tableau de sprites
 * @param ecran le renderer
 * @param pavage la texture associe au pavage
 * @param tableau_Src_Sprites le tableau contenant contenant les sources pour les sprites
 * @param nbSpriteAffichage le nombre de caractere affichable
 * copie tous les sprites dans le rendererÒ
*/
void SDL_RenderCopySprites(sprite_t* tabSprite, SDL_Renderer* ecran, SDL_Texture* pavage, SDL_Rect* tableau_Src_Sprites,int nbSpriteAffichage);

















#endif