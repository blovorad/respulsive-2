#include "prototype.h"

void init(void)
{
	srand(time(NULL));
	
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("IMPOSSIBLE DE CHARGER LA SDL : %s",SDL_GetError());
		exit(EXIT_FAILURE);
	}

	initWindowAndRenderer();

	//ON ACTIVE LA TRANSPARENCE
	if(SDL_SetRenderDrawBlendMode(getRenderer(), SDL_BLENDMODE_BLEND) != 0)
	{
		SDL_Log("IMPOSSIBLE D'ACTIVER LA TRANSPARENCE :%s",SDL_GetError());
		exit(EXIT_FAILURE);
	}

	//ON INIT LA LIB D'ECRITURE
	if(TTF_Init() != 0)
	{
		SDL_Log("IMPOSSIBLE DE CHARGER TTF :%s",TTF_GetError());
		exit(EXIT_FAILURE);
	}

	//ON INIT LA LIB DE SON
	if(Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		SDL_Log("IMPOSSIBLE DE CHARGER MIXER :%s",Mix_GetError());
		exit(EXIT_FAILURE);
	}

	initSceneManager();
	initAudio(0, 13);
	initEvent();
	initMouse();
	initTexture();
	initMainMenu();
	initGameBackground();
}

//LE GRAND NETTOYAGE
void cleanUp(void)
{
	SDL_Log("----CLEAN GENERAL EN COURS----\n");
	if(isActiveGame())
	{
		cleanGame();
	}
	if(isActiveMainMenu())
	{
		cleanMainMenu();
	}
	if(isActiveCredit())
	{
		cleanCredit();
	}
	if(isActiveOption())
	{
		cleanOption();
	}
	cleanTexture();
	cleanGameBackground();
	cleanAudio();

	cleanWindowAndRenderer();

	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
	SDL_Log("----CLEAN GENERAL TERMINER----\n");
}