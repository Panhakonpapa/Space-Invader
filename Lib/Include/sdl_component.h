#ifndef SDL_COMPONENT_H
#define SDL_COMPONENT_H
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

/* dependency Header for drawing something in real time event input and output */
#include "game_lib.h"


int initialize_sdl();  
void draw(int x, int y, int w, int h, SDL_Renderer* renderer, SDL_Texture* texture);  
void clear_screen(SDL_Renderer* renderer, SDL_Texture* bgtextue);	
void game_sprite_manger_load_textuere(Invader invader[], Ship* ship, SDL_Renderer* renderer);  
void game_sprite_manger(Invader invader[], Ship* ship);  
void draw_game_point_text(SDL_Renderer* renderer, int* point);  
void draw_game_over_text(SDL_Renderer* renderer);  
SDL_Window* sdl_create_window(char* titles,int width, int height); 
SDL_Renderer* sdl_create_renderer(SDL_Window* window); 
SDL_Texture* load_texture(char* filename, SDL_Renderer* renderer);  
int sdl_input(SDL_Event e, Ship* ship, Bomb* missle, int* running_flag);  
int draw_invader(Invader invader[], SDL_Renderer* renderer, int end_flag);  
int draw_bomb(Bomb bomb[], Invader invader[], SDL_Renderer* renderer, int end_flag); 
int draw_ship(Ship* ship, Bomb* missle, SDL_Renderer*renderer, int end_flag); 
int render_game(Invader invader[], Ship* ship, Bomb* missle, Bomb bomb[]);  

#endif

