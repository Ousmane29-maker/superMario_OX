#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h> 
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
    // Initialiser la SDL et crÃ©er la fenÃªtre
    init_sdl(&fenetre, &ecran, nbCol*PLATFORM_SIZE, nbLig*PLATFORM_SIZE);
    //initialiser les ressources
    init_ressources(ecran, &ressources) ;
    // Initialiser le monde
    init_world(&world, "ressources/terrain.txt");

    //Boucle principale
    while (!is_game_over(&world)) {
        // GÃ©rer les Ã©vÃ©nements SDL
        handle_events(&world, &events);
        // Mise a jour des donnees
        update_data(&world, nbLig*PLATFORM_SIZE, nbCol*PLATFORM_SIZE);
        // RafraÃ®chissement de l'Ã©cran
        refresh_graphics(ecran, &world, &ressources) ;
        // pause de 20 ms a chaque tour de boucle pour bien gerer l'affichage
        SDL_Delay(20);
        // Attendre environ 1000 milliseconde apres la fin du jeu
        if(is_game_over(&world)){
            SDL_Delay(1000) ;
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
    liberer_liste(world.ennemis) ; 
    // Quitter SDL
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return 0;
}