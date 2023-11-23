#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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

void init_player(sprite_t *player, double x, double y) {
    player->weapeon = 0 ;
    player->current_frame_walk = 0 ;
    player->vers_la_droite = 1 ;
    player->current_frame_jump = 0 ;
    player->nbPieceRamasse = 0 ;

    player->walk_rects = malloc(NOMBRE_FRAMES_WALK * sizeof(SDL_Rect)) ;
    int x_src , y_src ;
    x_src = 20 ;
    y_src = 11 * (IMAGE_PLAYER_HEIGHT + 15 ) ; // la 11eme ligne dans l'image du joueur (15 pixel entre chaque ligne)
    for(int i = 0 ; i <  NOMBRE_FRAMES_WALK; i++){
        player->walk_rects [i].x = x_src ;
        player->walk_rects [i].y = y_src ;
        player->walk_rects [i].w = IMAGE_PLAYER_WIDTH;
        player->walk_rects [i].h = IMAGE_PLAYER_HEIGHT;
        x_src = x_src + 64 ;
    }

    player->walk_with_weapeon_rects = malloc(NOMBRE_FRAMES_WALK * sizeof(SDL_Rect)) ;
    x_src = 45 ;
    y_src = 1770 ;
    for(int i = 0 ; i < NOMBRE_FRAMES_WALK; i++){
        player->walk_with_weapeon_rects [i].x = x_src ;
        player->walk_with_weapeon_rects [i].y = y_src ;
        player->walk_with_weapeon_rects [i].w = IMAGE_ARMED_PLAYER_WIDTH;
        player->walk_with_weapeon_rects [i].h = IMAGE_PLAYER_HEIGHT;
        x_src = x_src + 129 ;
    }

    player->jump_rects = malloc(NOMBRE_FRAMES_JUMP * sizeof(SDL_Rect)) ;
    x_src = 20 ;
    y_src = 206 ;
    for(int i = 0 ; i < NOMBRE_FRAMES_JUMP; i++){
        player->jump_rects [i].x = x_src ;
        player->jump_rects [i].y = y_src ;
        player->jump_rects [i].w = IMAGE_PLAYER_WIDTH ;
        player->jump_rects [i].h = IMAGE_PLAYER_HEIGHT;
        x_src = x_src + 64 ;
    }
    //destination
    player->dest_rect.x = x ;
    player->dest_rect.y = y ;
    player->dest_rect.w = SPRITE_WIDTH;
    player->dest_rect.h = SPRITE_HEIGHT ;

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

void init_world(world_t* world, const char* nomFichier){
    world->gameOver = 0 ;
    world->gravity = GRAVITY;
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
    init_player(&world->player,0,(nbLig * PLATFORM_SIZE - PLATFORM_SIZE) - SPRITE_HEIGHT) ;
    init_end_Level(&world->endLevel, nbCol * PLATFORM_SIZE - PLATFORM_SIZE, PLATFORM_SIZE) ;
    world->nbPiece =  nbrPieces(world->tab_terrain, nbLig, nbCol) ;
    world->tab_coins = malloc(world->nbPiece * sizeof(fixedSprite_t)) ;
    if (world->tab_coins == NULL) {
    fprintf(stderr, "Erreur : Ã‰chec de l'allocation mÃ©moire pour world->tab_coins\n");
    exit(EXIT_FAILURE);  // Quitter le programme en cas d'erreur critique
    }
    init_tab_coins(world->tab_terrain, nbLig, nbCol, world->tab_coins) ;
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
                        if(!is_colliding_left_with_a_platform(&world->player, world->tab_platesFormes, world->nbPlateForme) ){
                            world->player.dest_rect.x -= MOVE_STEP;
                            if(world->player.current_frame_walk == NOMBRE_FRAMES_WALK - 1){
                                world->player.current_frame_walk = 0 ;
                            }else{
                                world->player.current_frame_walk ++ ;
                            }
                            world->player.vers_la_droite = 0 ;
                        }    
                        break;
                    case SDLK_RIGHT:
                        if(!is_colliding_right_with_a_platform(&world->player, world->tab_platesFormes, world->nbPlateForme) ){
                            world->player.dest_rect.x += MOVE_STEP;
                            if(world->player.current_frame_walk == NOMBRE_FRAMES_WALK - 1){
                                world->player.current_frame_walk = 0 ;
                            }else{
                                world->player.current_frame_walk ++ ;
                            }
                            world->player.vers_la_droite = 1 ;
                        }
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
    if(sprite->dest_rect.y + IMAGE_PLAYER_HEIGHT > screen_Height){

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
    //geston colision avec le drapeau
    if(is_colliding(&world->player , &world->endLevel)){
        world->gameOver = 1 ;
        printf(" !!!!!!!! You finish the first level with %d/%d coins !!!!!!!! \n", world->player.nbPieceRamasse, world->nbPiece) ;
    }
    //la fin du jeu
    if(world->player.dest_rect.y + SPRITE_HEIGHT == screen_Height){
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
        if(sprite->current_frame_jump <= NOMBRE_FRAMES_JUMP/2 ){
            if(!is_colliding_up_with_a_platform(sprite, world->tab_platesFormes, world->nbPlateForme)){
                sprite->dest_rect.y -= 20 ; // On monte de 20 a chaque monte du saut
            }else{
                sprite->current_frame_jump =  NOMBRE_FRAMES_JUMP/2 ;
            }
            SDL_Delay(80);
        }else{
            if(!is_colliding_down_with_a_platform(sprite, world->tab_platesFormes, world->nbPlateForme)){
                sprite->dest_rect.y += 1 ; // On descend de 1 a chaque descente du saut
            }
            SDL_Delay(40);
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