#include "Include/sdl_component.h"
#include "Include/game_lib.h"

int initialize_sdl() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Sdl initialize failure \n %s", SDL_GetError()); 
		exit(EXIT_FAILURE); 
	} 
	
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {	
		exit(EXIT_FAILURE); 
	}
	    
	if (Mix_OpenAudio(24100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		exit(EXIT_FAILURE); 
	}

	if (TTF_Init()) {
		printf("TTF Creation Faliure\n"); 
		exit(EXIT_FAILURE); 
	}
	return 0; 
}
SDL_Window* sdl_create_window(char* tiles, int width, int height) {	
	SDL_Window* window = SDL_CreateWindow(tiles, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	if (window == NULL) {
		printf("sdl window init failure \n"); 
		exit(EXIT_FAILURE); 
	}
	return window; 
} 
SDL_Renderer* sdl_create_renderer(SDL_Window* window) {	
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 
	if (renderer == NULL) {	
		printf("sdl create renderer failure\n"); 
		exit(EXIT_FAILURE);
	}
	return renderer; 
}

void draw(int x, int y, int w, int h, SDL_Renderer* renderer, SDL_Texture* texture) {
		SDL_Rect rect_draw = {x, y, w, h}; 
		SDL_RenderCopy(renderer, texture, NULL, &rect_draw); 
}

SDL_Texture* load_texture(char* filename, SDL_Renderer* renderer) {

	SDL_Surface* surface = IMG_Load(filename); 	
	if (surface == NULL) {
		printf("Print: Error> Couldn't load the png\n"); 
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface); 
	if (texture == NULL) {		
		printf("Print: Error> Couldn't load the png\n"); 
	}
	SDL_FreeSurface(surface); 
	return texture; 
}

int sdl_input(SDL_Event e, Ship* ship, Bomb* missle, int* running_flag) {
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_KEYDOWN) {	
			   switch (e.key.keysym.sym) { 
					case SDLK_d: 
						update_player(ship,missle, 1);
						break; 						
					case SDLK_a: 
						update_player(ship,missle, -1);
						break; 					
					case SDLK_SPACE: 
						ship->is_missle = 1;
						play_sound("/path/to/sound"); 			
						break;
					case SDLK_q: 
						*running_flag = false; 
						break; 
		  	}
		}
	} 
	    return 1; 
} 

void clear_screen(SDL_Renderer* renderer, SDL_Texture* bgtextue) {	
	SDL_RenderClear(renderer);	
	SDL_RenderCopy(renderer, bgtextue, NULL, NULL); 
}

int draw_invader(Invader invader[], SDL_Renderer* renderer, int end_flag) {

	SDL_Texture* texture1 = load_texture("path/to/texture", renderer);
	SDL_Texture* texture2 = load_texture("path/to/texture", renderer);
	SDL_Texture* texture3 = load_texture("path/to/texture", renderer);
	if (end_flag == 1) {				
		SDL_DestroyTexture(texture1); 
		SDL_DestroyTexture(texture2); 
		SDL_DestroyTexture(texture3); 
	}

	for (int i = 0; i  < 10; i++) {
		
		if (invader[i].is_active != 0) {
			draw(invader[i].rect.x, invader[i].rect.y, invader[i].rect.w, invader[i].rect.h, renderer, texture2);	
		}	
	}


	for (int j = 10; j < 30; j++) {
		
		if (invader[j].is_active != 0) {
			draw(invader[j].rect.x, invader[j].rect.y, invader[j].rect.w, invader[j].rect.h, renderer, texture1);	
		}	

	}
	for (int k = 30; k < 40; k++)	{
		
		if (invader[k].is_active != 0) {
			draw(invader[k].rect.x, invader[k].rect.y, invader[k].rect.w, invader[k].rect.h, renderer, texture3);	
		}	
	}
	return 0;		
}

int draw_bomb(Bomb bomb[], Invader invader[], SDL_Renderer* renderer, int end_flag) {
	
	SDL_Texture* texture = load_texture("path/to/texture", renderer);	

	if (end_flag == 1) {				
		SDL_DestroyTexture(texture); 
	}

	for (int i = 0; i < 40; i++) {	
		for (int j = 0; j < 6; j++) {
			if (invader[i].is_bome == 1) {
				
				draw(bomb[j].rect.x,bomb[j].rect.y, bomb[j].rect.w, bomb[j].rect.h, renderer, texture); 
			}
		}
	}
	return 0;  
}
int draw_ship(Ship* ship, Bomb* missle, SDL_Renderer*renderer, int end_flag) {

	SDL_Texture* texture1 = load_texture("path/to/texture", renderer);
	SDL_Texture* texture2 = load_texture("path/to/texture", renderer);	
	if (end_flag == 1) {		
		SDL_DestroyTexture(texture1); 
		SDL_DestroyTexture(texture2); 
	}

	draw(ship->rect.x, ship->rect.y, ship->rect.w, ship->rect.h, renderer, texture1); 		     
	if (ship->is_missle == 1) {							
		draw(missle->rect.x, missle->rect.y, missle->rect.w, missle->rect.h, renderer, texture2); 		     
	}
	return 0; 
}

void draw_game_point_text(SDL_Renderer* renderer, int* point) {
		
	TTF_Font* openFont = TTF_OpenFont("path/to/ttf_font", 32);
	if (!openFont) {
	        printf("Font can't load\n");	
		exit(EXIT_FAILURE); 
	}

	SDL_Rect rectangle; 
	rectangle.x = 50;
	rectangle.y = 5;  
	rectangle.w = 200;
	rectangle.h = 90;
		
	SDL_Color textColor = {255, 255, 255, 255}; 
	char score[20];
	sprintf(score, "P  %d", *point); 

	SDL_Surface* surfaceText = TTF_RenderText_Solid(openFont, score , textColor);
	SDL_Texture* textureText = SDL_CreateTextureFromSurface(renderer,surfaceText);
	SDL_FreeSurface(surfaceText);  
	SDL_RenderCopy(renderer ,textureText, NULL, &rectangle);
}

void draw_game_over_text(SDL_Renderer* renderer) {
	
	TTF_Font* openFont = TTF_OpenFont("path/to/ttf_font", 32);
	if (!openFont) {
	        printf("Font can't load\n");	
		exit(EXIT_FAILURE); 
	}

	SDL_Rect rectangle; 
	rectangle.x = 300;
	rectangle.y = 400;  
	rectangle.w = 200;
	rectangle.h = 100;

	SDL_Color textColor = {255, 255, 255, 255}; 
	SDL_Surface* surfaceText = TTF_RenderText_Solid(openFont, "GAME OVER" , textColor);
	SDL_Texture* textureText = SDL_CreateTextureFromSurface(renderer,surfaceText);
	SDL_FreeSurface(surfaceText);  
	SDL_RenderCopy(renderer ,textureText, NULL, &rectangle);
}

int render_game(Invader invader[], Ship* ship, Bomb* missle, Bomb bomb[]) {
	

	SDL_Window* window = sdl_create_window("Space Invader", 800, 900); 
	if (window == NULL) {
		printf("Window creation falure  \n"); 
		exit(EXIT_FAILURE); 
	}	

	SDL_Renderer* renderer = sdl_create_renderer(window); 
	if (renderer == NULL) {
		printf("Renderer creation falure  \n"); 
		exit(EXIT_FAILURE); 
	}	

	/* call in background music */
	play_backgound_music("path/to/music"); 

	SDL_Texture* backgound_texture = load_texture("path/to/backgound_texture", renderer);	
	if (backgound_texture == NULL)  {		
		printf("texture creation falure  \n"); 
		exit(EXIT_FAILURE); 
	}

	int running_flag, game_over_flags; 		
	int point = 100; 

	SDL_Event event; 

	game_over_flags = 0; 
	running_flag = true;
	while(running_flag) {
		
		clear_screen(renderer, backgound_texture); 
		/* game get input and output */
		sdl_input(event, ship, missle, &running_flag);
		if (running_flag == false) {
			game_over_flags = 1; 
			break; 
		}	

		/* update funtion */
		update_invader(invader); 	
		update_bome(invader, bomb); 			
		update_missle(missle, ship); 
		update_collision(missle, ship, invader, &point);

		/* Game Over detection */
		if (collision(bomb, ship->rect.x, ship->rect.y, ship->rect.w, ship->rect.h) == true) {
		
			play_sound("path/to/sound");
			game_over_flags = 1; 
		}

		/* rendere and draw functin */
		if (draw_invader(invader, renderer, game_over_flags) == 0) {
			/* contionue runing the game if falure is not */
			running_flag = 1; 
		} 
		if (draw_bomb(bomb, invader, renderer, game_over_flags) == 0) {	

			/* contionue runing the game if falure is not */
			running_flag = 1; 
		} 
		if (draw_ship(ship, missle, renderer, game_over_flags) == 0) {	

			/* contionue runing the game if falure is not */
			running_flag = 1;
		}
		/* function draw end */


		/* render ttf fonts */
		draw_game_point_text(renderer, &point); 

		/* render game over screen */
		if (game_over_flags == 1) {	

			draw_game_over_text(renderer); 

			for (int i = 0; i < 40; i++) {
				invader[i].is_active = 0; 
				invader[i].is_bome = 0; 
				ship->rect.x = 0; 
				ship->rect.y = 0; 
				ship->is_missle = 0; 
				
			}
			
		}

		/* show render and done :) */
		SDL_RenderPresent(renderer);	
		SDL_Delay(50);
	}

	/* Sdl clean up */
	SDL_DestroyWindow(window); 
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(backgound_texture); 
	Mix_CloseAudio(); 
	Mix_Quit();    

	return 1; 
}
