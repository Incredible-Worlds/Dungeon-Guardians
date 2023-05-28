#include "MainMenu.h"

#define ESCAPE_GAME 10
#define EVENT_SUCSESS 1

enum LayerType
{
	MAIN_MENU,
	LOAD_MENU,
	SETINGS_MENU
};

struct menutexture
{
	SDL_Texture* PlayButton = NULL;
	SDL_Texture* SetingsButton = NULL;
	SDL_Texture* LoadButton = NULL;
	SDL_Texture* ExitButton = NULL;

	SDL_Texture* MusicButtonOn = NULL;
	SDL_Texture* MusicButtonOff = NULL;

	SDL_Texture* Background = NULL;
}MainMenuTexture;


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
	SDL_RenderCopy(ren, MainMenuTexture.Background, NULL, NULL);

	SDL_Rect coord{};
	coord.w = setings.width / 7.5;
	coord.h = setings.height / 8.43;

	if (layers == MAIN_MENU)
	{
		coord.x = (setings.width / 6) - (setings.width / 15);
		coord.y = setings.height - (setings.width / 15) - (setings.width / 96);
		SDL_RenderCopy(ren, MainMenuTexture.PlayButton, NULL, &coord);

		coord.x = (setings.width / 3) - (setings.width / 15);
		coord.y = setings.height - (setings.width / 15) - (setings.width / 96);
		SDL_RenderCopy(ren, MainMenuTexture.LoadButton, NULL, &coord);

		coord.x = (setings.width / 2) - (setings.width / 15);
		coord.y = setings.height - (setings.width / 15) - (setings.width / 96);
		SDL_RenderCopy(ren, MainMenuTexture.SetingsButton, NULL, &coord);

		coord.x = (int)(setings.width / 1.5) - (setings.width / 15);
		coord.y = setings.height - (setings.width / 15) - (setings.width / 96);
		SDL_RenderCopy(ren, MainMenuTexture.SetingsButton, NULL, &coord);

		coord.x = (int)(setings.width / 1.2) - (setings.width / 15);
		coord.y = setings.height - (setings.width / 15) - (setings.width / 96);
		SDL_RenderCopy(ren, MainMenuTexture.ExitButton, NULL, &coord);
	}

	if (layers == SETINGS_MENU)
	{
		coord.x = (setings.width / 2) - (setings.width / 15);
		coord.y = setings.height - (setings.width / 15) - (setings.width / 96);
		SDL_RenderCopy(ren, MainMenuTexture.SetingsButton, NULL, &coord);

		coord.w = setings.width / 7.5;
		coord.h = setings.height / 16.875;
		coord.x = (setings.width / 2) - (setings.width / 15);
		coord.y = setings.height - (setings.height / 2);
		if (setings.music == false)
		{
			SDL_RenderCopy(ren, MainMenuTexture.MusicButtonOff, NULL, &coord);
		}
		else
		{
			SDL_RenderCopy(ren, MainMenuTexture.MusicButtonOn, NULL, &coord);
		}

	}

	if (layers == LOAD_MENU)
	{
		coord.x = (setings.width / 3) - (setings.width / 15);
		coord.y = setings.height - (setings.width / 15) - (setings.width / 96);
		SDL_RenderCopy(ren, MainMenuTexture.LoadButton, NULL, &coord);
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

	if (windowEvent.button.x > (int)(setings.width / 1.5) - (setings.width / 15)
		&& windowEvent.button.x < (int)(setings.width / 1.5) + (setings.width / 15)
		&& windowEvent.button.y > setings.height - (setings.width / 15) - (setings.width / 96)
		&& windowEvent.button.y < setings.height - (setings.width / 96))
	{
		status = MAIN_MENU;
		return 56;
	}
	

	if (windowEvent.button.x > (int)(setings.width / 1.2) - (setings.width / 15)
		&& windowEvent.button.x < (int)(setings.width / 1.2) + (setings.width / 15)
		&& windowEvent.button.y > setings.height - (setings.width / 15) - (setings.width / 96)
		&& windowEvent.button.y < setings.height - (setings.width / 96))
	{
		return ESCAPE_GAME;
	}

	return EVENT_SUCSESS;
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
	MainMenuTexture.PlayButton = SDL_CreateTextureFromSurface(ren, temp_surface);
	if (MainMenuTexture.PlayButton == NULL)
	{
		return LOADERROR;
	}

	temp_surface = SDL_LoadBMP("./Materials/GUI/SetingsButton.bmp");
	MainMenuTexture.SetingsButton = SDL_CreateTextureFromSurface(ren, temp_surface);
	if (MainMenuTexture.SetingsButton == NULL)
	{
		return LOADERROR;
	}

	temp_surface = SDL_LoadBMP("./Materials/GUI/LoadButton.bmp");
	MainMenuTexture.LoadButton = SDL_CreateTextureFromSurface(ren, temp_surface);
	if (MainMenuTexture.LoadButton == NULL)
	{
		return LOADERROR;
	}

	temp_surface = SDL_LoadBMP("./Materials/GUI/ExitButton.bmp");
	MainMenuTexture.ExitButton = SDL_CreateTextureFromSurface(ren, temp_surface);
	if (MainMenuTexture.ExitButton == NULL)
	{
		return LOADERROR;
	}

	temp_surface = SDL_LoadBMP("./Materials/GUI/Background.bmp");
	MainMenuTexture.Background = SDL_CreateTextureFromSurface(ren, temp_surface);
	if (MainMenuTexture.Background == NULL)
	{
		return LOADERROR;
	}

	temp_surface = SDL_LoadBMP("./Materials/GUI/MusicSetingsButtonOn.bmp");
	MainMenuTexture.MusicButtonOn = SDL_CreateTextureFromSurface(ren, temp_surface);
	if (MainMenuTexture.MusicButtonOn == NULL)
	{
		return LOADERROR;
	}

	temp_surface = SDL_LoadBMP("./Materials/GUI/MusicSetingsButtonOff.bmp");
	MainMenuTexture.MusicButtonOff = SDL_CreateTextureFromSurface(ren, temp_surface);
	if (MainMenuTexture.MusicButtonOff == NULL)
	{
		return LOADERROR;
	}

	temp_surface = NULL;

	return 0;
}

int unload_menu()
{
	MainMenuTexture.PlayButton = NULL;
	MainMenuTexture.SetingsButton = NULL;
	MainMenuTexture.LoadButton = NULL;
	MainMenuTexture.ExitButton = NULL;
	MainMenuTexture.Background = NULL;

	return 0;
}

int menu_main(SDL_Window* window, 
			  SDL_Surface* surface, 
			  SDL_Renderer* ren,
			  Mix_Music* mainmusic)
{
	SDL_Event windowEvent;

	LayerType status = MAIN_MENU;
	SetingsData setings;
	setings.LoadFromFile(setings);

	bool musicSetings = setings.music;
	if (musicSetings == true)
	{
		musicSetings = false;
	}
	else
	{
		musicSetings = true;
	}

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
				int tempmenureturn;
				if ((tempmenureturn = EventIn_MainMenu(windowEvent, setings, status)) != EVENT_SUCSESS)
				{
					if (tempmenureturn == 56)
					{
						GameEditor(ren);
					}
					else
					{
						unload_menu();
						return tempmenureturn;
					}
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

		if (setings.music == true && musicSetings == false)
		{
			Mix_PlayMusic(mainmusic, -1);
			musicSetings = true;
		}
		if (setings.music == false && musicSetings == true)
		{
			Mix_HaltMusic();
			musicSetings = false;
		}
	}

	return EXIT_SUCCESS;
}
//EASY4ENCE