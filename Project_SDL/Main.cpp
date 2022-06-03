#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <conio.h>

#include "Tjoueur.h"
#include "Tfenetre.h"




int main(int argc, char** argv)
{
	posj pos;
	pos.n_x = 0;
	pos.n_y = 0;



	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* picture = NULL;
	SDL_Texture* texture = NULL;
	SDL_Rect dest_rect = { 0, 0, 640, 480 };


	

	window = SDL_CreateWindow("RPG ou Platformer?", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
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
	while (app_tourne) {
		SDL_Event event;
		while (SDL_PollEvent(&event)){//si on clique sur la croix la fenêtre se ferme
			if (event.type == SDL_QUIT)
			{
				app_tourne = false;
			}

			

		}

		SDL_Event keyevent;

		while (SDL_PollEvent(&keyevent)) // chaque touche pressées, un évènement s'active.
		{

			switch (keyevent.type) {
			case SDL_KEYDOWN://lorsqu'on appuis sur la flèche du bas, on peut se déplacer en diagonale
				switch (keyevent.key.keysym.sym) {
				case SDLK_LEFT:
					charxvel = -1;
					break;
				case SDLK_RIGHT:
					charxvel = 1;
					break;
				case SDLK_UP://on ne peut pas aller en haut et en bas en même temps
					charyvel = -1;
					break;
				case SDLK_DOWN://on reste vers le bas
					charyvel = 1;
					break;
				default:
					break;
				}
				break;
			case SDL_KEYUP://lorsqu'on appuis sur la flèche du haut, on peut se déplacer en diagonale
				switch (keyevent.key.keysym.sym) {
				case SDLK_LEFT:
					charxvel = 0;
					break;
				case SDLK_RIGHT:
					charxvel = 0;
					break;
				case SDLK_UP: //on reste vers le haut
					charyvel = 0;
					break;
				case SDLK_DOWN://on ne peut pas aller en haut et en bas en même temps
					charyvel = 0;
					break;
				default:
					break;
				}
			}
		}

	charx += charxvel; chary += charyvel;
		
	}
	




	clean_ressources(window, renderer, texture);
	return EXIT_SUCCESS;

	return 0;
}
