#include "MainMenu.h"
#define ESCAPE_GAME 10


SDL_Surface* PlayButton = NULL;

int draw(SDL_Window* window, SDL_Surface* surface)
{
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));

	SDL_Rect coord{};
	coord.x = 1920 / 2 - 250;
	coord.y = 1080 / 2 - 234 / 2;

	SDL_BlitSurface(PlayButton, NULL, surface, &coord);

	SDL_UpdateWindowSurface(window);

	return EXIT_SUCCESS;
}

int menu_main(SDL_Window* window, SDL_Surface* surface)
{
	SDL_Event windowEvent;

	PlayButton = SDL_LoadBMP("./Materials/GUI/PlayButton.bmp");
	if (PlayButton == NULL)
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
				if (windowEvent.button.clicks == 1
					&& windowEvent.button.x > 1920 / 2 - 250
					&& windowEvent.button.y > 1080 / 2 - 234 / 2
					&& windowEvent.button.x < 1920 / 2 + 250
					&& windowEvent.button.y < 1080 / 2 + 234 / 2)
				{
					break;
				}
			}
			if (windowEvent.key.keysym.sym == SDLK_ESCAPE)
			{
				return ESCAPE_GAME;
			}
		}

		draw(window, surface);
	}

	return EXIT_SUCCESS;
}
