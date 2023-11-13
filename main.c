#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h> 
#include "world.h"
#include "display.h"

int main() {
    SDL_Window *fenetre; // Déclaration de la fenêtre
    SDL_Renderer *ecran;
    SDL_Event evenements; // Événements liés à la fenêtre
    ressources_t ressources;
    world_t world;
   
    int nbLig, nbCol;
    taille_fichier("ressources/terrain.txt", &nbLig, &nbCol);
    // Initialiser la SDL et créer la fenêtre
    init_sdl(&fenetre, &ecran, nbCol*PLATFORM_SIZE, nbLig*PLATFORM_SIZE);
    //initialiser les ressources
    init_ressources(ecran, &ressources) ;
    // Initialiser le monde
    init_world(&world, ressources.terrain);

    //Boucle principale
    while (!is_game_over(&world)) {
        SDL_RenderClear(ecran);

        // le fond
        SDL_RenderCopy(ecran, ressources.background,NULL, NULL);

        // Copier les platformes dans le renderer
        SDL_RenderCopyPlateFormes(&world, ecran, ressources.pavage, world.nbPlateForme);

        // Copier le joueur dans le renderer
        SDL_RenderCopy(ecran, ressources.playerTexture, &(world.player.walk_rects[world.player.current_frame_walk]), &(world.player.dest_rect));

        // Afficher tout dans la fenêtre
        SDL_RenderPresent(ecran);

        //gestion des évènements
        handle_events(&evenements, &world);

        //mise à jour des données liée à la physique du monde
        update_data(&world, nbLig*PLATFORM_SIZE);

        SDL_Delay(16); // Attendre environ 16 millisecondes (pour viser environ 60 images par seconde)
    }

    // Libérer la mémoire
    clean_ressources(&ressources);
    SDL_DestroyRenderer(ecran);
    desallouer_tab_2D(world.tab_terrain, nbLig);
    free(world.tab_platesFormes);

    // Quitter SDL
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return 0;
}
