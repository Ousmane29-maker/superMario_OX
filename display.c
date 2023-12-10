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
    if(sprite->HP > 0){
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
    }else{ //the sprite die
        if(sprite->current_frame_death < 5){
            sprite->current_frame_death = sprite->current_frame_death + 1 ;
        }
        SDL_Delay(80); //une petite pause
        SDL_RenderCopy(renderer, spriteTexture, &sprite->death_rects[sprite->current_frame_death], &sprite->dest_rect);
        
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


void display_life_bar(SDL_Renderer *renderer, int x, int y, int w, int h, int life, int max_life, SDL_Color color){
    if(life < 0){
        life = 0 ;
    }
    // Calcul du ratio de vie
    float life_ratio = (float)life / max_life;

    // Calcul de la taille de la barre de vie
    int life_bar_w = (int)(w * life_ratio);

    // Dessin du fond de la barre de vie au dessus du sprite (-5) et de hauteur 7
    SDL_Rect bg_rect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &bg_rect);

    // Dessin de la barre de vie
    SDL_Rect life_bar_rect = {x, y, life_bar_w, h};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &life_bar_rect);
}

void display_life_bar_ennemy(SDL_Renderer *renderer, liste ennemis){
    liste temp = ennemis ;
    SDL_Color color = {255, 0, 0, 255};
    while(! is_empty(temp)){
        sprite_t current_ennemy = value(temp) ;
        if(current_ennemy.HP > 0){
            display_life_bar(renderer, current_ennemy.dest_rect.x, current_ennemy.dest_rect.y - 5, SPRITE_WIDTH, 7, current_ennemy.HP, HP_INITIAL, color) ;
        }
        temp = next(temp) ;
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
    //life_bar des ennemy
    display_life_bar_ennemy(renderer, world->ennemis) ;
    // life_bar player
    SDL_Color color = {0, 0, 255, 255};
    display_life_bar(renderer, 5, 5, 2*PLATFORM_SIZE, PLATFORM_SIZE*3/4, world->player.HP, HP_INITIAL, color) ;
    // Afficher tout dans la fenÃªtre
    SDL_RenderPresent(renderer);
}