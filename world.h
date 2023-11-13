
#ifndef WORLD_H
#define WORLD_H

#include <SDL2/SDL.h> 

/**
 * le nombre de sprites 
*/
#define PLATFORM_SIZE 32

/**
 * la taille d'un sprites
*/
#define NOMBRE_TEXTURE_PLATFORM 9

/**
 * la taille du joueur
*/
#define SPRITE_SIZE 80

/**
 * le pas de deplacement 
*/
#define MOVE_STEP 5


#define IMAGE_PLAYER_HEIGHT 64

#define IMAGE_PLAYER_WIDTH 64

/**
 * Nombre de frames (images) dans l'animation du joueur. 
*/
#define NOMBRE_FRAMES_WALK 9

/**
 * Abscisse initiale du joueur. 
*/
#define ABS_PLAYER_INITIAL 0

/**
 * Ordonne initiale du joueur. 
*/
#define ORD_PLAYER_INITIAL 0


/**
 * @brief Structure représentant une plateforme statique pour l'affichage graphique.
 */
typedef struct fixedSprite_s {
    SDL_Rect src_rect; /**< Rectangle source représentant la plateforme (position et dimensions dans l'image source). */
    SDL_Rect dest_rect; /**< Rectangle de destination représentant la position et les dimensions sur l'écran. */
} fixedSprite_t;

/**
 * @brief Structure représentant un sprite pour l'affichage graphique avec animation.
 */
typedef struct sprite_s {
    SDL_Rect* walk_rects; /**< Tableau de rectangles source représentant les différentes images du sprite en marchant. */
    SDL_Rect dest_rect; /**< Rectangle de destination représentant la position et les dimensions sur l'écran. */
    int current_frame_walk; /**< Frame walk actuelle affichée. */
    int vers_la_droite; /**< Champ indiquant si le sprite va vers la droite  */
} sprite_t;

/**
 * @brief Représentation du monde du jeu.
 */
typedef struct world_s {
    char** tab_terrain ; /**< Champ representant le tableau de caracteres */
    int gameOver; /**< Champ indiquant si l'on est à la fin du jeu. */
    sprite_t player; /**< Champ indiquant le joueur. */
    fixedSprite_t* tab_platesFormes; /**< Champ correspondant au tableau de plates-formes. */
    int nbPlateForme ; /**< Champ correspondant au nombre de plates-formes. */
} world_t;
    


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
* @param tab_terrain tableau de caracteres
* @param n le nombre de lignes
* @param m le nombre de colonne
* @return le nombre de plateformes dans le fichiers text
*/
int nbrPlateformes(char** tab_terrain, int n, int m) ;


/**
* @return un tableau de SDL_Rect initialise representant les src associe a chaque plateformes (image dans pavage)
*/
SDL_Rect* init_tab_src_pavage() ;

/**
* @param tab_terrain tableau de caracteres
* @param n le nombre de lignes
* @param m le nombre de colonne
* @param tab_plateFormes le tableau de platform
* initialise src_rect du tab_plateFormes
*/
void init_src_rect_tab_plateFormes(char ** tab_terrain, int n, int m, fixedSprite_t* tab_plateFormes);


/**
* @param tab_terrain tableau de caracteres
* @param n le nombre de lignes
* @param m le nombre de colonne
* @param tab_plateFormes le tableau de platform
* initialise dest_rect du tab_plateFormes
*/
void init_dest_rect_tab_plateFormes(char ** tab_terrain, int n, int m, fixedSprite_t* tab_plateFormes) ;


/**
* @param tab_plateFormes le tableau de plateformes
* @param tab_terrain tableau de caracteres
* @param n le nombre de lignes
* @param m le nombre de colonne
* @return le tableau de plateformes initialise
*/
void init_tab_platesFormes(fixedSprite_t* tab_plateFormes, char ** tab_terrain, int n, int m) ;

/**
* \param player pointeur vers sprite_t
* \brief initialise le joueur
*/
void init_player(sprite_t *player) ;

/**
* \param world pointeur vers world_t
* \param nomFichier le nom du fichier 
* \brief initialise le monde
*/
void init_world(world_t* world, const char* nomFichier);


/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */
int is_game_over(world_t *world) ;

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_events(SDL_Event* event, world_t* world);

/**
 * \brief La fonction qui veillera à ce que si le vaisseau commence à dépasser la limite haut
 * \param sprite Le sprite
 */
void limite_haut(sprite_t* sprite);

/**
 * \brief La fonction qui veillera à ce que si le vaisseau commence à dépasser la limite bas
 * \param sprite Le sprite
 */
void limite_bas(sprite_t* sprite , int nbLig);
    

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param world les données du monde
 */
void update_data(world_t* world, int nbLig);




#endif