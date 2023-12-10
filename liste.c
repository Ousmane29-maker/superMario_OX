#include "liste.h"
#include <stdio.h>
#include <stdlib.h>

liste cons_empty() {
    return NULL;
}

liste cons(sprite_t sprite, liste next) {
    liste l = (liste)malloc(sizeof(node_t));
    if (l == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation mémoire.\n");
        exit(EXIT_FAILURE);
    }
    l->data = sprite;
    l->next = next;
    return l;
}

int is_empty(liste l) {
    return l == NULL;
}

sprite_t value(liste l) {
    if (is_empty(l)) {
        fprintf(stderr, "Erreur: Tentative d'accéder à la valeur d'une liste vide.\n");
        exit(EXIT_FAILURE);
    } else {
        return l->data;
    }
}

liste next(liste l ) {
    if (is_empty(l)) {
        fprintf(stderr, "Erreur: Tentative d'accéder au prochain nœud d'une liste vide.\n");
        exit(EXIT_FAILURE);
    } else {
        return l->next;
    }
}

void change_value_x(liste l, int new_x)
{
    if (is_empty(l)) {
        fprintf(stderr, "Erreur: Tentative de modifier (change_value_x) d'une liste vide.\n");
        exit(EXIT_FAILURE);
    }else{
    l->data.dest_rect.x = new_x ;
    }
}

void change_value_y(liste l, int new_y)
{
    if (is_empty(l)) {
        fprintf(stderr, "Erreur: Tentative de modifier (change_value_y) d'une liste vide.\n");
        exit(EXIT_FAILURE);
    }else{
    l->data.dest_rect.y = new_y ;
    }
}

void change_value_vers_la_droite(liste l , int new_direction){
    if (is_empty(l)) {
        fprintf(stderr, "Erreur: Tentative de modifier (change_value_vers_la_droite) d'une liste vide.\n");
        exit(EXIT_FAILURE);
    }else{
    l->data.vers_la_droite = new_direction ;
    }
}

void change_value_current_frame_walk(liste l, int new_current_frame_walk){
    if (is_empty(l)) {
        fprintf(stderr, "Erreur: Tentative de modifier (change_value_current_frame_walk) d'une liste vide.\n");
        exit(EXIT_FAILURE);
    }else{
    l->data.current_frame_walk = new_current_frame_walk ;
    }
}

void change_value_current_frame_death(liste l, int new_current_frame_death){
    if (is_empty(l)) {
        fprintf(stderr, "Erreur: Tentative de modifier (change_value_current_frame_death) d'une liste vide.\n");
        exit(EXIT_FAILURE);
    }else{
    l->data.current_frame_death = new_current_frame_death ;
    }
}

void change_HP(liste l, int new_HP){
    if (is_empty(l)) {
        fprintf(stderr, "Erreur: Tentative de modifier (change_HP) d'une liste vide.\n");
        exit(EXIT_FAILURE);
    }else{
    l->data.HP = new_HP ;
    }
}

void change_next(liste l, node_t* new_next){
    if (is_empty(l)) {
        fprintf(stderr, "Erreur: Tentative de modifier (change_next) d'une liste vide.\n");
        exit(EXIT_FAILURE);
    }else{
    l->next = new_next ;
    }
}    

void liberer_liste(liste l) {
    while (! is_empty(l)) {
        // Stocker le nœud actuel
        liste temp = l;       
        //liberer les tableaux dans la structure sprite_t
        free(temp->data.walk_rects) ;
        free(temp->data.walk_with_weapeon_rects) ;
        free(temp->data.jump_rects) ;
        free(temp->data.attack_rects) ;
        free(temp->data.attack_with_weapeon_rects) ;
        free(temp->data.death_rects) ;
        // Déplacer le pointeur vers le prochain nœud
        l = l->next;      
        // Libérer le nœud actuel    
        free(temp);           
    }
}

