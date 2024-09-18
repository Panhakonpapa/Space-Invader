#include "Include/game_lib.h"
#include "Include/sdl_component.h"

/* define macro for Invader */
#define MAX_INVADER 40 
#define INVADER_WIDTH 30 
/*define macro for Bomb */ 
#define BOMB_WIDTH 10 
#define BOMB_HEIGHT 70 
#define MAX_BOMB 6 

void play_backgound_music(char* file) {
	Mix_Music *bgMusic = Mix_LoadMUS(file);
	if (bgMusic == NULL) 
	{
		printf("Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
		exit(EXIT_FAILURE); 
	}

	if (Mix_PlayMusic(bgMusic, -1) == -1) 
	{
		printf("SDL_mixer could not play music! SDL_mixer Error: %s\n", Mix_GetError());
		exit(EXIT_FAILURE); 
	}	
}

void play_sound(char *file) {
    Mix_Chunk *soundEffect = Mix_LoadWAV(file);
    
    if (soundEffect == NULL) {
        printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    Mix_PlayChannel(-1, soundEffect, 0);

}

int initialize_invader(Invader invader[]) {

	int row = 0; 
	int col = 0; 
	int gaps = 50; 

	for (int i = 0; i < MAX_INVADER; i++) {
		invader[i].rect.x = gaps + row * (INVADER_WIDTH + gaps); 
		invader[i].rect.y = gaps + col * (INVADER_WIDTH + gaps); 
		invader[i].rect.w = 40; 
		invader[i].rect.h = 40; 	
		invader[i].direction = 1; 
		invader[i].is_active = 1; 

		row++; 

		if (row >= 10) {
			row = 0; 
			col++; 
		}
	}
	return 0; 
}

#define WINDOW_WIDTH 800 
int initialize_spaceship(Ship* ship) {
	ship->rect.x = 200; 
	ship->rect.y = 800; 
	ship->rect.w = 80; 
	ship->rect.h = 80; 
	ship->is_missle = 0; 
	return 0; 
}


int initialize_bomb(Bomb bomb[], Invader invader[]) {


	srand(time(0));	
	int count = 6; 
	for (int i = 0; i < MAX_INVADER; i++) {
		if (invader[i].is_bome == 1) {
			
			play_sound("/path/to/sound"); 			
		}
	}
	for (int i = 0; i < MAX_INVADER; i++) {

		int random = rand() % 2; 
		
		if (random == 1 && count != 0) {	

		
			int index = i;
			invader[index].is_bome = 1; 	

			if (invader[i].is_active == 0) {						

				invader[index].is_bome = 0; 	
			}

			for (int j = 0; j < MAX_BOMB; j++) {	

				if (invader[i].is_active == 1) {
					
					bomb[j].rect.x = invader[index].rect.x + invader[index].rect.w / 2 - BOMB_WIDTH / 2;   
					bomb[j].rect.y = invader[index].rect.y + invader[index].rect.h / 2; 
					bomb[j].rect.w = BOMB_WIDTH; 
					bomb[j].rect.h = BOMB_HEIGHT; 
				}

			}
			count--; 
		} 
	}
	return 0; 
}  

int initialize_missle(Bomb* missle, Ship* ship) {

	missle->rect.x = ship->rect.x + ship->rect.w / 2 - (10 / 2);   
	missle->rect.y = ship->rect.y + ship->rect.h / 2; 
	missle->rect.w = 10; 
	missle->rect.h = 70; 

	return 0; 
}

#define WINDOW_HEIGHT 800

void update_invader(Invader invader[]) {
	int speed = 8; 
	for (int i = 0; i < 40; i++) {					
		
		int down = 50; 
		if (invader[i].rect.x >= WINDOW_HEIGHT) {
			invader[i].direction = -1;
			invader[i].rect.y += down;  
			if (invader[i].is_active == 1) {	
							
				play_sound("/path/to/sound"); 			
				
			}
		}
		if (invader[i].rect.x <= 0) {
			invader[i].direction = 1;
			invader[i].rect.y += down;  
			if (invader[i].is_active == 1) {	

				play_sound("/path/to/sound"); 			
			}
		}
		
		if (invader[i].is_active == 1) {	
			invader[i].rect.x += invader[i].direction * speed; 
		}
	}
} 

#define WINDOW_HEIGHT 800

void update_player(Ship* ship, Bomb* missle, int direction) {
	int speed = 100; 


	ship->rect.x += direction * speed; 

	initialize_missle(missle, ship); 

	if (ship->rect.x <= 0) {
		ship->rect.x = 0; 
	}

	if (ship->rect.x + ship->rect.h >= WINDOW_HEIGHT) {
		ship->rect.x = WINDOW_HEIGHT - ship->rect.x; 
	}
}

bool collision(Bomb* missle, int x, int y, int w, int h) {
	return (missle->rect.x < x + w &&
			missle->rect.x + missle->rect.w > x &&
			missle->rect.y < y + h &&
			missle->rect.y + missle->rect.h > y); 
}	

void update_collision(Bomb* missile, Ship* ship, Invader invader[], int* point) {
    for (int i = 0; i < 40; i++) {
            if (collision(missile, invader[i].rect.x, invader[i].rect.y, invader[i].rect.w, invader[i].rect.h)) {

		/* if the system detected a collision we need to reset put it at pos 1 1 to display */
                invader[i].is_active = 0;  
		invader[i].rect.x = 1; 
		invader[i].rect.y = 1; 
		ship->is_missle = 0; 

		*point += 100; 
		

		play_sound("/path/to/sound"); 			

		initialize_missle(missile, ship); 	
                break;  
        }
    }
}

void update_bome(Invader invader[], Bomb bomb[]) {

	int bomb_speed = 3; 	
	
	for (int i = 0; i < MAX_INVADER; i++) {	

		if (invader[i].is_bome == 1) {


			for (int j = 0; j < MAX_BOMB; j++) {


				bomb[j].rect.y += bomb_speed; 	


				if (bomb[j].rect.y + bomb[j].rect.h >= 900) {
					
					/* Deactivate */
					invader[j].is_bome = 0; 				

					/* reset the posisiton */
					initialize_bomb(bomb, invader); 


				}
			}
		}
	}
	
}


void update_missle(Bomb* missle, Ship* ship) {
	int speed = 60; 
		
	if (ship->is_missle == 1) {	
		missle->rect.y -= speed;   
	}

	if (missle->rect.y + missle->rect.h <= 0) {
		ship->is_missle = 0; 
		/* reset missle */
		initialize_missle(missle, ship); 
	}
}
