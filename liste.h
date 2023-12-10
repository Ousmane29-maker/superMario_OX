
#ifndef LISTE_H
#define LISTE_H

#include <SDL2/SDL.h> 

/**
 * @file liste.h
 * @brief Définition des structures et fonctions pour la gestion d'une liste chaînée.
 */


/**
 * @brief Structure representant un sprite pour l'affichage graphique avec animation.
 */
typedef struct sprite_s {
    SDL_Rect* walk_rects; /**< Tableau de rectangles source representant les diffÃ©rentes images du sprite en marchant. */
    SDL_Rect* walk_with_weapeon_rects ; /**< Tableau de rectangles source reprÃ©sentant les diffÃ©rentes images du sprite en marchant. */
    SDL_Rect* jump_rects ; /**< Tableau de rectangles source representant les diffÃ©rentes images du sprite en sautant. */
    SDL_Rect* attack_rects ; /**< Tableau de rectangles source representant les differentes images du sprite en attaquant*/
    SDL_Rect* attack_with_weapeon_rects ; /**< Tableau de rectangles source representant les differentes images du sprite en attaquant avec l'arme*/
    SDL_Rect* death_rects ; /**< Tableau de rectangles source representant les differentes images du sprite apres que son HP <= 0 */
    SDL_Rect dest_rect; /**< Rectangle de destination reprÃ©sentant la position et les dimensions sur l'Ã©cran. */
    int weapeon ; /**< champ indiquant si le personnage est armee ou pas */
    int current_frame_walk; /**< Frame walk actuelle affiché. */
    int vers_la_droite; /**< Champ indiquant si le sprite va vers la droite  */
    int current_frame_jump ; /**< Champ indiquant le moment du saut */
    int current_frame_attack ; /**<  Frame attack actuelle affiché. */
    int current_frame_attack_with_weapeon ; /**<  Frame attack avec une arme actuelle affiché. */
    int current_frame_death ; /**<  Frame death actuelle affiché. */
    int is_attacking ; /**< Champ indiquant si le sprite est entrain d'attaquer ou pas */
    int HP ; /**< Champ indiquant le point de vie d'un sprite */
    int nbPieceRamasse ; /**< Champ correspondant au nombre de piece ramassÃ©. */
    Uint32 lastAttackTime; /** Chanp indiquant quand la derniere attaque a eu lieu*/
} sprite_t;


/**
 * @brief Structure pour représenter un nœud de la liste.
 */
typedef struct node_t {
    sprite_t data;             /**< Donnée du nœud */
    struct node_t* next;      /**< Pointeur vers le prochain nœud dans la liste */
} node_t, *liste;

/**
 * @brief Initialise une liste vide.
 * @return Un pointeur vers la liste vide.
 */
liste cons_empty();

/**
 * @brief Ajoute un nouveau nœud avec des données spécifiées à la tête de la liste.
 * @param sprite Les données à ajouter au nœud.
 * @param next Le pointeur vers le prochain nœud dans la liste.
 * @return Un pointeur vers le nouveau nœud ajouté à la liste.
 */
liste cons(sprite_t sprite, liste next);

/**
 * @brief Vérifie si la liste est vide.
 * @param l La liste à vérifier.
 * @return 1 si la liste est vide, 0 sinon.
 */
int is_empty(liste l);

/**
 * @brief Récupère la valeur du nœud en tête de liste.
 * @param l La liste dont on veut obtenir la valeur du nœud en tête.
 * @return Les données du nœud en tête de liste.
 */
sprite_t value(liste l);

/**
 * @brief Retourne le pointeur vers le prochain nœud dans la liste.
 * @param l La liste dont on veut obtenir le prochain nœud.
 * @return Un pointeur vers le prochain nœud dans la liste, ou NULL si la liste est vide.
 */
liste next(liste l);


/**
 * @brief remplace l'ancien abscisse du sprite par la nouvelle .
 * @param l La liste .
 * @param new_x la nouvelle abscisse pour le sprite en tete de la liste
 */
void change_value_x(liste l, int new_x) ;

/**
 * @brief remplace l'ancien ordonnee du sprite par la nouvelle .
 * @param l La liste .
 * @param new_y la nouvelle ordonnee pour le sprite en tete de la liste
 */
void change_value_y(liste l, int new_y) ;

/**
 * @brief remplace l'ancien valeur de vers_la_droite du sprite par la nouvelle .
 * @param l La liste .
 * @param new_direction la nouvelle direction pour le sprite en tete de la liste
 */
void change_value_vers_la_droite(liste l, int new_direction) ;


/**
 * @brief remplace l'ancien valeur de current_frame_walk du sprite par la nouvelle .
 * @param l La liste .
 * @param new_current_frame_walk la nouvelle current_frame_walk pour le sprite en tete de la liste
 */
void change_value_current_frame_walk(liste l, int new_current_frame_walk) ;

/**
 * @brief remplace l'ancien valeur de current_frame_death du sprite par la nouvelle .
 * @param l La liste .
 * @param new_current_frame_death la nouvelle current_frame_death pour le sprite en tete de la liste
 */
void change_value_current_frame_death(liste l, int new_current_frame_death) ;

/**
 * @brief remplace l'ancien valeur de HP du sprite par la nouvelle .
 * @param l La liste .
 * @param new_HP la nouvelle HP pour le sprite en tete de la liste
 */
void change_HP(liste l, int new_HP) ;

void change_next(liste l, node_t* new_next) ;

/**
 * @brief Libère la mémoire associée à tous les nœuds de la liste.
 * Cette fonction libère la mémoire allouée pour chaque nœud de la liste, en commençant par la tête.
 * @param l La liste à libérer.
 */
void liberer_liste(liste l) ;

#endif