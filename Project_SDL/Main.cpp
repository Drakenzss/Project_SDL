#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "Tjoueur.h"
#include "Tfenetre.h"




int main(int argc, char** argv)
{
	/*posj pos;
	pos.n_x = 0;
	pos.n_y = 0;*/

	



	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* picture = NULL;
	SDL_Texture* texture = NULL;
	SDL_Rect dest_rect = { 0, 0, 640, 480 };


	

	window = SDL_CreateWindow("Affichage avec SDL2_image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	if (window == NULL) {
		SDL_Log("ERREUR > %s\n", SDL_GetError());
		clean_ressources(NULL, NULL, NULL);
		exit(EXIT_FAILURE);
	}



	renderer= SDL_CreateRenderer (window,-1, SDL_RENDERER_SOFTWARE);
	if (renderer == NULL) {
		SDL_Log("ERREUR > %s\n", SDL_GetError());
		clean_ressources(window, NULL, NULL);
		exit(EXIT_FAILURE);
	}



	picture = IMG_Load("../img/Xiao.jpg");
	if (picture == NULL) {
		SDL_Log("ERREUR > %s\n", SDL_GetError());
		clean_ressources(window,renderer, NULL);
		exit(EXIT_FAILURE);
	}



	texture = SDL_CreateTextureFromSurface(renderer, picture);
	SDL_FreeSurface(picture);
	if (texture == NULL) {
		SDL_Log("ERREUR > %s\n", SDL_GetError());
		clean_ressources(window, renderer, NULL);
		exit(EXIT_FAILURE);
	}



	if (SDL_QueryTexture(texture, NULL, NULL, &dest_rect.w, &dest_rect.h) != 0) {
		SDL_Log("ERREUR > %s\n", SDL_GetError());
		clean_ressources(window, renderer, texture);
		exit(EXIT_FAILURE);
	}



	if (SDL_RenderCopy(renderer, texture, NULL, &dest_rect) != 0) {
		SDL_Log("ERREUR > %s\n", SDL_GetError());
		clean_ressources(window, renderer, texture);
		exit(EXIT_FAILURE);
	}




	SDL_RenderPresent(renderer);

	//la fenêtre reste ouverte
	//while (app_tourne == true) {

	//}
	SDL_Delay(5000);

	clean_ressources(window, renderer, texture);
	return EXIT_SUCCESS;

	return 0;
}
