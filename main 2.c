#include <stdlib.h>
#include <stdio.h>
#include "fonction_fichier.h"
#include <stdbool.h>

int main(){

    SDL_Window* fenetre; // Déclaration de la fenêtre
    SDL_Event evenements; // Événements liés à la fenêtre
    bool terminer = false;

    int nblig = 0 ;
    int nbCol = 0  ;
    taille_fichier("terrain.txt",&nblig,&nbCol) ;
    char ** tabTerrain = lire_fichier("terrain.txt") ;
    afficher_tab_2D(tabTerrain, nblig, nbCol) ;
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
    {
        printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    // Créer la fenêtre
    fenetre = SDL_CreateWindow("Mon jeu", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, nbCol * TAILLE_SPRITES , nblig * TAILLE_SPRITES, SDL_WINDOW_RESIZABLE); // on adapte la taille en fonction du fichier d'entree
    if(fenetre == NULL) // En cas d’erreur
    {
        printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    // Mettre en place un contexte de rendu de l’écran
    SDL_Renderer* ecran;
    ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    // Charger l’image
    //SDL_Texture* fond = charger_image( "fond.bmp", ecran ) ;
    SDL_Texture* pavage = charger_image("pavage.bmp", ecran) ;

    // Gestion des sprites
    int nbrCaractAffichable = nbrCaracteresAffichable(tabTerrain, nblig, nbCol) ;
    sprite_t* tabSprite = creer_Initialiser_tabSprites(tabTerrain, nblig, nbCol) ;
    //inialisation du tableau de source sprites
    SDL_Rect *tableau_Src_Sprites = malloc(NOMBRE_TEXTURE * sizeof(SDL_Rect)) ;
    int x,y ;
    x = 0;
    y = 0;
    for(int i = 0; i < 5; i++){
        tableau_Src_Sprites[i].x = x;
        tableau_Src_Sprites[i].y = y;
        tableau_Src_Sprites[i].h = TAILLE_SPRITES ;
        tableau_Src_Sprites[i].w = TAILLE_SPRITES ;
        x = x + TAILLE_SPRITES ; 
    }
    tableau_Src_Sprites[5].x = 0;
    tableau_Src_Sprites[5].y = TAILLE_SPRITES;
    tableau_Src_Sprites[5].h = TAILLE_SPRITES ;
    tableau_Src_Sprites[5].w = TAILLE_SPRITES ;

    tableau_Src_Sprites[6].x = 0;
    tableau_Src_Sprites[6].y = TAILLE_SPRITES * 4;
    tableau_Src_Sprites[6].h = TAILLE_SPRITES ;
    tableau_Src_Sprites[6].w = TAILLE_SPRITES ;

    // initialisation et declaration du joueur
    SDL_Texture *Mario = charger_image_transparente("player.bmp", ecran, 254, 254, 254);
    SDL_Rect *tabJoueur_Src = malloc(5 * sizeof(SDL_Rect)) ;
    tabJoueur_Src[0].x = 72;
    tabJoueur_Src[0].y = 40;
    tabJoueur_Src[0].w =  112;
    tabJoueur_Src[0].h = 124;

    tabJoueur_Src[1].x = 253;
    tabJoueur_Src[1].y = 30;
    tabJoueur_Src[1].w =  79;
    tabJoueur_Src[1].h = 130;

    tabJoueur_Src[2].x = 408;
    tabJoueur_Src[2].y = 30;
    tabJoueur_Src[2].w =  95;
    tabJoueur_Src[2].h = 138;

    tabJoueur_Src[3].x = 563;
    tabJoueur_Src[3].y = 30;
    tabJoueur_Src[3].w =  123;
    tabJoueur_Src[3].h = 135;

    tabJoueur_Src[4].x = 722;
    tabJoueur_Src[4].y = 30;
    tabJoueur_Src[4].w =  137;
    tabJoueur_Src[4].h = 132;

    SDL_Rect DestJoueur ;
    DestJoueur.x = 0;
    DestJoueur.y = (nblig * TAILLE_SPRITES - TAILLE_SPRITES) - 50; // (hauteur ecran - taille sprite) = tete - taille joueur
    DestJoueur.w = 50;
    DestJoueur.h = 50 ;
    //fond
    SDL_Texture* fond = charger_image("fond.bmp",ecran) ; 
    //end game
    SDL_Texture* end_Game = charger_image_transparente("endGame.bmp", ecran, 230,230,230) ;  
    SDL_Rect Dest_end_Game ;
    Dest_end_Game.x = nbCol * TAILLE_SPRITES - 2*TAILLE_SPRITES ;
    Dest_end_Game.y =  4;
    Dest_end_Game.w =  60;
    Dest_end_Game.h =  60;

    // Boucle principale
    bool saut = false ;
    int compteur = 0 ;
    int animation = 0 ;
    int graviteSaut = 0 ;
    SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;   // effet mirroir
    int droite = 1 ;
    while(!terminer){
        SDL_RenderClear(ecran);
        //copier le fond
        SDL_RenderCopy(ecran,fond,NULL,NULL) ;
       // SDL_RenderCopy(ecran,pavage,&tableau_Src_Sprites[0],NULL) ;
       //copier enGame
        SDL_RenderCopy(ecran,end_Game,NULL,&Dest_end_Game) ;
        //SDL_RenderCopy(ecran,pavage,&tableauSprites[3],&tableauSprites[0]) ;
    
        //copier les images des sprites dans le renderer
        SDL_RenderCopySprites(tabSprite,ecran,pavage,tableau_Src_Sprites,nbrCaractAffichable) ;
        
        //copier image du joueur dans le renderer
        if(droite == 1){
            SDL_RenderCopy(ecran,Mario,&tabJoueur_Src[animation],&DestJoueur) ;
        }else{
            SDL_RenderCopyEx(ecran, Mario, &tabJoueur_Src[animation],&DestJoueur, 0, NULL, flip);
        }

        //
        SDL_RenderPresent(ecran) ;
        //Gestion des evenements
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
                    saut = true;
                    compteur = 5 ;
                    animation = 2 ; //saut
                break;
            case SDLK_DOWN:
                if(!OnTheland(DestJoueur,tabSprite, nbrCaractAffichable)){
                    if (DestJoueur.y + MOVE_STEP < nblig * TAILLE_SPRITES - TAILLE_JOUEUR) {
                        DestJoueur.y = DestJoueur.y + MOVE_STEP;
                    }               
                }
                break;
            case SDLK_LEFT:
                DestJoueur.x = DestJoueur.x - 10;
                animation ++ ;
                droite = 0 ;
                break;
            case SDLK_RIGHT:
                DestJoueur.x = DestJoueur.x + 10;
                animation ++ ;
                droite = 1 ;
                break; 
            }   
        }
        if(saut == false){
            if(!OnTheland(DestJoueur,tabSprite, nbrCaractAffichable)){
                if (DestJoueur.y + MOVE_STEP < nblig * TAILLE_SPRITES - TAILLE_JOUEUR) {
                    DestJoueur.y = DestJoueur.y + 5;
                    if(graviteSaut >0){
                        if(droite == 1){
                            DestJoueur.x = DestJoueur.x + 4;
                        }else{
                            DestJoueur.x = DestJoueur.x - 4;
                        }
                    }
                }
            }
        }
        if(compteur > 0){
            DestJoueur.y = DestJoueur.y - 12;
            if(droite == 1){
                DestJoueur.x = DestJoueur.x + 7;
            }else{
                DestJoueur.x = DestJoueur.x - 7;
            }
            compteur -- ;
        }else{
            saut = false ;
            graviteSaut = 5 ;
        }
        if(animation == 5){
            animation = 0;
        }
        if(graviteSaut > 0){
            graviteSaut -- ;
        }
        SDL_Delay(60); // faire une pause de 60 ms
       
    }

    SDL_DestroyTexture(pavage);
    SDL_DestroyTexture(Mario);
    SDL_DestroyRenderer(ecran);
    free(tableau_Src_Sprites);
    free(tabSprite) ;
    desallouer_tab_2D(tabTerrain, nblig) ;

    // Quitter SDL
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}


