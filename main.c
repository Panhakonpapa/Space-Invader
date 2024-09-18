#include "Lib/Include/game_lib.h"
#include "Lib/Include/sdl_component.h"

#define MAX_INVADER 40
#define MAX_BOMB 6

int main() {
	
	Invader enermy[MAX_INVADER]; 
	Bomb bomb[MAX_BOMB]; 
	Bomb missle; 
	Ship ship; 

	if (initialize_invader(enermy) == 0) {
		printf("Invader init [ good ]\n"); 
	} 
	if (initialize_spaceship(&ship) == 0) {	
		printf("Spaceship init [ good ]\n"); 
	} 
	if (initialize_bomb(bomb, enermy) == 0) {	
		printf("Bomb init [ good ]\n"); 
	} 
	if (initialize_missle(&missle, &ship) == 0) {	
		printf("missle init [ good ]\n"); 
	} 
	if (initialize_sdl() == 0) {	
		printf("missle init [ good ]\n"); 
	}	
	if (render_game(enermy, &ship, &missle, bomb) == 1) {
		printf("Engine run perfectly \n"); 
		return 0; 
	} 
}
