#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "world.h"


/**
* @param int n
* @param int m
* @return allouer un tableau de caractÃ¨res de taille n Ã— m, oÃ¹ n et m sont les nombres de lignes et de colonnes, 
* et initialiser ce tableau avec le caractÃ¨re espace (â€™ â€™).
*/
char** allouer_tab_2D(int n, int m){

    char** tab = malloc(n * sizeof(char*));
    if(tab == NULL){
        exit(EXIT_FAILURE);
    }
    for(int i= 0; i < n; i++){
        tab[i] = malloc(m * sizeof(char));
    }
    for(int j = 0; j < n; j++){
        for(int k = 0; k < m; k++){
            tab[j][k] = ' ';
        }
    }
    return tab;

}

/**
* @param int n
* @param int m
* libÃ©rer un tableau Ã  deux dimensions, de n lignes.
*/
void desallouer_tab_2D(char** tab, int n){
    for(int i = 0; i < n; i++){
        free(tab[i]);
    }
    free(tab);
    tab = NULL;
}

/**
* @param 2D tableau char** tab
* @param int n
* @param int m
* afficherlecontenudâ€™un tableau de caractÃ¨res de taille n Ã— m.
*/
void afficher_tab_2D(char** tab, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            printf("%c ", tab[i][j]);
        }
        printf("\n");
    }
}

/**
* @param const char* nomFichier
* @param int* nbLig
* @param int* nbCol
* compter le nombre max de lignes (nbLig) et de colonnes (nbCol) dans le fichier dont le nom est nomFichier.
*/
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol){
    *nbLig = 0 ;
    *nbCol = 0 ;
    int nbColAct = 0 ;
    char c = ' ' ;
    FILE *fic =fopen(nomFichier,"r") ;
    if(fic == NULL){
        perror("Error opening file") ;
    }else{
        c = fgetc(fic) ;
        while(c != EOF){
            // si on est pas a la fin du fichier 
            if(c == '\n'){ //on considere que '\n' est un caractere
                *nbLig = *nbLig + 1 ; // a la fin de la ligne on incremente le nombre de ligne 
                *nbCol = (*nbCol > nbColAct) ? *nbCol : nbColAct; // le nombre de colonne est egale au maximum du nombre de colonne precedent et celui d'actuel
                nbColAct = 0 ; // on remet le compteur a 0
            }else if (c != '\r') {
                nbColAct ++ ;
            }
            c = fgetc(fic) ;
        }
        // VÃ©rifier si la derniÃ¨re ligne se termine par un retour Ã  la ligne
        if (nbColAct > 0) {
            *nbLig = *nbLig + 1;
            *nbCol = (*nbCol > nbColAct) ? *nbCol : nbColAct ;

        }
    }
    fclose(fic) ;
}



char** lire_fichier(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", nomFichier);
        return NULL;
    }
    int nbLig, nbCol;
    taille_fichier(nomFichier, &nbLig, &nbCol);
    char** tab = allouer_tab_2D(nbLig, nbCol);
    if (tab == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation du tableau.\n");
        fclose(fichier);
        return NULL;
    }
    
    int ligne = 0;
    int colonne = 0;
    int c;
    while ((c = fgetc(fichier)) != EOF) {
        if (c == '\n' || c == '\r') {
            if(colonne != 0){
                ligne++;
                colonne = 0;
            }
        } else {
            tab[ligne][colonne] = c;
            colonne++;
        }

    }      
    fclose(fichier);
    return tab;
}

char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau){
    char** T = allouer_tab_2D(n, m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(tab[i][j] == ancien){

                T[i][j] = nouveau;
            }
            else{
                T[i][j] = tab[i][j];
            }
        }
    }
    return T;
    
}


void ecrire_fichier(const char* nomFichier, char** tab, int n, int m){
    FILE* fichier = NULL;
    fichier = fopen(nomFichier, "w");
    if(fichier != NULL){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                fputc(tab[i][j], fichier);
            }
            fputc('\n', fichier);
        }
        
        fclose(fichier);
        
    }
}

void ecrire_fichier_heightScore(const char* nomFichier, int tableau[]){
    FILE *fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        perror("Error opening file") ;
    }else{
        for(int i = 0; i < TAILLE_TABLEAU_SCORE; i++){
            fprintf(fichier,"%d\n", tableau[i]) ;
        }
    }
    fclose(fichier);

}
void lire_heightScore(const char* nomFichier, int tableau[]){
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Error opening file") ;
    }else{
        int entier;
        int indice = 0;
        // Lire jusqu'à la fin du fichier et  remplir le tableau
        while (fscanf(fichier, "%d", &entier) == 1 && indice < TAILLE_TABLEAU_SCORE) {
            tableau[indice] = entier;
            indice++;
        }
    }
    fclose(fichier);

}

int nbrPlateformes(char** tab_terrain, int n, int m){
    int compteur = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){ //les plateformes c'est de 1 a 6
            if(tab_terrain[i][j] == '1' || tab_terrain[i][j] == '2' || tab_terrain[i][j] == '3'|| tab_terrain[i][j] == '4' || tab_terrain[i][j] == '5' || tab_terrain[i][j] == '6'){
                compteur++;
            }
        }
    }
    return compteur;
}


int nbrPieces(char** tab_terrain, int n, int m){
    int compteur = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){ //les plateformes c'est de 1 a 6
            if(tab_terrain[i][j] == '7'){
                compteur++;
            }
        }
    }
    return compteur;
}

SDL_Rect* init_tab_src_pavage(){
    SDL_Rect *tab_src = malloc(NOMBRE_TEXTURE_PLATFORM * sizeof(SDL_Rect)) ;
    int x,y ;
    y = 0;
    x = PLATFORM_SIZE; // On ignore la premiere (le vert)
    for(int i = 0; i < NOMBRE_TEXTURE_PLATFORM - 1; i++){
        tab_src[i].x = x;
        tab_src[i].y = y;
        tab_src[i].h = PLATFORM_SIZE ;
        tab_src[i].w = PLATFORM_SIZE ;
        x += PLATFORM_SIZE; 
    }
    tab_src[5].x = 0;
    tab_src[5].y = PLATFORM_SIZE;
    tab_src[5].h = PLATFORM_SIZE ;
    tab_src[5].w = PLATFORM_SIZE ;
    return tab_src ;
}

void init_src_rect_tab_plateFormes(char ** tab_terrain, int n, int m, fixedSprite_t* tab_plateFormes){
    SDL_Rect *tab_src = init_tab_src_pavage() ;
    int indice_PlateForme = 0 ;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            switch (tab_terrain[i][j])
            {
            case '1' :
                tab_plateFormes[indice_PlateForme].src_rect = tab_src[0];
                indice_PlateForme ++ ;
                break;
            case '2' :
                tab_plateFormes[indice_PlateForme].src_rect = tab_src[1];
                indice_PlateForme ++ ;
                break;
            case '3' :
                tab_plateFormes[indice_PlateForme].src_rect = tab_src[2];
                indice_PlateForme ++ ;
                break;
            case '4' :
                tab_plateFormes[indice_PlateForme].src_rect = tab_src[3];
                indice_PlateForme ++ ;
                break;
            case '5' :
                tab_plateFormes[indice_PlateForme].src_rect = tab_src[4];
                indice_PlateForme ++ ;
                break;
            case '6' :
                tab_plateFormes[indice_PlateForme].src_rect = tab_src[5];
                indice_PlateForme ++ ;
                break;                                        
            }
        }
    }
    free(tab_src) ;
}

void init_dest_rect_tab_plateFormes(char ** tab_terrain, int n, int m, fixedSprite_t* tab_plateFormes){
    int x,y,indice_PlateForme ;
    y = 0;
    indice_PlateForme = 0;
    for(int i = 0; i < n; i++){
        x = 0;
        for(int j = 0; j < m; j++){
            if(tab_terrain[i][j] == '1' || tab_terrain[i][j] == '2' || tab_terrain[i][j] == '3'|| tab_terrain[i][j] == '4' || tab_terrain[i][j] == '5' || tab_terrain[i][j] == '6'){
                tab_plateFormes[indice_PlateForme].dest_rect.x = x;
                tab_plateFormes[indice_PlateForme].dest_rect.y = y;
                tab_plateFormes[indice_PlateForme].dest_rect.w = PLATFORM_SIZE;
                tab_plateFormes[indice_PlateForme].dest_rect.h = PLATFORM_SIZE;
                indice_PlateForme++;
            }
            x += PLATFORM_SIZE;
        }
        y += PLATFORM_SIZE;    
    }

}

void init_tab_platesFormes(fixedSprite_t* tab_plateFormes, char ** tab_terrain, int n, int m){
    // int nbre_plateforme = nbrPlateformes(tab_terrain) ;
    //tab_plateFormes = (platform_t*) malloc(nbre_plateforme * sizeof(platform_t)) ;
    init_src_rect_tab_plateFormes(tab_terrain, n, m, tab_plateFormes);
    init_dest_rect_tab_plateFormes(tab_terrain, n, m, tab_plateFormes) ;
}

void init_sprite(sprite_t *sprite, double x, double y, int w, int h,int weapon) {
    sprite->weapeon = weapon ;
    sprite->current_frame_walk = 0 ;
    sprite->vers_la_droite = 1 ;
    sprite->current_frame_jump = 0 ;
    sprite->nbPieceRamasse = 0 ;
    sprite->current_frame_attack = 0 ;
    sprite->current_frame_attack_with_weapeon = 0 ;
    sprite->current_frame_death = 0 ;
    sprite->is_attacking = 0 ;
    sprite->HP = HP_INITIAL ;
    sprite->lastAttackTime = SDL_GetTicks();

    sprite->walk_rects = malloc(NOMBRE_FRAMES_WALK * sizeof(SDL_Rect)) ;
    int x_src , y_src ;
    x_src = 20 ;
    y_src = 11 * (IMAGE_SPRITE_HEIGHT + 15 ) ; // la 11eme ligne dans l'image du joueur (15 pixel entre chaque ligne)
    for(int i = 0 ; i <  NOMBRE_FRAMES_WALK; i++){
        sprite->walk_rects [i].x = x_src ;
        sprite->walk_rects [i].y = y_src ;
        sprite->walk_rects [i].w = IMAGE_SPRITE_WIDTH;
        sprite->walk_rects [i].h = IMAGE_SPRITE_HEIGHT;
        x_src = x_src + 64 ;
    }

    sprite->walk_with_weapeon_rects = malloc(NOMBRE_FRAMES_WALK * sizeof(SDL_Rect)) ;
    x_src = 45 ;
    y_src = 1770 ;
    for(int i = 0 ; i < NOMBRE_FRAMES_WALK; i++){
        sprite->walk_with_weapeon_rects [i].x = x_src ;
        sprite->walk_with_weapeon_rects [i].y = y_src ;
        sprite->walk_with_weapeon_rects [i].w = IMAGE_ARMED_SPRITE_WIDTH;
        sprite->walk_with_weapeon_rects [i].h = IMAGE_SPRITE_HEIGHT;
        x_src = x_src + 129 ;
    }

    sprite->jump_rects = malloc(NOMBRE_FRAMES_JUMP * sizeof(SDL_Rect)) ;
    x_src = 20 ;
    y_src = 206 ;
    for(int i = 0 ; i < NOMBRE_FRAMES_JUMP; i++){
        sprite->jump_rects [i].x = x_src ;
        sprite->jump_rects [i].y = y_src ;
        sprite->jump_rects [i].w = IMAGE_SPRITE_WIDTH ;
        sprite->jump_rects [i].h = IMAGE_SPRITE_HEIGHT;
        x_src = x_src + 64 ;
    }
    
    sprite->attack_rects = malloc(NOMBRE_FRAMES_ATTACK * sizeof(SDL_Rect)) ;
    x_src = 20 ;
    y_src = 1227 ; //
    for(int i = 0 ; i < NOMBRE_FRAMES_ATTACK; i++){
        sprite->attack_rects [i].x = x_src ;
        sprite->attack_rects [i].y = y_src ;
        sprite->attack_rects [i].w = IMAGE_SPRITE_WIDTH ;
        sprite->attack_rects [i].h = IMAGE_SPRITE_HEIGHT;
        x_src = x_src + 64 ;
    }
    sprite->attack_with_weapeon_rects = malloc(NOMBRE_FRAMES_ATTACK_WITH_WEAPEON * sizeof(SDL_Rect)) ;
    x_src = 45 ;
    y_src = 2285 ; // 
    for(int i = 0 ; i < NOMBRE_FRAMES_ATTACK_WITH_WEAPEON; i++){
        sprite->attack_with_weapeon_rects [i].x = x_src ;
        sprite->attack_with_weapeon_rects [i].y = y_src ;
        sprite->attack_with_weapeon_rects [i].w = IMAGE_ARMED_SPRITE_WIDTH ;
        sprite->attack_with_weapeon_rects [i].h = IMAGE_SPRITE_HEIGHT;
        x_src = x_src + 129 ;
    }

    sprite->death_rects = malloc(NOMBRE_FRAMES_DEATH * sizeof(SDL_Rect)) ;
    x_src = 20 ;
    y_src = 1290 ; // 
    for(int i = 0 ; i < NOMBRE_FRAMES_DEATH; i++){
        sprite->death_rects [i].x = x_src ;
        sprite->death_rects [i].y = y_src ;
        sprite->death_rects [i].w = IMAGE_SPRITE_WIDTH ;
        sprite->death_rects [i].h = IMAGE_SPRITE_HEIGHT;
        x_src = x_src + 64 ;
    }

    //destination
    sprite->dest_rect.x = x ;
    sprite->dest_rect.y = y ;
    sprite->dest_rect.w = w;
    sprite->dest_rect.h = h ;

}

void init_end_Level(fixedSprite_t *endLevel, double x, double y){
    endLevel->dest_rect.x = x ;
    endLevel->dest_rect.y = y ;
    endLevel->dest_rect.w = ENDLEVEL_WIDTH ;
    endLevel->dest_rect.h = ENDLEVEL_HEIGHT ;
}

void init_tab_coins(char ** tab_terrain, int n, int m, fixedSprite_t* tab_coins){
    int x,y,indice_Piece ;
    y = 0;
    indice_Piece = 0;
    for(int i = 0; i < n; i++){
        x = 0;
        for(int j = 0; j < m; j++){
            if(tab_terrain[i][j] == '7'){
                tab_coins[indice_Piece].dest_rect.x = x;
                tab_coins[indice_Piece].dest_rect.y = y;
                tab_coins[indice_Piece].dest_rect.w = PIECE_SIZE;
                tab_coins[indice_Piece].dest_rect.h = PIECE_SIZE;
                indice_Piece++;
            }
            x += PLATFORM_SIZE;
        }
        y += PLATFORM_SIZE;    
    }
}

int generateRandomNumber(int a, int b) {
    return rand() % (b - a + 1) + a;
}

liste init_ennemis_level1(int screenWidth, int screenHeight, fixedSprite_t* tab_platesFormes, int nbPlateForme){
    liste ennemis = cons_empty() ;
    sprite_t ennemy ;
    int x, y;
    srand(time(NULL));
    for(int i = 0; i < NOMBRE_ENNEMIES_LEVEL1; i++){
        x = generateRandomNumber(0,screenWidth - SPRITE_WIDTH)  ; 
        y = 0 ; 
        init_sprite(&ennemy,x, y, SPRITE_WIDTH, SPRITE_HEIGHT, 0) ;
        while(!is_colliding_down_with_a_platform(&ennemy , tab_platesFormes, nbPlateForme)){
            
            if(y > screenHeight || isEnemyInitializationInvalid(&ennemy, ennemis)){ // si l'ennemy sort de la carte on reprend !
                x = generateRandomNumber(0,screenWidth - SPRITE_WIDTH)  ; 
                y = 0 ;
            }
            y++ ;
            init_sprite(&ennemy,x, y, SPRITE_WIDTH, SPRITE_HEIGHT, 0) ;
        }
        ennemis = cons(ennemy, ennemis) ;
    }
    return ennemis ;
}

SDL_Rect* init_tab_src_labels(){
    SDL_Rect* tab_src_labels = malloc(NOMBRE_LABELS*sizeof(SDL_Rect));
    tab_src_labels[0].x = 163; 
    tab_src_labels[0].y = 380; 
    tab_src_labels[0].w = LABEL_WIDTH;
    tab_src_labels[0].h = LABEL_HEIGHT;
    tab_src_labels[1].x = 163;
    tab_src_labels[1].y = 2154;
    tab_src_labels[1].w = LABEL_WIDTH;
    tab_src_labels[1].h = LABEL_HEIGHT;
    tab_src_labels[2].x = 163;
    tab_src_labels[2].y = 3706;
    tab_src_labels[2].w = LABEL_WIDTH;
    tab_src_labels[2].h = LABEL_HEIGHT;

    return tab_src_labels;

}

void init_tab_Src_Menu(fixedSprite_t* tab_menu){

    SDL_Rect* tab_src_labels = init_tab_src_labels();
    for(int i = 0; i < NOMBRE_LABELS; i++){

        tab_menu[i].src_rect = tab_src_labels[i];

    }

    free(tab_src_labels);
}

void init_tab_Dest_Menu(fixedSprite_t* tab_menu, int line, int clone){

    tab_menu[0].dest_rect.x = clone/2 - 100;
    tab_menu[0].dest_rect.y = line/2 - 25;
    tab_menu[0].dest_rect.w = LABEL_DEST_WIDTH;
    tab_menu[0].dest_rect.h = LABEL_DEST_HEIGHT;
    tab_menu[1].dest_rect.x = clone/2 - 100;
    tab_menu[1].dest_rect.y = line/2 + 50;
    tab_menu[1].dest_rect.w = LABEL_DEST_WIDTH;
    tab_menu[1].dest_rect.h = LABEL_DEST_HEIGHT;
    tab_menu[2].dest_rect.x = clone/2 - 100;
    tab_menu[2].dest_rect.y = line/2 + 125;
    tab_menu[2].dest_rect.w = LABEL_DEST_WIDTH;
    tab_menu[2].dest_rect.h = LABEL_DEST_HEIGHT;

}

void init_tab_menu(fixedSprite_t* tab_menu, int line, int clone){
    init_tab_Src_Menu(tab_menu);
    init_tab_Dest_Menu(tab_menu, line, clone);
}

void init_world(world_t* world, const char* nomFichier){
    world->gameOver = 0 ;
    world->gravity = GRAVITY;
        // world->level = 1 ;
    int nbLig, nbCol;
    taille_fichier(nomFichier, &nbLig, &nbCol);
    world->tab_terrain = lire_fichier(nomFichier) ; // allocation memoire inclu
    world->nbPlateForme = nbrPlateformes(world->tab_terrain, nbLig, nbCol) ;
    world->tab_platesFormes = malloc(world->nbPlateForme * sizeof(fixedSprite_t)) ;
    if (world->tab_platesFormes == NULL) {
    fprintf(stderr, "Erreur : Ã‰chec de l'allocation mÃ©moire pour world->tab_platesFormes\n");
    exit(EXIT_FAILURE);  // Quitter le programme en cas d'erreur critique
    }
    init_tab_platesFormes(world->tab_platesFormes, world->tab_terrain, nbLig, nbCol) ;
    init_sprite(&world->player,0,(nbLig * PLATFORM_SIZE - PLATFORM_SIZE) - SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT,0) ;
    if(!is_colliding_down_with_a_platform(&world->player, world->tab_platesFormes, world->nbPlateForme)){
        int a = generateRandomNumber(0, world->nbPlateForme);
        init_sprite(&world->player,world->tab_platesFormes[a].dest_rect.x, world->tab_platesFormes[a].dest_rect.y - SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT,0) ;
    }
    init_end_Level(&world->endLevel, nbCol * PLATFORM_SIZE - PLATFORM_SIZE, PLATFORM_SIZE) ;
    world->nbPiece =  nbrPieces(world->tab_terrain, nbLig, nbCol) ;
    world->tab_coins = malloc(world->nbPiece * sizeof(fixedSprite_t)) ;
    if (world->tab_coins == NULL) {
    fprintf(stderr, "Erreur : Ã‰chec de l'allocation mÃ©moire pour world->tab_coins\n");
    exit(EXIT_FAILURE);  // Quitter le programme en cas d'erreur critique
    }
    init_tab_coins(world->tab_terrain, nbLig, nbCol, world->tab_coins) ;
    world->ennemis = init_ennemis_level1(nbCol * PLATFORM_SIZE, nbLig * PLATFORM_SIZE, world->tab_platesFormes, world->nbPlateForme) ;
    world->tab_menu = malloc(NOMBRE_LABELS*sizeof(fixedSprite_t));
    if (world->tab_menu == NULL) {
    fprintf(stderr, "Erreur : Ã‰chec de l'allocation mÃ©moire pour tab_menu\n");
    exit(EXIT_FAILURE);  // Quitter le programme en cas d'erreur critique
    }
    init_tab_menu(world->tab_menu,nbLig * PLATFORM_SIZE,nbCol * PLATFORM_SIZE);
        // // initialisation de la camera
        // world->cameraRect.x = 0;
        // world->cameraRect.y = 0;
        // world->cameraRect.w = WINDOW_WIDTH;
        // world->cameraRect.h = PLATFORM_SIZE * nbLig;
    // initialisation du tableau des meuilleures scores a 0
    for(int i = 0; i < TAILLE_TABLEAU_SCORE; i++){
        world->tab_Score[i] = 0 ;
    }
    
}

int is_game_over(world_t *world){
    return world->gameOver;
}

void handle_events(world_t *world, SDL_Event *event) {
    // GÃ©rer les Ã©vÃ©nements SDL
    while(SDL_PollEvent(event)){
        switch (event->type) {
            case SDL_QUIT:
                world->gameOver = 1;
                break;
            case SDL_KEYDOWN:
                switch (event->key.keysym.sym) {
                    case SDLK_UP:
                    // On ne peut sauter dans l'air
                        if(is_colliding_down_with_a_platform(&world->player, world->tab_platesFormes, world-> nbPlateForme )){
                            world->player.current_frame_jump = 1 ;
                        }    
                        break;
                    case SDLK_LEFT:
                        if(!is_colliding_left_with_a_platform(&world->player, world->tab_platesFormes, world->nbPlateForme) && !player_is_colliding_left_with_ennemis(&world->player, world->ennemis)){
                            world->player.dest_rect.x -= MOVE_STEP;
                            if(world->player.current_frame_walk == NOMBRE_FRAMES_WALK - 1){
                                world->player.current_frame_walk = 0 ;
                            }else{
                                world->player.current_frame_walk ++ ;
                            }
                        }    
                        world->player.vers_la_droite = 0 ;
                        break;
                    case SDLK_RIGHT:
                        if(!is_colliding_right_with_a_platform(&world->player, world->tab_platesFormes, world->nbPlateForme) && !player_is_colliding_right_with_ennemis(&world->player, world->ennemis)){
                            world->player.dest_rect.x += MOVE_STEP;
                            if(world->player.current_frame_walk == NOMBRE_FRAMES_WALK - 1){
                                world->player.current_frame_walk = 0 ;
                            }else{
                                world->player.current_frame_walk ++ ;
                            }
                        }
                        world->player.vers_la_droite = 1 ;
                        break;

                    case SDLK_w :
                        if(world->player.weapeon == 0 ){
                        world->player.weapeon = 1 ; 
                            world->player.dest_rect.w = ARMED_SPRITE_WIDTH ;
                        }else{
                            world->player.weapeon = 0 ;
                            world->player.dest_rect.w = SPRITE_WIDTH ;
                        }  
                        break; 
                    case SDLK_a :
                        if(world->player.is_attacking == 0 ){
                            world->player.is_attacking = 1 ; 
                            if(world->player.weapeon == 1 ){
                                world->player.current_frame_walk = 5 ;
                            }
                        }  
                }   
        }
    }

}



void limite_haut(sprite_t* sprite){
    if(sprite->dest_rect.y < 0){

        sprite->dest_rect.y = 0;

    }

}

void limite_bas(sprite_t* sprite, int screen_Height){
    if(sprite->dest_rect.y + SPRITE_HEIGHT > screen_Height){

        sprite->dest_rect.y = screen_Height - SPRITE_HEIGHT;


    }
}

void limite_gauche(sprite_t* sprite){
    if(sprite->dest_rect.x < 0){
        sprite->dest_rect.x = 0;
    }
}
void limite_droite(sprite_t* sprite, int screen_Width){
    if(sprite->dest_rect.x + sprite->dest_rect.w > screen_Width){
        sprite->dest_rect.x = screen_Width - sprite->dest_rect.w ;
    }
}



void update_data(world_t* world, int screen_Height, int screen_Width){
        // // Placez la caméra autour du joueur 
        // world->cameraRect.x = world->player.dest_rect.x  - world->cameraRect.w / 2;
        // adjustAllObjectsCoordinates(world)  ;
    //gestion des limites du jeu
    limite_haut(&world->player);
    limite_bas(&world->player, screen_Height);
    limite_gauche(&world->player);
    limite_droite(&world->player, screen_Width) ;

    if(is_colliding_down_with_a_platform(&world->player, world->tab_platesFormes, world->nbPlateForme )){
        world->gravity = 0 ;   // donc il ne doit pas tombeer
    }else{
        world->gravity = GRAVITY ;
    }
    if(world->player.current_frame_jump == 0){
        world->player.dest_rect.y += world->gravity ;
    }else{ //is_jumping
        jump(&world->player, world) ;
    }
    //gestion de collision avec les bonus
    handle_colliding_with_piece(&world->player, world->tab_coins, world->nbPiece) ;
    // deplacement des ennemis
    moving_ennemis(world->ennemis, world->tab_platesFormes, world->nbPlateForme, screen_Width, &world->player)  ;
    // gestion des attaques du joueur
    handle_attack_player(&world->player, world->ennemis) ;
    attack_sprite(&world->player) ;
    //supprimer les ennemis morts
    delete_ennemy(&world->ennemis) ;
    //gestion des attack des ennemis
    handle_ennemy_is_attacking(&world->player, world->ennemis) ;
    attack_ennemis(world->ennemis) ;
    //geston colision avec le drapeau
    if(is_colliding(&world->player , &world->endLevel)){
        world->gameOver = 1 ;
        printf(" !!!!!!!! You finish with %d/%d coins !!!!!!!! \n", world->player.nbPieceRamasse, world->nbPiece) ;
    }
    //la fin du jeu
    if(world->player.dest_rect.y + SPRITE_HEIGHT == screen_Height || (world->player.HP <= 0 && world->player.current_frame_death == NOMBRE_FRAMES_DEATH - 1)){
        world->gameOver = 1 ;
        printf(" !!!!!!!! Game Over !!!!!!!! \n") ;
    }
}



bool is_colliding_right_with_a_platform(sprite_t *sprite , fixedSprite_t* tab_platesFormes, int nbPlateForme)
{
    for(int i = 0; i < nbPlateForme; i++)
    {
        if (sprite->dest_rect.x + sprite->dest_rect.w > tab_platesFormes[i].dest_rect.x &&
    sprite->dest_rect.x < tab_platesFormes[i].dest_rect.x + tab_platesFormes[i].dest_rect.w &&
    sprite->dest_rect.y < tab_platesFormes[i].dest_rect.y + tab_platesFormes[i].dest_rect.h &&
    sprite->dest_rect.y + sprite->dest_rect.h > tab_platesFormes[i].dest_rect.y)
        {   
            if(sprite->dest_rect.x <= tab_platesFormes[i].dest_rect.x){
                return true ;
            }
        }
    }
    return false ;
}

bool is_colliding_left_with_a_platform(sprite_t *sprite , fixedSprite_t* tab_platesFormes, int nbPlateForme)
{
    for(int i = 0; i < nbPlateForme; i++)
    {
        if (sprite->dest_rect.x < tab_platesFormes[i].dest_rect.x + tab_platesFormes[i].dest_rect.w &&
            sprite->dest_rect.x + sprite->dest_rect.w > tab_platesFormes[i].dest_rect.x &&
            sprite->dest_rect.y < tab_platesFormes[i].dest_rect.y + tab_platesFormes[i].dest_rect.h &&
            sprite->dest_rect.y + sprite->dest_rect.h > tab_platesFormes[i].dest_rect.y) 
        {
            if(sprite->dest_rect.x > tab_platesFormes[i].dest_rect.x){
                return true ;
            }
        }
    }
    return false ;
}

bool is_colliding_up_with_a_platform(sprite_t *sprite , fixedSprite_t* tab_platesFormes, int nbPlateForme)
{
    for(int i = 0; i < nbPlateForme; i++)
    {
        if (sprite->dest_rect.x < tab_platesFormes[i].dest_rect.x + tab_platesFormes[i].dest_rect.w &&
            sprite->dest_rect.x + sprite->dest_rect.w >=tab_platesFormes[i].dest_rect.x &&
            sprite->dest_rect.y < tab_platesFormes[i].dest_rect.y + tab_platesFormes[i].dest_rect.h &&
            sprite->dest_rect.y + sprite->dest_rect.h >= tab_platesFormes[i].dest_rect.y) 
        {
            if(sprite->dest_rect.y > tab_platesFormes[i].dest_rect.y){
                return true ;
            }
        }
    }
    return false ;
}

bool is_colliding_down_with_a_platform(sprite_t *sprite , fixedSprite_t* tab_platesFormes, int nbPlateForme)
{
    for(int i = 0; i < nbPlateForme; i++)
    {
        if (sprite->dest_rect.x < tab_platesFormes[i].dest_rect.x + tab_platesFormes[i].dest_rect.w &&
            sprite->dest_rect.x + sprite->dest_rect.w > tab_platesFormes[i].dest_rect.x &&
            sprite->dest_rect.y < tab_platesFormes[i].dest_rect.y + tab_platesFormes[i].dest_rect.h &&
            sprite->dest_rect.y + sprite->dest_rect.h >= tab_platesFormes[i].dest_rect.y) 
        {
            if(sprite->dest_rect.y < tab_platesFormes[i].dest_rect.y){
                return true ;
            }
        }
    }
    return false ;
}


bool is_jumping(sprite_t *sprite){
    return sprite->current_frame_jump > 0 && sprite->current_frame_jump <= NOMBRE_FRAMES_JUMP;
}

void jump(sprite_t *sprite, world_t *world){
    if(is_jumping(sprite)){
        world->player.weapeon = 0 ; // on range l'arme
        world->player.dest_rect.w = SPRITE_WIDTH ; // largeur par defaut 
        sprite->current_frame_jump ++ ;
        if(sprite->current_frame_jump <= NOMBRE_FRAMES_JUMP/2){
            if(!is_colliding_up_with_a_platform(sprite, world->tab_platesFormes, world->nbPlateForme)){
                sprite->dest_rect.y -= 20 ; // On monte de 20 a chaque monte du saut
            }else{
                sprite->current_frame_jump =  NOMBRE_FRAMES_JUMP/2 ;
            }
            SDL_Delay(40);
        }else{
            if(!is_colliding_down_with_a_platform(sprite, world->tab_platesFormes, world->nbPlateForme)){
                sprite->dest_rect.y += 2 ; // On descend de 1 a chaque descente du saut
            }
        }
        //se deplacer soit a gauche soit a droite  en sautant
        if(sprite->vers_la_droite == 1){
            if(!is_colliding_right_with_a_platform(sprite, world->tab_platesFormes, world->nbPlateForme)){
                sprite->dest_rect.x += 8 ; 
            }
        }else{
            if(!is_colliding_left_with_a_platform(sprite, world->tab_platesFormes, world->nbPlateForme)){
                sprite->dest_rect.x -= 8 ; 
            }
        }
    }else{
        sprite->current_frame_jump = 0 ;
    }
}

bool is_colliding(sprite_t *sprite1 , fixedSprite_t* sprite2)
{
    if (sprite1->dest_rect.x < sprite2->dest_rect.x + sprite2->dest_rect.w &&
        sprite1->dest_rect.x + sprite1->dest_rect.w > sprite2->dest_rect.x &&
        sprite1->dest_rect.y < sprite2->dest_rect.y + sprite2->dest_rect.h &&
        sprite1->dest_rect.y + sprite1->dest_rect.h > sprite2->dest_rect.y) 
    {
        return true ;
        
    }
    return false ;
}
void handle_colliding_with_piece(sprite_t *sprite , fixedSprite_t* tab_coins, int nbre_piece){
    for(int i = 0 ; i < nbre_piece; i++){
        if(is_colliding(sprite, &tab_coins[i])){
            tab_coins[i].dest_rect.y = - 100 ; // la piece disparait s'il est en collision avec le sprite
            sprite->nbPieceRamasse ++ ;
        }
    }
}

void moving_ennemis(liste ennemis, fixedSprite_t* tab_platesFormes, int nbPlateForme, int Screenwidth, sprite_t * player) {
    liste temp = ennemis;
    while (!is_empty(temp)) {
        sprite_t current_sprite = value(temp);
        if(current_sprite.HP > 0){
            // Collision en bas avec une plate-forme
            if (is_colliding_down_with_a_platform(&current_sprite, tab_platesFormes, nbPlateForme) && current_sprite.vers_la_droite == 1) {
                if(! (sprite1_is_coliding_with_sprite2(player, &current_sprite) && player->dest_rect.x > current_sprite.dest_rect.x)){
                    change_value_x(temp, current_sprite.dest_rect.x + 1);
                    change_value_current_frame_walk(temp, current_sprite.current_frame_walk + 1);
                }
            }
            if (is_colliding_down_with_a_platform(&current_sprite, tab_platesFormes, nbPlateForme) && current_sprite.vers_la_droite == 0) {
                if(! (sprite1_is_coliding_with_sprite2(player, &current_sprite) && player->dest_rect.x < current_sprite.dest_rect.x)){
                    change_value_x(temp, current_sprite.dest_rect.x - 1);
                    change_value_current_frame_walk(temp, current_sprite.current_frame_walk + 1);
                }
            }

            // Pas de collision en bas avec une plate-forme ou il ya une plateforme a droite ou l'ennemy sort de la carte a droite 
            if ((!is_colliding_down_with_a_platform(&current_sprite, tab_platesFormes, nbPlateForme)|| is_colliding_right_with_a_platform(&current_sprite, tab_platesFormes, nbPlateForme) || current_sprite.dest_rect.x + SPRITE_WIDTH > Screenwidth) && current_sprite.vers_la_droite == 1) {
                change_value_vers_la_droite(temp, 0);
                change_value_x(temp, current_sprite.dest_rect.x - 1);
                change_value_current_frame_walk(temp, current_sprite.current_frame_walk + 1);
            }
            // Pas de collision en bas avec une plate-forme ou il ya une plateforme a gauche ou l'ennemy sort de la carte a gauche 
            if ((!is_colliding_down_with_a_platform(&current_sprite, tab_platesFormes, nbPlateForme) || is_colliding_left_with_a_platform(&current_sprite, tab_platesFormes, nbPlateForme) || current_sprite.dest_rect.x < 0) && current_sprite.vers_la_droite == 0) {
                change_value_vers_la_droite(temp, 1);
                change_value_x(temp, current_sprite.dest_rect.x + 1);
                change_value_current_frame_walk(temp, current_sprite.current_frame_walk + 1);
            }
            // Gestion du frame walk
            if (current_sprite.current_frame_walk >= NOMBRE_FRAMES_WALK - 1) {
                change_value_current_frame_walk(temp, 0);
            }
        }else{
            
        }
        temp = next(temp);
    }
}


void attack_sprite(sprite_t* sprite){
    if(sprite->is_attacking == 1){ // is_attacking
        if(sprite->weapeon == 0){ //sans arme
            sprite->current_frame_attack ++ ;
            if(sprite->current_frame_attack == NOMBRE_FRAMES_ATTACK - 1){ // fin attack
                sprite->is_attacking = 0 ; // initial
                sprite->current_frame_attack = 0 ; // initial
            }
        }else{ // avec arme
            sprite->current_frame_attack_with_weapeon ++ ;
            if(sprite->current_frame_attack_with_weapeon == NOMBRE_FRAMES_ATTACK_WITH_WEAPEON - 1){ // fin attack
                sprite->is_attacking = 0 ; // initial
                sprite->current_frame_attack_with_weapeon = 0 ; // initial
            }
        }
    }
}

bool is_click_play(fixedSprite_t* tab_menu, int position_x, int position_y){

    if(position_x >= tab_menu[0].dest_rect.x && position_x <= tab_menu[0].dest_rect.x + tab_menu[0].dest_rect.w &&
        position_y <= tab_menu[0].dest_rect.y + tab_menu[0].dest_rect.h && position_y >= tab_menu[0].dest_rect.y){

        return true;
    }
    else{

        return false;
    }

}   

void handle_hightScore(const char* nomFichier, sprite_t* player, int tableau[]){
    int new_score = player->nbPieceRamasse ;
    lire_heightScore(nomFichier, tableau) ;
    // mise a jour des meuilleures scores
    for(int i = 0; i < TAILLE_TABLEAU_SCORE; i++){
        if(new_score > tableau[i]){
            tableau[i] = new_score;
            break ;
        }
    }
    //ecriture des meuilleures scores dans le fichier
    ecrire_fichier_heightScore(nomFichier, tableau) ;
    
}

bool sprite1_is_coliding_with_sprite2(sprite_t* sprite1, sprite_t* sprite2){
      if (sprite1->dest_rect.x <sprite2->dest_rect.x + sprite2->dest_rect.w &&
        sprite1->dest_rect.x + sprite1->dest_rect.w > sprite2->dest_rect.x &&
        sprite1->dest_rect.y < sprite2->dest_rect.y + sprite2->dest_rect.h &&
        sprite1->dest_rect.y + sprite1->dest_rect.h > sprite2->dest_rect.y) 
    {
        return true ;
    }
    return false ;
}

bool isEnemyInitializationInvalid(sprite_t* Ennemy, liste ennemis){
    liste temp = ennemis ;
    while(!is_empty(temp)){
        sprite_t current_ennemy = value(temp);
        if(sprite1_is_coliding_with_sprite2(Ennemy, &current_ennemy) || (abs(current_ennemy.dest_rect.x - Ennemy->dest_rect.x) < 100 && abs(current_ennemy.dest_rect.y - Ennemy->dest_rect.y) < 100)){
            return true;
        }
        temp = next(temp);
    }
    return false ;
}

bool player_is_colliding_left_with_ennemis(sprite_t* player, liste ennemis){
    liste temp = ennemis ;
    while(!is_empty(temp)){
        sprite_t current_ennemy = value(temp);
        if(sprite1_is_coliding_with_sprite2(player, &current_ennemy) && player->dest_rect.x > current_ennemy.dest_rect.x){
            return true;
        }
        temp = next(temp);
    }
    return false ;
}

bool player_is_colliding_right_with_ennemis(sprite_t* player, liste ennemis){
    liste temp = ennemis ;
    while(!is_empty(temp)){
        sprite_t current_ennemy = value(temp);
        if(sprite1_is_coliding_with_sprite2(player, &current_ennemy) && player->dest_rect.x < current_ennemy.dest_rect.x){
            return true;
        }
        temp = next(temp);
    }
    return false ;
}

void handle_attack_player(sprite_t* player, liste ennemis){
    srand(time(NULL));
    liste temp = ennemis ;
    while(! is_empty(temp)){
        sprite_t current_ennemy = value(temp);
        if(sprite1_is_coliding_with_sprite2(player, &current_ennemy)){
            if(player->is_attacking == 1 && ((player->dest_rect.x < current_ennemy.dest_rect.x && player->vers_la_droite == 1 ) || (player->dest_rect.x > current_ennemy.dest_rect.x && player->vers_la_droite == 0))){
                int new_HP ;
                if(player->current_frame_attack == 1){ // attack sans arme
                    new_HP = current_ennemy.HP - generateRandomNumber(5,20) ;
                    change_HP(temp,new_HP) ;
                }
                if(player->current_frame_attack_with_weapeon == 1){ // attack avec arme
                    new_HP = current_ennemy.HP - generateRandomNumber(10,40) ;
                    change_HP(temp,new_HP) ;
                }
            
            }
        }
        temp = next(temp);
    }
}

void handle_ennemy_is_attacking(sprite_t* player, liste ennemis){
    srand(time(NULL));
    liste temp = ennemis ;
    while(! is_empty(temp)){
        sprite_t current_ennemy = value(temp);
        Uint32 actual_time = SDL_GetTicks();
        if(actual_time - current_ennemy.lastAttackTime >= TIME_MIN_ATTACK){
            if(sprite1_is_coliding_with_sprite2(player, &current_ennemy) && ((player->dest_rect.x < current_ennemy.dest_rect.x && current_ennemy.vers_la_droite == 0 ) || (player->dest_rect.x > current_ennemy.dest_rect.x && current_ennemy.vers_la_droite == 1))){
                change_is_attacking(temp,1) ; // le l'ennemy attack
                if(current_ennemy.weapeon == 0){
                    player->HP = player->HP - generateRandomNumber(0,10);
                }else{
                    player->HP = player->HP - generateRandomNumber(5,20);
                }
                change_lastAttackTime(temp,SDL_GetTicks()) ; //mise a jour de lastAttackTime
            }
        }
        temp = next(temp);
    }
}

void attack_ennemis(liste ennemis){
    liste temp = ennemis ;
    while(! is_empty(temp)){
        sprite_t current_ennemy = value(temp);
        if(current_ennemy.is_attacking == 1){ // is_attacking
            if(current_ennemy.weapeon == 0){ //sans arme
                change_current_frame_attack(temp, current_ennemy.current_frame_attack + 1) ;
                if(current_ennemy.current_frame_attack == NOMBRE_FRAMES_ATTACK - 1){ // fin attack
                    change_is_attacking(temp,0) ; // initial
                    change_current_frame_attack(temp,0) ; // initial
                }
            }else{ // avec arme
                change_current_frame_attack_with_weapeon(temp, current_ennemy.current_frame_attack_with_weapeon + 1) ;
                if(current_ennemy.current_frame_attack_with_weapeon == NOMBRE_FRAMES_ATTACK_WITH_WEAPEON - 1){ // fin attack
                    change_is_attacking(temp,0); // initial
                    change_current_frame_attack_with_weapeon(temp,0) ; // initial
                }
            }
        }
        temp = next(temp);
    }
}

void delete_ennemy(liste *ennemis) {
    liste temp = *ennemis;
    liste prec = NULL;

    while (!is_empty(temp)) {
        sprite_t current_ennemy = value(temp);
        if (current_ennemy.HP <= 0 && current_ennemy.current_frame_death == NOMBRE_FRAMES_DEATH - 1) {
            // Si l'ennemi à supprimer est en tête de liste
            if (prec == NULL) {
                *ennemis = temp->next;
            } else {
                // Mettre à jour les liens pour sauter le nœud à supprimer
                prec->next = temp->next;
            }

            // Libérer la mémoire du nœud supprimé
            free(temp);
            
            // Avancer vers le prochain nœud
            temp = prec == NULL ? *ennemis : prec->next;
        } else {
            // Avancer vers le prochain nœud
            prec = temp;
            temp = temp->next;
        }
    }
}


// void adjustObjectCoordinates(SDL_Rect* objectRect, SDL_Rect cameraRect) {
//     objectRect->x -= cameraRect.x;
//     //objectRect->y -= cameraRect.y;
// }

// void adjustAllObjectsCoordinates(world_t* world) {
//     // Ajuster les coordonnées du joueur
//     adjustObjectCoordinates(&world->player.dest_rect, world->cameraRect);

//     // Ajuster les coordonnées des plateformes
//     for (int i = 0; i < world->nbPlateForme; i++) {
//         adjustObjectCoordinates(&world->tab_platesFormes[i].dest_rect, world->cameraRect);
//     }
//     // Ajuster les coordonnées des pieces
//     for (int i = 0; i < world->nbPiece; i++) {
//         adjustObjectCoordinates(&world->tab_coins[i].dest_rect, world->cameraRect);
//     }
//     // Ajuster les coordonnées du drapeau
//     adjustObjectCoordinates(&world->endLevel.dest_rect, world->cameraRect);
//     // Ajuster les coordonnées des ennemis
//     liste temp = world->ennemis ;
//     while(!is_empty(temp)){
//         sprite_t current_ennemy = value(temp);
//         change_value_x(temp, current_ennemy.dest_rect.x - world->cameraRect.x);
//         temp = next(temp);
//     }
// }

void clean_world(world_t* world, int nbLig) {
    desallouer_tab_2D(world->tab_terrain, nbLig);
    free(world->tab_platesFormes);
    free(world->tab_coins);
    free(world->player.walk_rects);
    free(world->player.walk_with_weapeon_rects);
    free(world->player.jump_rects);
    free(world->player.attack_rects);
    free(world->player.attack_with_weapeon_rects);
    free(world->player.death_rects);
    free(world->tab_menu);
    liberer_liste(world->ennemis);
}