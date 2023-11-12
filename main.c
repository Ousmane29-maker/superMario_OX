#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "world.h"
#include "display.h"


int main (){
   
    GameState gameState;
    SDL_Window* fenetre; // Déclaration de la fenêtre
    SDL_Renderer* ecran;
    SDL_Event evenements; // Événements liés à la fenêtre
    bool terminer = false;


    // allouer tableau 2D
    int line = 0;
    int colone = 0; 
    const char* nomF = "terrain.txt";
    taille_fichier(nomF, &line, &colone); //line et colone dynamique selone la taille du fichier
    char** tableauTerrain = allouer_tab_2D(line, colone);
    tableauTerrain = lire_fichier(nomF);
    afficher_tab_2D(tableauTerrain, line, colone);

    // initialiser la sdl et cree la fenêtre
    init_sdl(&fenetre, &ecran, colone*SPRITE_SIZE, line*SPRITE_SIZE) ; 

    // Charger l’image
    SDL_Texture* pavage = charger_image( "ressources/pavage.bmp", ecran );

    // Gestion des sprites
    int nbSpriteAffichagable = nbSpriteAffichage(line, colone);
    sprite_t* tabSprite = initialiser_tabSprite(tableauTerrain, line, colone) ;

    //inialisation du tableau de source sprites
    SDL_Rect *tableau_Src_Sprites = malloc(NOMBRE_TEXTURE * sizeof(SDL_Rect)) ;
    int x,y ;
    x = 0;
    y = 0;
    for(int i = 0; i < NOMBRE_TEXTURE; i++){
        tableau_Src_Sprites[i].x = x;
        tableau_Src_Sprites[i].y = y;
        tableau_Src_Sprites[i].h = SPRITE_SIZE ;
        tableau_Src_Sprites[i].w = SPRITE_SIZE ;
        x += SPRITE_SIZE; 
    }

    tableau_Src_Sprites[5].x = 0;
    tableau_Src_Sprites[5].y = SPRITE_SIZE;
    tableau_Src_Sprites[5].h = SPRITE_SIZE ;
    tableau_Src_Sprites[5].w = SPRITE_SIZE ;

    // initialisation et declaration du joueur
    // int w ;
    // int h ;
    SDL_Texture *obj = charger_image_transparente("ressources/Mario.bmp", ecran, 95,205,228) ;
    //Récupérer largeur et hargeur de la texture avec SDL_QueryTexture
    // SDL_QueryTexture(obj, NULL, NULL, &w, &h); 
    gameState.player.Src_Sprite.x = 1;
    gameState.player.Src_Sprite.y = 1;
    gameState.player.Src_Sprite.w = MARIO_WIDTH ;
    gameState.player.Src_Sprite.h = MARIO_HEIGHT ;
    gameState.player.Dest_Sprite.x = 0;
    gameState.player.Dest_Sprite.y = line*SPRITE_SIZE - SIZE_OBJ;
    gameState.player.Dest_Sprite.w = SIZE_OBJ;
    gameState.player.Dest_Sprite.h = SIZE_OBJ;
 
    //init data
    init_data(&gameState);

    // Boucle principale
    while(!terminer)
    {
        SDL_RenderClear(ecran);
        
        //copier les images des sprites dans le renderer
        SDL_RenderCopySprites(tabSprite,ecran,pavage,tableau_Src_Sprites,nbSpriteAffichagable) ;
        
        //copier le joueur dans le renderer
        SDL_RenderCopy(ecran, obj, &(gameState.player.Src_Sprite), &(gameState.player.Dest_Sprite)); 

        //show everything on the window
        SDL_RenderPresent(ecran);

        //gestion des évènements
        handle_events(&evenements, &gameState);


        //ne supprime pas!!!!!!
        /*
        SDL_PollEvent( &evenements );
        switch(evenements.type)
        {
        case SDL_QUIT:
            terminer = true;
            break;
        case SDL_KEYDOWN:
            switch(evenements.key.keysym.sym)
            {
            case SDLK_UP:
                DestR.y -= MOVE_STEP;
                break;
            case SDLK_DOWN:
                DestR.y += MOVE_STEP;
                break;
            case SDLK_LEFT:
                DestR.x -= MOVE_STEP;
                break;
            case SDLK_RIGHT:
                DestR.x += MOVE_STEP;
                break; 
            }   
        }

        Get a snapshot of the current state of the keyboard.
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_LEFT]){

            gameState.player.Dest_Sprite.x -= MOVE_STEP;

        }
        if(state[SDL_SCANCODE_RIGHT]){

            
            gameState.player.Dest_Sprite.x += MOVE_STEP;

        }

        if(state[SDL_SCANCODE_UP]){

            
            gameState.player.Dest_Sprite.y -= MOVE_STEP;

        }
        if(state[SDL_SCANCODE_DOWN]){

            
            gameState.player.Dest_Sprite.y += MOVE_STEP;

        }

        SDL_Delay(10);

        */

    }

    

    // Libérer de la mémoire
    SDL_DestroyTexture(pavage);
    SDL_DestroyTexture(obj);
    SDL_DestroyRenderer(ecran);
    free(tabSprite);
    free(tableau_Src_Sprites);
    desallouer_tab_2D(tableauTerrain, line);
    // Quitter SDL
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    
    return 0;
}





