#include <stdlib.h>
#include <stdio.h>
#include "display.h"


int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height)
{
    if(0 != SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO))
    {
        fprintf(stderr, "Erreur initialisation de la SDL : %s", SDL_GetError());
        return -1;
    }
    if(0 != SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, window, renderer))
    {
        fprintf(stderr, "Erreur lors de la creation de l'image et du renderer : %s", SDL_GetError());
        return -1;
    }
    return 0;
}

void  init_ressources(SDL_Renderer *renderer, ressources_t *ressources){
    ressources->terrain = "ressources/terrain.txt" ;
    ressources->background= charger_image("ressources/fond.bmp", renderer) ;
    ressources->playerTexture = charger_image("ressources/player.bmp", renderer) ;
    ressources->endLevel = charger_image("ressources/endLevel.bmp", renderer) ;
    ressources->pavage = charger_image("ressources/pavage.bmp", renderer) ;

}

void clean_ressources(ressources_t *ressources){
    SDL_DestroyTexture(ressources->pavage);
    SDL_DestroyTexture(ressources->playerTexture);
    SDL_DestroyTexture(ressources->background);
}

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


void SDL_RenderCopyPlateFormes(world_t* world, SDL_Renderer* ecran, SDL_Texture* pavage,int nbre_plateforme){
    for(int i = 0; i < nbre_plateforme; i++){
        SDL_RenderCopy(ecran,pavage, &world->tab_platesFormes[i].src_rect, &world->tab_platesFormes[i].dest_rect);
    }
}


void refresh_graphics(SDL_Renderer* renderer, world_t *world, ressources_t* ressources){
    SDL_RenderClear(renderer);
    // le fond
    SDL_RenderCopy(renderer, ressources->background,NULL, NULL);
    // Copier les platformes dans le renderer
    SDL_RenderCopyPlateFormes(world, renderer, ressources->pavage, world->nbPlateForme);
    // Copier le joueur dans le renderer
    if(is_jumping(&world->player)){
       if(world->player.vers_la_droite == 1){
            SDL_RenderCopy(renderer, ressources->playerTexture, &world->player.jump_rects[world->player.current_frame_jump], &world->player.dest_rect);
        }else{
            SDL_RenderCopyEx(renderer, ressources->playerTexture, &world->player.jump_rects[world->player.current_frame_jump], &world->player.dest_rect,0,NULL,SDL_FLIP_HORIZONTAL) ;
        } 
    }else{
        if(world->player.weapeon == 0){
            if(world->player.vers_la_droite == 1){
                SDL_RenderCopy(renderer, ressources->playerTexture, &world->player.walk_rects[world->player.current_frame_walk], &world->player.dest_rect);
            }else{
                SDL_RenderCopyEx(renderer, ressources->playerTexture, &world->player.walk_rects[world->player.current_frame_walk], &world->player.dest_rect,0,NULL,SDL_FLIP_HORIZONTAL) ;
            }
        }else{
            if(world->player.vers_la_droite == 1){
                SDL_RenderCopy(renderer, ressources->playerTexture, &world->player.walk_with_weapeon_rects[world->player.current_frame_walk], &world->player.dest_rect);
            }else{
                SDL_RenderCopyEx(renderer, ressources->playerTexture, &world->player.walk_with_weapeon_rects[world->player.current_frame_walk], &world->player.dest_rect,0,NULL,SDL_FLIP_HORIZONTAL) ;
            }
        }
    }
    
    // Afficher tout dans la fenêtre
    SDL_RenderPresent(renderer);
}
