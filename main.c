#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "fonctions_fichiers.h"

int main (){
    // const char* nomFichier = "tabChiffres.txt";
    // int line;
    // int colone; 
    // taille_fichier(nomFichier, &line, &colone);
    // printf("creer un tableau 2D\n");
    // char** T = allouer_tab_2D(line,colone);
    // printf("lire un fichier\n");
    // T = lire_fichier(nomFichier);
    // printf("affiche un tableau 2D:\n");
    // afficher_tab_2D(T,line,colone);
    // printf("test la fonction modifier_caractere:\n");
    // // modifier_caractere(T, line, colone,'1','a');
    // afficher_tab_2D(modifier_caractere(T, line, colone,'1','a'),line,colone);
    // char** tab = allouer_tab_2D(line,colone);
    
   
    SDL_Window* fenetre; // Déclaration de la fenêtre
    SDL_Event evenements; // Événements liés à la fenêtre
    bool terminer = false;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
    {
        printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // allouer tableau 2D
    int line = 0;
    int colone = 0; 
    const char* nomF = "terrain.txt";
    taille_fichier(nomF, &line, &colone); //line et colone dynamique selone la taille du fichier
    char** tableauTerrain = allouer_tab_2D(line, colone);
    tableauTerrain = lire_fichier(nomF);
    afficher_tab_2D(tableauTerrain, line, colone);

    // Créer la fenêtre
    fenetre = SDL_CreateWindow("Mon Jeu", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, colone*SPRITE_SIZE, line*SPRITE_SIZE, SDL_WINDOW_RESIZABLE);
    if(fenetre == NULL) // En cas d’erreur
    {
        printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Mettre en place un contexte de rendu de l’écran
    SDL_Renderer* ecran;
    ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    // Charger l’image
    SDL_Texture* pavage = charger_image( "pavage.bmp", ecran );

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

    // initialisation et declaration du joueur
    int w ;
    int h ;
    SDL_Texture *obj = charger_image_transparente("sprites.bmp", ecran, 0, 255, 255) ;
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
        SDL_RenderCopySprites(tabSprite,ecran,pavage,tableau_Src_Sprites,nbSpriteAffichagable) ;
        
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
    free(tabSprite);
    free(tableau_Src_Sprites);
    desallouer_tab_2D(tableauTerrain, line);
    // Quitter SDL
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    
    return 0;
}





