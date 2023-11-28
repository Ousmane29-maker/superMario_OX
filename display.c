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
    ressources->ennemyTexture = charger_image("ressources/ennemy.bmp", renderer) ;
    ressources->endLevel = charger_image_transparente("ressources/endLevel.bmp", renderer, 255,255,255) ;
    ressources->pavage = charger_image("ressources/pavage.bmp", renderer) ;
    ressources->piece = charger_image("ressources/piece.bmp", renderer) ;
    ressources->menu = charger_image("ressources/menu.bmp", renderer) ;
    ressources->menubackground = charger_image("ressources/menubackground.bmp", renderer) ;

}

void clean_ressources(ressources_t *ressources){
    SDL_DestroyTexture(ressources->pavage);
    SDL_DestroyTexture(ressources->playerTexture);
    SDL_DestroyTexture(ressources->ennemyTexture);
    SDL_DestroyTexture(ressources->background);
    SDL_DestroyTexture(ressources->endLevel);
    SDL_DestroyTexture(ressources->piece);
    SDL_DestroyTexture(ressources->menu);
    SDL_DestroyTexture(ressources->menubackground);
}

SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer* renderer){
    // Charger l'image depuis le fichier
    SDL_Surface* surface = SDL_LoadBMP(nomfichier);
    
    if (surface == NULL) {
        // GÃ©rer les erreurs si la surface n'a pas pu Ãªtre chargÃ©e
        fprintf(stderr,"Erreur de chargement de l'image : %s\n", SDL_GetError());
        return NULL;
    }
    
    // Convertir la surface en texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    if (texture == NULL) {
        // GÃ©rer les erreurs si la texture n'a pas pu Ãªtre crÃ©Ã©e
        fprintf(stderr,"Erreur de crÃ©ation de la texture : %s\n", SDL_GetError());
    }
    
    // LibÃ©rer la mÃ©moire de la surface, car nous n'en avons plus besoin
    SDL_FreeSurface(surface);
    
    return texture;
}



SDL_Texture* charger_image_transparente(const char* nomfichier, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b) {
    // Charger l'image depuis le fichier
    SDL_Surface* surface = SDL_LoadBMP(nomfichier);
    
    if (surface == NULL) {
        // GÃ©rer les erreurs si la surface n'a pas pu Ãªtre chargÃ©e
        fprintf(stderr,"Erreur de chargement de l'image : %s\n", SDL_GetError());
        return NULL;
    }
    
    // DÃ©finir la couleur transparente en utilisant SDL_MapRGB avec le format de la surface
    Uint32 colorkey = SDL_MapRGB(surface->format, r, g, b);
    
    SDL_SetColorKey(surface, SDL_TRUE, colorkey);
    // Appliquer la couleur transparente Ã  la surface
    if (SDL_SetColorKey(surface, SDL_TRUE, colorkey) != 0) {
        // GÃ©rer les erreurs si la couleur transparente n'a pas pu Ãªtre dÃ©finie
        fprintf(stderr,"Erreur de configuration de la couleur transparente : %s\n", SDL_GetError());
    }
    
    // Convertir la surface en texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    if (texture == NULL) {
        // GÃ©rer les erreurs si la texture n'a pas pu Ãªtre crÃ©Ã©e
        fprintf(stderr,"Erreur de crÃ©ation de la texture : %s\n", SDL_GetError());
    }
    
    // LibÃ©rer la mÃ©moire de la surface, car nous n'en avons plus besoin
    SDL_FreeSurface(surface);
    
    return texture;
}


void SDL_RenderCopyPlateFormes(fixedSprite_t* tab_platesFormes, SDL_Renderer* renderer, SDL_Texture* pavage,int nbre_plateforme){
    for(int i = 0; i < nbre_plateforme; i++){
        SDL_RenderCopy(renderer, pavage, &tab_platesFormes[i].src_rect, &tab_platesFormes[i].dest_rect);
    }
}


void SDL_RenderCopyPieces(fixedSprite_t* tab_coins, SDL_Renderer* renderer, SDL_Texture* piece, int nbre_piece){
    for(int i = 0; i < nbre_piece; i++){
        SDL_RenderCopy(renderer, piece, NULL, &tab_coins[i].dest_rect);
    }
}

void SDL_RenderCopySprite(sprite_t* sprite, SDL_Renderer* renderer, SDL_Texture* spriteTexture){
    if(is_jumping(sprite)){
        if(sprite->vers_la_droite == 1){
            SDL_RenderCopy(renderer, spriteTexture, &sprite->jump_rects[sprite->current_frame_jump], &sprite->dest_rect);
        }else{
            SDL_RenderCopyEx(renderer, spriteTexture, &sprite->jump_rects[sprite->current_frame_jump],& sprite->dest_rect,0,NULL,SDL_FLIP_HORIZONTAL) ;
        } 
    }else{ // ! is_jumping
        if(sprite->weapeon == 0){ // le sprite est sans arme
            if(sprite->vers_la_droite == 1){ // sans arme + vers la droite
                if(sprite->is_attacking == 1){ //is_attacking
                    SDL_RenderCopy(renderer, spriteTexture, &sprite->attack_rects[sprite->current_frame_attack], &sprite->dest_rect);
                }else{ // !is_attacking
                    SDL_RenderCopy(renderer, spriteTexture, &sprite->walk_rects[sprite->current_frame_walk], &sprite->dest_rect);
                }
            }else{ // sans arme + vers la gauche
                if(sprite->is_attacking == 1){ //is_attacking
                    SDL_RenderCopyEx(renderer, spriteTexture, &sprite->attack_rects[sprite->current_frame_attack], &sprite->dest_rect,0,NULL,SDL_FLIP_HORIZONTAL);
                }else{ // !is_attacking
                    SDL_RenderCopyEx(renderer, spriteTexture, &sprite->walk_rects[sprite->current_frame_walk], &sprite->dest_rect,0,NULL,SDL_FLIP_HORIZONTAL) ;
                }
            }
        }else{ // le sprite a son arme
            if(sprite->vers_la_droite == 1){ //  arme + vers la droite
                if(sprite->is_attacking == 1){ //is_attacking
                    SDL_RenderCopy(renderer, spriteTexture, &sprite->attack_with_weapeon_rects[sprite->current_frame_attack_with_weapeon], &sprite->dest_rect);
                }else{ // !is_attacking
                    SDL_RenderCopy(renderer, spriteTexture, &sprite->walk_with_weapeon_rects[sprite->current_frame_walk], &sprite->dest_rect);
                }
            }else{ //  arme + vers la gauche
                if(sprite->is_attacking == 1){ //is_attacking
                    SDL_RenderCopyEx(renderer, spriteTexture, &sprite->attack_with_weapeon_rects[sprite->current_frame_attack_with_weapeon], &sprite->dest_rect,0,NULL,SDL_FLIP_HORIZONTAL);
                }else{ // !is_attacking
                    SDL_RenderCopyEx(renderer, spriteTexture, &sprite->walk_with_weapeon_rects[sprite->current_frame_walk], &sprite->dest_rect,0,NULL,SDL_FLIP_HORIZONTAL) ;
                }    
            }
        }
    }
}

void SDL_RenderCopyEnnemis(liste ennemis, SDL_Renderer* renderer, SDL_Texture* ennemyTexture){
    liste temp = ennemis ;
    while(! is_empty(temp)){
        SDL_RenderCopySprite(&temp->data, renderer, ennemyTexture) ;
        temp = next(temp) ;
    }
}

void SDL_RenderCopyMenu(SDL_Renderer* renderer, SDL_Texture *menu, fixedSprite_t* tab_menu){
    for(int i = 0; i < NOMBRE_LABELS; i++){

        SDL_RenderCopy(renderer, menu, &tab_menu[i].src_rect, &tab_menu[i].dest_rect);

    }

}

void refresh_graphics(SDL_Renderer* renderer, world_t *world, ressources_t* ressources){
    SDL_RenderClear(renderer);   
    // le fond
    SDL_RenderCopy(renderer, ressources->background,NULL, NULL);
    // Copier les platformes dans le renderer
    SDL_RenderCopyPlateFormes(world->tab_platesFormes, renderer, ressources->pavage, world->nbPlateForme);
    // Copier les pieces dans le renderer
    SDL_RenderCopyPieces(world->tab_coins, renderer, ressources->piece, world->nbPiece);
    // Copier le drapeau dans le renderer
    SDL_RenderCopy(renderer, ressources->endLevel, NULL, &world->endLevel.dest_rect);
    // Copier le joueur dans le renderer
    SDL_RenderCopySprite(&world->player, renderer, ressources->playerTexture) ;
    // Copier les ennemis dans le renderer
    SDL_RenderCopyEnnemis(world->ennemis,renderer, ressources->ennemyTexture) ;
    // Afficher tout dans la fenÃªtre
    SDL_RenderPresent(renderer);
}