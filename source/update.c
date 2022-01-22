#include "prototype.h"

void update(Input *input)
{
	getMousePos();					//recuperation de la position de la souris
	getInput(input);				//recuperation des touches presser/relacher
	//updateAudio();
	
	if(isActiveGame())
	{
		if(getPrintPause() == SDL_FALSE)
		{
			updateGameBackground();
		}
	}
	else
	{
		updateGameBackground();
	}

	if(isActiveGame())
	{
		updateGame(input);
	}
	if(isActiveMainMenu())
	{
		updateMainMenu();
	}
	if(isActiveCredit())
	{
		updateCredit();
	}
	if(isActiveOption())
	{
		updateOption();
	}

	actualiseOldLeftButton();
}