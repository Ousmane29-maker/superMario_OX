#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h> 
#include "world.h"
#include "display.h"

int main() {
    SDL_Window *fenetre ; // Déclaration de la fenêtre
    SDL_Renderer *ecran ;
    SDL_Event events; // Événements liés à la fenêtre
    ressources_t ressources ;
    world_t world ;
    int nbLig, nbCol;
    taille_fichier("ressources/terrain.txt", &nbLig, &nbCol);
    // Initialiser la SDL et créer la fenêtre
    init_sdl(&fenetre, &ecran, nbCol*PLATFORM_SIZE, nbLig*PLATFORM_SIZE);
    //initialiser les ressources
    init_ressources(ecran, &ressources) ;
    // Initialiser le monde
    init_world(&world, "ressources/terrain.txt");

    //Boucle principale
    while (!is_game_over(&world)) {
        // Gérer les événements SDL
        handle_events(&world, &events);
        // Mise a jour des donnees
        update_data(&world, nbLig*PLATFORM_SIZE);
        // Rafraîchissement de l'écran
        refresh_graphics(ecran, &world, &ressources) ;
        // Attendre environ 5 millisecondes  
    }

    // Libérer la mémoire
    clean_ressources(&ressources);
    SDL_DestroyRenderer(ecran);
    desallouer_tab_2D(world.tab_terrain, nbLig);
    free(world.tab_platesFormes);
    free(world.player.walk_rects) ;
    free(world.player.walk_with_weapeon_rects) ;

    // Quitter SDL
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return 0;
}
