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
    SDL_Texture *endLevel; /**< Texture indiquant la fin du niveau. */
    SDL_Texture *pavage; /**< Texture pour les plateformes. */
    // Autres ressources ici
} ressources_t;


/**
 * \brief La fonction initialise les ressources nécessaires à l'affichage graphique du jeu
 * \param renderer surface correspondant à l'écran de jeu
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
 * Elle crée la fenêtre du jeu ainsi que le renderer
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param width largeur de l'écran de jeu
 * \param height hauteur de l'écran de jeu
 * \return -1 en cas d'erreur, 0 sinon
*/

int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height);

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
 * @param world le monde
 * @param ecran le renderer
 * @param pavage la texture associe au pavage
 * @param nbre_plateforme le nombre de nbre_plateforme
 * copie tous les sprites dans le rendererÒ
*/
void SDL_RenderCopyPlateFormes(world_t* world, SDL_Renderer* ecran, SDL_Texture* pavage,int nbre_plateforme);



void refresh_graphics(SDL_Renderer* renderer, world_t *world, ressources_t* ressources);


#endif