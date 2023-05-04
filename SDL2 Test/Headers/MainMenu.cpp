#include "MainMenu.h"
#define ESCAPE_GAME 10

enum LayerType
{
	MAIN_MENU,
	LOAD_MENU,
	SETINGS_MENU
};

SDL_Surface* PlayButton = NULL;
SDL_Surface* SetingsButton = NULL;

int draw(SDL_Window* window, SDL_Surface* surface, LayerType layers)
{
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));
	SDL_Rect coord{};

	if (layers == MAIN_MENU)
	{
		coord.x = 1920 / 4 - 128;
		coord.y = 1080 - 128 - 20;
		SDL_BlitSurface(PlayButton, NULL, surface, &coord);

		coord.x = 1920 / 2 - 128;
		coord.y = 1080 - 128 - 20;
		SDL_BlitSurface(SetingsButton, NULL, surface, &coord);
	}
	else if (layers == SETINGS_MENU)
	{

	}


	SDL_UpdateWindowSurface(window);

	return EXIT_SUCCESS;
}

int menu_main(SDL_Window* window, SDL_Surface* surface)
{
	SDL_Event windowEvent;

	LayerType status = MAIN_MENU;

	PlayButton = SDL_LoadBMP("./Materials/GUI/PlayButton.bmp");
	if (PlayButton == NULL)
	{
		return LOADERROR;
	}

	SetingsButton = SDL_LoadBMP("./Materials/GUI/SetingsButton.bmp");
	if (SetingsButton == NULL)
	{
		return LOADERROR;
	}


	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT)
			{
				return ESCAPE_GAME;
			}
			if (windowEvent.type == SDL_MOUSEBUTTONDOWN)
			{
				if (windowEvent.button.x > 1920 / 4 - 128
					&& windowEvent.button.x < 1920 / 4 + 128
					&& windowEvent.button.y > 1080 - 128 - 20
					&& windowEvent.button.y < 1080 - 20)
				{
					return EXIT_SUCCESS;
				}




			}


			if (windowEvent.key.keysym.sym == SDLK_ESCAPE)
			{
				return ESCAPE_GAME;
			}
		}

		draw(window, surface, status);
	}

	return EXIT_SUCCESS;
}
//EASY4ENCE