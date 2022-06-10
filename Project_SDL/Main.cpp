#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <conio.h>
#include <SDL_keycode.h>

#include "Tjoueur.h"
#include "Tfenetre.h"




int main(int argc, char** argv)
{
	posj pos;//pour la position de l'image
	pos.n_x = 0;
	pos.n_y = 0;

	direction direct;//pour les déplacements de l'image
	direct.droite = 0;
	direct.gauche = 0;
	direct.bas = 0;
	direct.haut = 0;



	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* picture = NULL;
	SDL_Texture* texture = NULL;
	SDL_Rect dest_rect = { pos.n_x, pos.n_y, 40, 40 };




	if (SDL_Init(SDL_INIT_VIDEO) != NULL) {
		SDL_Log("ERREUR de chargement vidéo > %s\n", SDL_GetError());
		clean_ressources(NULL, NULL, NULL);
		exit(EXIT_FAILURE);
	}


	window = SDL_CreateWindow("RPG ou Platformer?", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	if (window == NULL) {
		SDL_Log("ERREUR de création de fenêtre > %s\n", SDL_GetError());
		clean_ressources(NULL, NULL, NULL);
		exit(EXIT_FAILURE);
	}



	renderer= SDL_CreateRenderer (window,-1, SDL_RENDERER_SOFTWARE);
	if (renderer == NULL) {
		SDL_Log("ERREUR de création du renderer > %s\n", SDL_GetError());
		clean_ressources(window, NULL, NULL);
		exit(EXIT_FAILURE);
	}



	picture = IMG_Load("../img/startpoint.png");
	if (picture == NULL) {
		SDL_Log("ERREUR de création de l'image> %s\n", SDL_GetError());
		clean_ressources(window,renderer, NULL);
		exit(EXIT_FAILURE);
	}

	


	texture = SDL_CreateTextureFromSurface(renderer, picture);
	SDL_FreeSurface(picture);
	if (texture == NULL) {
		SDL_Log("ERREUR de création de la texture> %s\n", SDL_GetError());
		clean_ressources(window, renderer, NULL);
		exit(EXIT_FAILURE);
	}

	
	
	//la fenêtre reste ouverte
	while (app_tourne == True) {

		

		SDL_Event event;
		while (SDL_PollEvent(&event)){//si on clique sur la croix la fenêtre se ferme

			switch (event.type)
			{
			case SDL_QUIT:
				app_tourne = False;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_UP://lorsqu'on appuis sur la flèche du haut
						direct.haut = 1;
						break;
						

					case SDLK_DOWN://lorsqu'on appuis sur la flèche du bas
						direct.bas = 1;
						break;

					case SDLK_RIGHT://lorsqu'on appuis sur la flèche de droite
						direct.droite = 1;
						break;

					case SDLK_LEFT://lorsqu'on appuis sur la flèche de gauche
						direct.gauche = 1;
						break;

					default:
						break;
				}

				if (direct.bas == 1)
				{
					pos.n_y = 1;
					
				}

				if (direct.droite == 1)
				{
					pos.n_x = 1;
				}

				if (direct.haut == 1)
				{
					pos.n_y = -1;
				}

				if (direct.gauche == 1)
				{
					pos.n_x = -1;
				}
			
				

				dest_rect.x = dest_rect.x + pos.n_x;
				dest_rect.y = dest_rect.y + pos.n_y;

			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
					case SDLK_UP://lorsqu'on appuis sur la flèche du haut
						direct.haut = 0;
						pos.n_y = 0;
						break;

					case SDLK_DOWN://lorsqu'on appuis sur la flèche du bas
						direct.bas = 0;
						pos.n_y = 0;
						break;

					case SDLK_RIGHT://lorsqu'on appuis sur la flèche de droite
						direct.droite = 0;
						pos.n_x = 0;

						break;

					case SDLK_LEFT://lorsqu'on appuis sur la flèche de gauche
						direct.gauche = 0;
						pos.n_x = 0;

						break;
					default:
						break;
				}

				

			default:
				break;
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


			
			SDL_RenderClear(renderer);

		}

	}
	




	clean_ressources(window, renderer, texture);
	return EXIT_SUCCESS;

	return 0;
}
