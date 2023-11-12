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


void SDL_RenderCopySprites(sprite_t* tabSprite, SDL_Renderer* ecran, SDL_Texture* pavage, SDL_Rect* tableau_Src_Sprites,int nbSpriteAffichage){
    for(int i = 0; i < nbSpriteAffichage; i++){
        switch (tabSprite[i].caractere)
        {    case ' ':
                SDL_RenderCopy(ecran,pavage,&tableau_Src_Sprites[0], &tabSprite[i].Dest_Sprite) ;
                break;
            case '0' :
                SDL_RenderCopy(ecran,pavage,&tableau_Src_Sprites[0], &tabSprite[i].Dest_Sprite) ;
                break;
            case '1':
                SDL_RenderCopy(ecran,pavage,&tableau_Src_Sprites[1], &tabSprite[i].Dest_Sprite) ;
                break;
            case '2':
                SDL_RenderCopy(ecran,pavage,&tableau_Src_Sprites[2], &tabSprite[i].Dest_Sprite) ;
                break;
            case '3':
                SDL_RenderCopy(ecran,pavage,&tableau_Src_Sprites[3], &tabSprite[i].Dest_Sprite) ;
                break;
            case '4':
                SDL_RenderCopy(ecran,pavage,&tableau_Src_Sprites[4], &tabSprite[i].Dest_Sprite) ;
                break;  
            case '5':
                SDL_RenderCopy(ecran,pavage,&tableau_Src_Sprites[5], &tabSprite[i].Dest_Sprite) ;
                break;   
        }
    }
}

void init_data (GameState* gameState){
    //on n'est pas à la fin du jeu
    gameState->gameover = 0;
}


void handle_events(SDL_Event *event, GameState *gameState){
    // int done= 0;
    // while(SDL_PollEvent(event)){
    //     switch(event.type){
    //         case SDL_WINDOWEVENT_CLOSE:

    //     }

    SDL_PollEvent(event);
    
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if(state[SDL_SCANCODE_LEFT]){

        gameState->player.Dest_Sprite.x -= MOVE_STEP;

    }
    if(state[SDL_SCANCODE_RIGHT]){

            
        gameState->player.Dest_Sprite.x += MOVE_STEP;

    }

    if(state[SDL_SCANCODE_UP]){

            
        gameState->player.Dest_Sprite.y -= MOVE_STEP;

    }
    if(state[SDL_SCANCODE_DOWN]){

            
        gameState->player.Dest_Sprite.y += MOVE_STEP;

    }

    
}
