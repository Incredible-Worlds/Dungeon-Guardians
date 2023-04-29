#include "MainMenu.h"

int draw(SDL_Window* window, SDL_Surface* surface)
{
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 250, 0, 0));

	SDL_UpdateWindowSurface(window);

	return SUCSESS_EXIT;
}

int menu_main(SDL_Window* window, SDL_Surface* surface)
{
	SDL_Event windowEvent;

	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT)
			{
				break;
			}
		}

		draw(window, surface);
	}

	return SUCSESS_EXIT;
}
