#include "MainMenu.h"

#define ESCAPE_GAME 10
#define EVENT_SUCSESS 1

enum LayerType
{
	MAIN_MENU,
	LOAD_MENU,
	SETINGS_MENU
};

SDL_Texture* PlayButton = NULL;
SDL_Texture* SetingsButton = NULL;
SDL_Texture* LoadButton = NULL;
SDL_Texture* ExitButton = NULL;

SDL_Texture* MusicButtonOn = NULL;
SDL_Texture* MusicButtonOff = NULL;

SDL_Texture* Background = NULL;

int MenuEvents(SDL_Event windowEvent, SetingsData &setings)
{
	

	return EXIT_SUCCESS;
}

int draw(SDL_Window* window, 
		 SDL_Surface* surface,
		 LayerType layers, 
		 SetingsData setings, 
		 SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, Background, NULL, NULL);

	SDL_Rect coord{};
	coord.w = setings.width / 7.5;
	coord.h = setings.height / 8.43;

	if (layers == MAIN_MENU)
	{
		coord.x = (setings.width / 6) - (setings.width / 15);
		coord.y = setings.height - (setings.width / 15) - (setings.width / 96);
		SDL_RenderCopy(ren, PlayButton, NULL, &coord);

		coord.x = (setings.width / 3) - (setings.width / 15);
		coord.y = setings.height - (setings.width / 15) - (setings.width / 96);
		SDL_RenderCopy(ren, LoadButton, NULL, &coord);

		coord.x = (setings.width / 2) - (setings.width / 15);
		coord.y = setings.height - (setings.width / 15) - (setings.width / 96);
		SDL_RenderCopy(ren, SetingsButton, NULL, &coord);

		coord.x = (int)(setings.width / 1.5) - (setings.width / 15);
		coord.y = setings.height - (setings.width / 15) - (setings.width / 96);
		SDL_RenderCopy(ren, SetingsButton, NULL, &coord);

		coord.x = (int)(setings.width / 1.2) - (setings.width / 15);
		coord.y = setings.height - (setings.width / 15) - (setings.width / 96);
		SDL_RenderCopy(ren, ExitButton, NULL, &coord);
	}

	if (layers == SETINGS_MENU)
	{
		coord.x = (setings.width / 2) - (setings.width / 15);
		coord.y = setings.height - (setings.width / 15) - (setings.width / 96);
		SDL_RenderCopy(ren, SetingsButton, NULL, &coord);

		coord.w = setings.width / 7.5;
		coord.h = setings.height / 16.875;
		coord.x = (setings.width / 2) - (setings.width / 15);
		coord.y = setings.height - (setings.height / 2);
		if (setings.music == false)
		{
			SDL_RenderCopy(ren, MusicButtonOff, NULL, &coord);
		}
		else
		{
			SDL_RenderCopy(ren, MusicButtonOn, NULL, &coord);
		}

	}

	if (layers == LOAD_MENU)
	{
		coord.x = (setings.width / 3) - (setings.width / 15);
		coord.y = setings.height - (setings.width / 15) - (setings.width / 96);
		SDL_RenderCopy(ren, LoadButton, NULL, &coord);
	}

	SDL_RenderPresent(ren);
	SDL_RenderClear(ren);

	return EXIT_SUCCESS;
}

int EventIn_MainMenu(SDL_Event windowEvent,
					SetingsData setings,
					LayerType& status)
{
	if (windowEvent.button.x > (setings.width) / 6 - (setings.width / 15)
		&& windowEvent.button.x < (setings.width / 6) + (setings.width / 15)
		&& windowEvent.button.y > setings.height - (setings.width / 15) - (setings.width / 96)
		&& windowEvent.button.y < setings.height - (setings.width / 96))
	{
		return EXIT_SUCCESS;
	}

	if (windowEvent.button.x > (setings.width) / 3 - (setings.width / 15)
		&& windowEvent.button.x < (setings.width / 3) + (setings.width / 15)
		&& windowEvent.button.y > setings.height - (setings.width / 15) - (setings.width / 96)
		&& windowEvent.button.y < setings.height - (setings.width / 96))
	{
		status = LOAD_MENU;
		return EVENT_SUCSESS;
	}

	if (windowEvent.button.x > (setings.width) / 2 - (setings.width / 15)
		&& windowEvent.button.x < (setings.width / 2) + (setings.width / 15)
		&& windowEvent.button.y > setings.height - (setings.width / 15) - (setings.width / 96)
		&& windowEvent.button.y < setings.height - (setings.width / 96))
	{
		status = SETINGS_MENU;
		return EVENT_SUCSESS;
	}

	if (windowEvent.button.x > (int)(setings.width / 1.2) - (setings.width / 15)
		&& windowEvent.button.x < (int)(setings.width / 1.2) + (setings.width / 15)
		&& windowEvent.button.y > setings.height - (setings.width / 15) - (setings.width / 96)
		&& windowEvent.button.y < setings.height - (setings.width / 96))
	{
		return ESCAPE_GAME;
	}

	return -1;
}

int EventIn_LoadMenu(SDL_Event windowEvent,
					SetingsData setings,
					LayerType& status)
{
	if (windowEvent.key.keysym.sym == SDLK_ESCAPE)
	{
		status = MAIN_MENU;
	}


	return EXIT_SUCCESS;
}

int EventIn_SetingsMenu(SDL_Event windowEvent,
					SetingsData& setings,
					LayerType& status)
{
	if (windowEvent.key.keysym.sym == SDLK_ESCAPE)
	{
		status = MAIN_MENU;
	}

	if (windowEvent.type == SDL_MOUSEBUTTONDOWN)
	{
		if (windowEvent.button.x >= (setings.width / 2) - (setings.width / 15)
			&& windowEvent.button.x < (setings.width / 2) + (setings.width / 15)
			&& windowEvent.button.y >= setings.height - (setings.height / 2)
			&& windowEvent.button.y < setings.height - (setings.height / 2) + (int)(setings.height / 16.875))
		{
			setings.ChangeMusicStatus(setings);
			setings.WriteToFile(setings);
		}
	}
	

	return EXIT_SUCCESS;
}

int load_menu(SDL_Renderer* ren)
{
	SDL_Surface* temp_surface = SDL_LoadBMP("./Materials/GUI/PlayButton.bmp");
	PlayButton = SDL_CreateTextureFromSurface(ren, temp_surface);
	if (PlayButton == NULL)
	{
		return LOADERROR;
	}

	temp_surface = SDL_LoadBMP("./Materials/GUI/SetingsButton.bmp");
	SetingsButton = SDL_CreateTextureFromSurface(ren, temp_surface);
	if (SetingsButton == NULL)
	{
		return LOADERROR;
	}

	temp_surface = SDL_LoadBMP("./Materials/GUI/LoadButton.bmp");
	LoadButton = SDL_CreateTextureFromSurface(ren, temp_surface);
	if (LoadButton == NULL)
	{
		return LOADERROR;
	}

	temp_surface = SDL_LoadBMP("./Materials/GUI/ExitButton.bmp");
	ExitButton = SDL_CreateTextureFromSurface(ren, temp_surface);
	if (ExitButton == NULL)
	{
		return LOADERROR;
	}

	temp_surface = SDL_LoadBMP("./Materials/GUI/Background.bmp");
	Background = SDL_CreateTextureFromSurface(ren, temp_surface);
	if (Background == NULL)
	{
		return LOADERROR;
	}

	temp_surface = SDL_LoadBMP("./Materials/GUI/MusicSetingsButtonOn.bmp");
	MusicButtonOn = SDL_CreateTextureFromSurface(ren, temp_surface);
	if (MusicButtonOn == NULL)
	{
		return LOADERROR;
	}

	temp_surface = SDL_LoadBMP("./Materials/GUI/MusicSetingsButtonOff.bmp");
	MusicButtonOff = SDL_CreateTextureFromSurface(ren, temp_surface);
	if (MusicButtonOff == NULL)
	{
		return LOADERROR;
	}

	temp_surface = NULL;

	return 0;
}

int unload_menu()
{
	PlayButton = NULL;
	SetingsButton = NULL;
	LoadButton = NULL;
	ExitButton = NULL;
	Background = NULL;

	return 0;
}

int menu_main(SDL_Window* window, 
			  SDL_Surface* surface, 
			  SDL_Renderer* ren)
{
	SDL_Event windowEvent;

	LayerType status = MAIN_MENU;
	SetingsData setings;
	setings.LoadFromFile(setings);

	load_menu(ren);

	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT)
			{
				unload_menu();
				return ESCAPE_GAME;
			}
			if (windowEvent.type == SDL_MOUSEBUTTONDOWN 
				&& status == MAIN_MENU)
			{
				int tempmenureturn = EventIn_MainMenu(windowEvent, setings, status);
				if (tempmenureturn == EXIT_SUCCESS || tempmenureturn ==  ESCAPE_GAME)
				{
					unload_menu();
					return tempmenureturn;
				}
			}

			if (status == LOAD_MENU)
			{
				EventIn_LoadMenu(windowEvent, setings, status);
			}

			if (status == SETINGS_MENU)
			{
				EventIn_SetingsMenu(windowEvent, setings, status);
			}
		}

		draw(window, surface, status, setings, ren);
	}

	return EXIT_SUCCESS;
}
//EASY4ENCE