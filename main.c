#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "world.h"
#include "display.h"


int main (){
   
    SDL_Window* fenetre; // Déclaration de la fenêtre
    SDL_Renderer* ecran;
    SDL_Event evenements; // Événements liés à la fenêtre
    bool terminer = false;
    world_t world ; 

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
    world.tab_platesFormes = initialiser_tabSprite(tableauTerrain, line, colone) ;

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

    // initialisation et declaration du joueur
    int w ;
    int h ;
    SDL_Texture *obj = charger_image_transparente("ressources/sprites.bmp", ecran, 0, 255, 255) ;
    //Récupérer largeur et hargeur de la texture avec SDL_QueryTexture
    SDL_QueryTexture(obj, NULL, NULL, &w, &h); 
    SDL_Rect SrcR, DestR;
    SrcR.x = 0;
    SrcR.y = 0;
    SrcR.w = w/3 ;
    SrcR.h = h/2 ;
    DestR.x = 0;
    DestR.y = 0;
    DestR.w = SIZE_OBJ;
    DestR.h = SIZE_OBJ;


    // Boucle principale
    while(!terminer)
    {
        SDL_RenderClear(ecran);
        
        //copier les images des sprites dans le renderer
        SDL_RenderCopySprites(world.tab_platesFormes,ecran,pavage,tableau_Src_Sprites,nbSpriteAffichagable) ;
        
        //copier le joueur dans le renderer
        SDL_RenderCopy(ecran, obj, &SrcR, &DestR); 

        //show everything on the window
        SDL_RenderPresent(ecran);

        //SDL_PollEvent ...
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
    }

    

    // Libérer de la mémoire
    SDL_DestroyTexture(pavage);
    SDL_DestroyTexture(obj);
    SDL_DestroyRenderer(ecran);
    free(tableau_Src_Sprites);
    desallouer_tab_2D(tableauTerrain, line);
    // Quitter SDL
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    
    return 0;
}





