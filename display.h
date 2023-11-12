#include <SDL2/SDL.h>
#include "world.h"

#ifndef DISPLAY_H
#define DISPLAY_H


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
 * @param tabSprite le tableau de sprites
 * @param ecran le renderer
 * @param pavage la texture associe au pavage
 * @param tableau_Src_Sprites le tableau contenant contenant les sources pour les sprites
 * @param nbSpriteAffichage le nombre de caractere affichable
 * copie tous les sprites dans le rendererÒ
*/
void SDL_RenderCopySprites(sprite_t* tabSprite, SDL_Renderer* ecran, SDL_Texture* pavage, SDL_Rect* tableau_Src_Sprites,int nbSpriteAffichage);


/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param gameState les données du monde
 */
void handle_events(SDL_Event* event, GameState* gameState);

void init_data (GameState* gameState);













#endif