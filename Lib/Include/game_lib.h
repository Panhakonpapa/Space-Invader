#ifndef GAME_LIB
#define GAME_LIB
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL.h>


typedef struct {
	SDL_Rect rect; 
	int direction; 
	int is_active; 
	int is_bome; 
} Invader; 

typedef struct {
	SDL_Rect rect; 
	int is_missle; 
} Ship; 

typedef struct {
	SDL_Rect rect; 
} Bomb; 

void play_sound(char *file);  
void play_backgound_music(char* file);  
int initialize_invader(Invader invader[]); 
int initialize_spaceship(Ship* ship); 
int initialize_bomb(Bomb bomb[], Invader invader[]);  
int initialize_missle(Bomb* missle, Ship* ship);  
void update_invader(Invader invader[]);  
void update_player(Ship* ship, Bomb* missle, int direction);  
void update_collision(Bomb* missile, Ship* ship, Invader invader[], int* point);  
bool collision(Bomb* missle, int x, int y, int w, int h); 
void update_bome(Invader invader[], Bomb* ordence);   
void update_missle(Bomb* missle, Ship* ship);  

#endif
