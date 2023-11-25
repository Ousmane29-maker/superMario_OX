#include <SDL2/SDL.h>
#include "world.h"

#ifndef DISPLAY_H
#define DISPLAY_H


/**
 * \brief Structure de gestion des ressources du jeu.
 */
typedef struct ressources_s {
    const char* terrain ; /**< le fichier representant le terrain, */
    SDL_Texture *background;  /**< Texture pour le fond du jeu. */
    SDL_Texture *playerTexture; /**< Texture pour le joueur. */
    SDL_Texture *ennemyTexture; /**< Texture l'ennemi. */
    SDL_Texture *endLevel; /**< Texture indiquant la fin du niveau. */
    SDL_Texture *pavage; /**< Texture pour les plateformes. */
    SDL_Texture *piece; /**< Texture pour les pieces. */
    // Autres ressources ici
} ressources_t;


/**
 * \brief La fonction initialise les ressources nÃ©cessaires Ã  l'affichage graphique du jeu
 * \param renderer surface correspondant Ã  l'Ã©cran de jeu
 * \param ressources les ressources du jeu
*/

void  init_ressources(SDL_Renderer *renderer, ressources_t *ressources);

/**
 * \brief La fonction nettoie les resources
 * \param resources les resources
*/
void clean_ressources(ressources_t *ressources);


/**
 * \brief La fonction nettoie les resources
 * \param resources les resources
*/
void clean_ressources(ressources_t *ressources);

/**
 * \brief La fonction initialise la SDL.
 * Elle crÃ©e la fenÃªtre du jeu ainsi que le renderer
 * \param window la fenÃªtre du jeu
 * \param renderer le renderer
 * \param width largeur de l'Ã©cran de jeu
 * \param height hauteur de l'Ã©cran de jeu
 * \return -1 en cas d'erreur, 0 sinon
*/

int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height);

/**
*@param nomfichier le nom du fichier
*@param renderer le renderer
* charger une image et retourner la surface de texture associeÌe.
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
 * @param tab_platesFormes le tableau de plateformes
 * @param renderer le renderer
 * @param pavage la texture associe au pavage
 * @param nbre_plateforme le nombre de plateforme
 * @brief copie tous les plateformes dans le renderer
*/
void SDL_RenderCopyPlateFormes(fixedSprite_t* tab_platesFormes, SDL_Renderer* renderer, SDL_Texture* pavage,int nbre_plateforme);

/**
 * @param tab_coins le tableau de pieces
 * @param renderer le renderer
 * @param piece la texture associe au piece
 * @param nbre_piece le nombre de piece
 * @brief copie tous les pieces dans le rendererÃ’
*/
void SDL_RenderCopyPieces(fixedSprite_t* tab_coins, SDL_Renderer* renderer, SDL_Texture* piece, int nbre_piece);

/**
 * @param sprite le sprite
 * @param renderer le renderer
 * @param spriteTexture la texture associee au sprite
 * @brief copie le sprite dans le rendererer
*/
void SDL_RenderCopySprite(sprite_t* sprite, SDL_Renderer* renderer, SDL_Texture* spriteTexture) ;

/**
 * @param ennemis la liste des ennemis
 * @param renderer le renderer
 * @param ennemyTexture la texture associee au ennemis
 * @brief copie tous les ennemis dans le rendererer
*/
void SDL_RenderCopyEnnemis(liste ennemis, SDL_Renderer* renderer, SDL_Texture* ennemyTexture) ;

/**
 * @param renderer le renderer
 * @param world le monde du jeu
 * @param ressources les ressources du jeu 
 * @brief met a jour l'ecran
*/
void refresh_graphics(SDL_Renderer* renderer, world_t *world, ressources_t* ressources);


#endif