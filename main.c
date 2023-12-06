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
    //initialiser les ressources
    init_ressources(ecran, &ressources) ;
    // Initialiser le monde
    init_world(&world, "ressources/terrain.txt");
    //le menu
    SDL_RenderClear(ecran); 
    SDL_RenderCopy(ecran, ressources.menubackground,NULL, NULL);
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
                if(x >= world.tab_menu[0].dest_rect.x && x <= world.tab_menu[0].dest_rect.x + world.tab_menu[0].dest_rect.w &&
                    y <= world.tab_menu[0].dest_rect.y + world.tab_menu[0].dest_rect.h && y >= world.tab_menu[0].dest_rect.y){
                    while(!is_game_over(&world)){
                        handle_events(&world, &events);
                        // Mise a jour des donnees
                        update_data(&world, nbLig*PLATFORM_SIZE, nbCol*PLATFORM_SIZE);
                        refresh_graphics(ecran, &world, &ressources) ;
                        // pause de 20 ms a chaque tour de boucle pour bien gerer l'affichage
                        SDL_Delay(20);
                        // Attendre environ 1000 milliseconde apres la fin du jeu
                        if(is_game_over(&world)){
                            handle_hightScore("ressources/hightScore.txt", &world.player) ;
                            SDL_Delay(1000) ;
                        }
                    }
                                    
                                    
                }
                if(x >= world.tab_menu[1].dest_rect.x && x <= world.tab_menu[1].dest_rect.x + world.tab_menu[1].dest_rect.w &&
                    y <= world.tab_menu[1].dest_rect.y + world.tab_menu[1].dest_rect.h && y >= world.tab_menu[1].dest_rect.y){
                                    
                        world.gameOver = 1;
                }
                        
                SDL_Log("mouse down(x:%d, y:%d)", events.button.x, events.button.y);
                break;

        }

    }

     // LibÃ©rer la mÃ©moire
    clean_ressources(&ressources);
    SDL_DestroyRenderer(ecran);
    desallouer_tab_2D(world.tab_terrain, nbLig);
    free(world.tab_platesFormes);
    free(world.tab_coins);
    free(world.player.walk_rects) ;
    free(world.player.walk_with_weapeon_rects) ;
    free(world.player.jump_rects) ;
    free(world.player.attack_rects) ;
    free(world.player.attack_with_weapeon_rects) ;
    free(world.tab_menu);
    liberer_liste(world.ennemis) ; 
    // Quitter SDL
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return 0;
}