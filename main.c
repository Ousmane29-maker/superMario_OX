#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_ttf.h>
#include "world.h"
#include "display.h"

int main() {
    SDL_Window *fenetre ; // DÃ©claration de la fenÃªtre
    SDL_Renderer *ecran ;
    SDL_Event events; // Ã‰vÃ©nements liÃ©s Ã  la fenÃªtre
    ressources_t ressources ;
    world_t world ;
    int nbLig, nbCol;
    taille_fichier("ressources/terrain.txt", &nbLig, &nbCol);
    if(nbLig < 10|| nbCol < 10){
        printf("la taille du fichier est trop petite : 10/10 minimum") ;
        exit(EXIT_FAILURE) ;

    }
    // Initialiser la SDL et crÃ©er la fenÃªtre
    init_sdl(&fenetre, &ecran, nbCol*PLATFORM_SIZE, nbLig*PLATFORM_SIZE);
    //initialiser le font
    init_ttf();
    //initialiser les ressources
    init_ressources(ecran, &ressources) ;
    // initialiser le monde
    init_world(&world, "ressources/terrain.txt");
    
    SDL_RenderClear(ecran); 
    //le menu background
    SDL_RenderCopy(ecran, ressources.menubackground,NULL, NULL);
    //le menu
    SDL_RenderCopyMenu(ecran, ressources.menu, world.tab_menu);
    SDL_RenderPresent(ecran);

                    
    //Boucle principale
    while (!is_game_over(&world)) {
        SDL_PollEvent( &events );
        int x, y;
        switch(events.type){
            case SDL_QUIT:
                world.gameOver = 1;
                break;
            
            case SDL_MOUSEBUTTONDOWN:                    
                x = events.button.x;
                y = events.button.y;

                //check if the mouse clicked on the play button
                if(x >= world.tab_menu[0].dest_rect.x && x <= world.tab_menu[0].dest_rect.x + world.tab_menu[0].dest_rect.w &&
                    y <= world.tab_menu[0].dest_rect.y + world.tab_menu[0].dest_rect.h && y >= world.tab_menu[0].dest_rect.y){
                    while(!is_game_over(&world)){
                        //gerer event
                        handle_events(&world, &events);
                        // Mise a jour des donnees
                        update_data(&world, nbLig*PLATFORM_SIZE, nbCol*PLATFORM_SIZE);
                        //refresh graphics
                        refresh_graphics(ecran, &world, &ressources, nbCol*PLATFORM_SIZE) ;
                        // pause de 20 ms a chaque tour de boucle pour bien gerer l'affichage
                        SDL_Delay(20);
                        // Attendre environ 1000 milliseconde apres la fin du jeu
                        if(is_game_over(&world)){
                            handle_hightScore("ressources/hightScore.txt", &world.player, world.tab_Score) ;
                            SDL_Delay(1000) ;
                        }
                    }

                    print_end_game(ecran, &world, &ressources) ;               
                                    
                }
                world.gameOver = 0;
                //check if the mouse clicked in the exit button
                if(x >= world.tab_menu[2].dest_rect.x && x <= world.tab_menu[2].dest_rect.x + world.tab_menu[2].dest_rect.w &&
                    y <= world.tab_menu[2].dest_rect.y + world.tab_menu[2].dest_rect.h && y >= world.tab_menu[2].dest_rect.y){
                                    
                        world.gameOver = 1;
                }
                //check if the mouse clicked on the play button
                if(x >= world.tab_menu[0].dest_rect.x && x <= world.tab_menu[0].dest_rect.x + world.tab_menu[0].dest_rect.w &&
                    y <= world.tab_menu[0].dest_rect.y + world.tab_menu[0].dest_rect.h && y >= world.tab_menu[0].dest_rect.y){
                            clean_world(&world, nbLig) ;
                            init_world(&world, "ressources/terrain.txt");
                }
                 //check if the mouse clicked on the scores button     
                if(x >= world.tab_menu[1].dest_rect.x && x <= world.tab_menu[1].dest_rect.x + world.tab_menu[1].dest_rect.w &&
                    y <= world.tab_menu[1].dest_rect.y + world.tab_menu[1].dest_rect.h && y >= world.tab_menu[1].dest_rect.y){
                    handle_hightScore("ressources/hightScore.txt", &world.player, world.tab_Score) ;
                    printScore(ecran, &world, &ressources);
                } 
                break;
        }

    }

     // LibÃ©rer la mÃ©moire et quitter sdl
    clean_up(&world, &ressources, ecran, fenetre, nbLig) ;

    return 0;
}