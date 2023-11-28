
#ifndef WORLD_H
#define WORLD_H

#include "liste.h"
#include <stdbool.h>


/**
 * la taille d'une plateform 
*/
#define PLATFORM_SIZE 32

/**
 * la taille d'une d'une piece 
*/
#define PIECE_SIZE 20

/**
 * le nombre de texture representant un plateformes dans limage pavage
*/
#define NOMBRE_TEXTURE_PLATFORM 6

/**
 * la hauteur du sprite
*/
#define SPRITE_HEIGHT 50

/**
 * la largeur du sprite
*/
#define SPRITE_WIDTH 30

/**
 * la largeur du sprite lorsqu'il est armee
*/
#define ARMED_SPRITE_WIDTH 60


/**
 * le pas de deplacement 
*/
#define MOVE_STEP 15

/**
 * la hauteur de l'image (src) du sprite 
*/
#define IMAGE_SPRITE_HEIGHT 50

/**
 * la largeur de l'image (src) du sprite 
*/
#define IMAGE_SPRITE_WIDTH 28

/**
 * la largeur de l'image (src) du sprite armee  
*/
#define IMAGE_ARMED_SPRITE_WIDTH 60

/**
 * Nombre de frames (images) walk  dans l'animation du joueur. 
*/
#define NOMBRE_FRAMES_WALK 9


/**
 * Nombre de frames (images) jump dans l'animation du joueur. 
*/
#define NOMBRE_FRAMES_JUMP 7

/**
 * Nombre de frames (images) attack sans arme dans l'animation du joueur. 
*/
#define NOMBRE_FRAMES_ATTACK 13

/**
 * Nombre de frames (images) attack avec arme dans l'animation du joueur. 
*/
#define NOMBRE_FRAMES_ATTACK_WITH_WEAPEON 6


/**
 * le point de vie initial d'un sprite. 
*/
#define HP_INITIAL 100


/**
 * la gravite du jeu 
*/
#define GRAVITY 2

/**
 * la largeur du drapeau 
*/
#define ENDLEVEL_WIDTH 40

/**
 * la hauteur du drapeau 
*/
#define ENDLEVEL_HEIGHT 64

#define LABEL_HEIGHT 42

#define LABEL_WIDTH 143

#define NOMBRE_LABELS 4


/**
 * @brief Structure reprÃ©sentant une plateforme statique pour l'affichage graphique.
 */
typedef struct fixedSprite_s {
    SDL_Rect src_rect; /**< Rectangle source reprÃ©sentant la plateforme (position et dimensions dans l'image source). */
    SDL_Rect dest_rect; /**< Rectangle de destination reprÃ©sentant la position et les dimensions sur l'Ã©cran. */
} fixedSprite_t;


/**
 * @brief ReprÃ©sentation du monde du jeu.
 */
typedef struct world_s {
    char** tab_terrain ; /**< Champ representant le tableau de caracteres */
    int gameOver ; /**< Champ indiquant si l'on est Ã  la fin du jeu. */
    int gravity ; /**< Champ indiquant la gravite */
    int level ; /**< Champ indiquant le level actuel */
    sprite_t player; /**< Champ indiquant le joueur. */
    fixedSprite_t endLevel ;  /**< Champ indiquant le drapeau de fin de jeu. */
    fixedSprite_t* tab_platesFormes; /**< Champ correspondant au tableau de plates-formes. */
    int nbPlateForme ; /**< Champ correspondant au nombre de plates-formes. */
    fixedSprite_t* tab_coins ; /**< Champ correspondant au tableau de pieces. */
    int nbPiece ; /**< Champ correspondant au nombre de plates-formes. */
    liste ennemis ;  /**< liste de sprite_t (les ennemies) */
    // SDL_Rect* tab_Src_Menu; /**< Champ correspondant au tableau de menu. */
    // SDL_Rect* tab_Dest_Menu; /**< Champ correspondant au tableau de menu. */
    fixedSprite_t* tab_menu;
} world_t;
    


/**
* @param int n
* @param int m
* @return allouer un tableau de caractÃ¨res de taille n Ã— m, oÃ¹ n et m sont les nombres de lignes et de colonnes, 
* et initialiser ce tableau avec le caractÃ¨re espace (â€™ â€™).
*/
char** allouer_tab_2D(int n, int m);


/**
* @param int n
* @param int m
* libÃ©rer un tableau Ã  deux dimensions, de n lignes.
*/
void desallouer_tab_2D(char** tab, int n);


/**
* @param 2D tableau char** tab
* @param int n
* @param int m
* afficherlecontenudâ€™un tableau de caractÃ¨res de taille n Ã— m.
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
* @return lireunfichierdontlenom est nomFichier, et retourner le tableau qui contient les caractÃ¨res du fichier tel quâ€™une ligne du tableau correspond Ã  une ligne du fichier.
*/
char** lire_fichier(const char* nomFichier);


/**
* @param char** tab
* @param int n
* @param int m
* @param char ancien
* @param char nouveau
* @return un nouveau tableau, dans lequel toutes les occurrences du caractÃ¨re ancien sont remplacÃ©es par le caractÃ¨re nouveau.
*/
char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau);

/**
* @param char** tab
* @param int n
* @param int m
* @param const char* nomFichier
* Ã‰crire le tableau tab de taille n Ã— m dans un fichier dont le nom est nomFichier.
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
* @param tab_terrain tableau de caracteres
* @param n le nombre de lignes
* @param m le nombre de colonne
* @return le nombre de pieces dans le fichiers text
*/
int nbrPieces(char** tab_terrain, int n, int m) ;


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
* \param sprite pointeur vers sprite_t
* \param x l'abscisse initial du sprite 
* \param y l'ordonne intial du sprite
* \param w la largeur initiale du sprite
* \param h la hauteur initiale du sprite
* \param weapon l'arme
* \brief initialise le joueur
*/
void init_sprite(sprite_t *sprite, double x, double y, int w, int h,int weapon) ;


/**
 * \brief initialise les ennemis du niveau1
*/
liste init_ennemis_level1() ;
/**
* \param endLevel  pointeur vers fixedSprite_t
* \param x l'abscisse initial du joueur 
* \param y l'ordonne intial du joueur
* \brief initialise le le drapeau
*/
void init_end_Level(fixedSprite_t *endLevel, double x, double y) ;

/**
* @param tab_terrain tableau de caracteres
* @param n le nombre de lignes
* @param m le nombre de colonne
* @param tab_coins le tableau de pieces
* @brief initialise le tableau de pieces
*/
void init_tab_coins(char ** tab_terrain, int n, int m, fixedSprite_t* tab_coins) ;

/**
* \param world pointeur vers world_t
* \param nomFichier le nom du fichier 
* \brief initialise le monde
*/
void init_world(world_t* world, const char* nomFichier);


/**
 * \brief La fonction indique si le jeu est fini en fonction des donnÃ©es du monde
 * \param world les donnÃ©es du monde
 * \return 1 si le jeu est fini, 0 sinon
 */
int is_game_over(world_t *world) ;

/**
 * \brief la fonction gere les evenements lies a la souris et au clavier
 * \param world les donnÃ©es du monde
 * \param event evenements
 */
void handle_events(world_t* world, SDL_Event *event) ;


/**
 * \brief La fonction qui veillera Ã  ce que si le sprite commence Ã  dÃ©passer la limite haut
 * \param sprite Le sprite
 */
void limite_haut(sprite_t* sprite);

/**
 * \brief La fonction qui veillera Ã  ce que si le sprite commence Ã  dÃ©passer la limite bas
 * \param sprite Le sprite
 * \param screen_Height le hauteur d'ecran
 */
void limite_bas(sprite_t* sprite , int screen_Height);

/**
 * \brief La fonction qui veillera Ã  ce que si le sprite commence Ã  dÃ©passer la limite gauche
 * \param sprite Le sprite
 */
void limite_gauche(sprite_t* sprite);

/**
 * \brief La fonction qui veillera Ã  ce que si le sprite commence Ã  dÃ©passer la limite droie
 * \param sprite Le sprite
 * \param screen_Width le largeur d'ecran
 */
void limite_droite(sprite_t* sprite, int screen_Width) ;
    

/**
 * \brief La fonction met Ã  jour les donnÃ©es en tenant compte de la physique du monde
 * \param world les donnÃ©es du monde
 * \param screen_Height le hauteur d'ecran
 * \param screen_Width la largeur de l'ecran
 */
void update_data(world_t* world, int screen_Height, int screen_Width) ;


/**
* \brief la fonction indique si le sprite est en collision avec une plateforme (du tableau) qui est a sa droite 
* \param sprite le sprite a 
* \param tab_platesFormes le tableau de plateforme
* \param nbPlateForme le nombre de plateforme
* \return vrai s'ils sont en collision
*/
bool is_colliding_right_with_a_platform(sprite_t *sprite , fixedSprite_t* tab_platesFormes, int nbPlateForme);

/**
* \brief la fonction indique si le sprite est en collision avec une plateforme (du tableau) qui est a sa gauche
* \param sprite le sprite a 
* \param tab_platesFormes le tableau de plateforme
* \param nbPlateForme le nombre de plateforme
* \return vrai s'ils sont en collision
*/
bool is_colliding_left_with_a_platform(sprite_t *sprite , fixedSprite_t* tab_platesFormes, int nbPlateForme) ;

/**
* \brief la fonction indique si le sprite est en collision avec une plateforme (du tableau) qui est en dessous 
* \param sprite le sprite a 
* \param tab_platesFormes le tableau de plateforme
* \param nbPlateForme le nombre de plateforme
* \return vrai s'ils sont en collision
*/
bool is_colliding_down_with_a_platform(sprite_t *sprite , fixedSprite_t* tab_platesFormes, int nbPlateForme) ;

/**
* \brief la fonction indique si le sprite est en collision avec une plateforme (du tableau) qui est au dessus 
* \param sprite le sprite a 
* \param tab_platesFormes le tableau de plateforme
* \param nbPlateForme le nombre de plateforme
* \return vrai s'ils sont en collision
*/
bool is_colliding_up_with_a_platform(sprite_t *sprite , fixedSprite_t* tab_platesFormes, int nbPlateForme) ;


/**
* \brief la fonction indique si le sprite est en entrain de sauter
* \param sprite le sprite  
* \return vrai si le sprite s'il est entrain de sauter
*/
bool is_jumping(sprite_t *sprite) ;


/**
* \brief la fonction qui permet de sauter
* \param sprite le sprite  
* \param world les donnÃ©es du monde
*/
void jump(sprite_t *sprite, world_t *world) ;


/**
* \brief la fonction verifie si les deux sprites passes en parametre sont en collision
* \param sprite1 le sprite  
* \param sprite2 le sprite fixe
*/
bool is_colliding(sprite_t *sprite1 , fixedSprite_t* sprite2) ;

/**
* \brief la fonction verifie si le sprite est en collision avec une piece, si oui elle supprime la piece
* \param sprite le sprite  
* \param tab_coins le tableau de piece
* \param nbre_piece le nombre de piece
*/
void handle_colliding_with_piece(sprite_t *sprite , fixedSprite_t* tab_coins, int nbre_piece) ;

/**
* \brief la fonction qui permet de deplacer les ennemis
* \param ennemis liste des ennemis  
* \param tab_platesFormes le tableau de plateformes
* \param nbPlateForme le nombre de plateforme
*/
void moving_ennemis(liste ennemis, fixedSprite_t* tab_platesFormes, int nbPlateForme) ;

/**
 * \brief la fonction qui permet au joueur d'attaquer les ennemis
 * \param player le joueur
*/
void attack_player(sprite_t* player) ;

void init_tab_Src_Menu(fixedSprite_t* tab_menu);

void init_tab_Dest_Menu(fixedSprite_t* tab_menu, int line, int clone);

void init_tab_menu(fixedSprite_t* tab_menu, int line, int clone);

bool is_click_play(fixedSprite_t* tab_menu, int position_x, int position_y);

SDL_Rect* init_tab_src_labels();

#endif