#include "prototype.h"

static SDL_bool printPause;
static GroupeGui menu;
static GroupeGui defaite;

void initGame(void)
{
	playFx(4);
	SDL_Log("--------------INIT GAME EN COURS--------------\n");
	setPrintGame(SDL_TRUE);
	printPause = SDL_FALSE;
	SDL_ShowCursor(SDL_DISABLE);

	initFontHack();
	initGroupeGui(&menu, 0, 1, 2, 1);
	initDefaite();

	if(getLocalisation() == 0)
	{
		//int x, int y, int w, int h, int texture,SDL_Color panelColor, char *ptexte, SDL_Color texteColor, TTF_Font *font, SDL_bool pFill, int event
		menu.liste_bouton[0] = createBouton(10, 300, 200, 50, -1, getNoir(255), "MENU PRINCIPAL", getBlanc(255), getFontHack(), SDL_TRUE, 4);
		menu.liste_bouton[1] = createBouton(10, 350, 200, 50, -1, getNoir(255), "RETOUR", getBlanc(255), getFontHack(), SDL_TRUE, 11);

		//int x, int y, int w, int h, int texture, SDL_Color color, SDL_bool pFill
		menu.liste_panel[0] = createPanel(0, 290, 220, 120, -1, getBleu(255), SDL_TRUE);

		//int x, int y, int w, int h, char *texte, SDL_Color color, TTF_Font *font
		menu.liste_texte[0] = createTexte(300, 50, 200, 50, "PAUSE ACTIVE", getBlanc(255), getFontHack());
	}
	else
	{
		//int x, int y, int w, int h, int texture,SDL_Color panelColor, char *ptexte, SDL_Color texteColor, TTF_Font *font, SDL_bool pFill, int event
		menu.liste_bouton[0] = createBouton(10, 300, 200, 50, -1, getNoir(255), "MAIN MENU", getBlanc(255), getFontHack(), SDL_TRUE, 4);
		menu.liste_bouton[1] = createBouton(10, 350, 200, 50, -1, getNoir(255), "RETURN", getBlanc(255), getFontHack(), SDL_TRUE, 11);

		//int x, int y, int w, int h, int texture, SDL_Color color, SDL_bool pFill
		menu.liste_panel[0] = createPanel(0, 290, 220, 120, -1, getBleu(255), SDL_TRUE);

		//int x, int y, int w, int h, char *texte, SDL_Color color, TTF_Font *font
		menu.liste_texte[0] = createTexte(300, 50, 200, 50, "PAUSE ON", getBlanc(255), getFontHack());
	}

	initShoot();
	initHostile();
	initPlayer();
	initTuto();
	initPowerUp();

	SDL_Log("--------------INIT GAME TERMINER--------------\n");
}

void updateGame(Input *input)
{	
	if(!printPause)
	{
		if(getPrintTuto())
		{
			updateTuto();
			if(input->z)
			{
				playFx(5);
				giveAmmo();
				addVitesseHostile();
				stopAcceleration();
				cleanTuto();
			}
		}
		else
		{
			updatePowerUp();
			updateHostile();
		}
		updateShoot();
		updatePlayer(input);
	}
	else
	{
		updateHostile();
		updateGroupeGui(&menu);
	}
	if(!isPlayerAlive())
	{
		updateGroupeGui(&defaite);
	}
}

void drawGame(void)
{
	drawShoot();
	drawPowerUp();
	drawPlayer();
	drawHostile();
	if(getPrintTuto())
	{
		drawTuto();
	}
	if(printPause)
	{
		drawGroupeGui(&menu);
	}
	if(!isPlayerAlive())
	{
		drawGroupeGui(&defaite);
	}
}

void cleanGame(void)
{
	SDL_Log("--------------CLEAN GAME EN COURS--------------\n");
	setPrintGame(SDL_FALSE);
	
	if(getPrintTuto())
	{
		cleanTuto();
	}
	cleanFontHack();
	cleanPowerUp();
	cleanPlayer();
	cleanHostile();
	cleanShoot();
	cleanGroupeGui(&menu);
	cleanGroupeGui(&defaite);
	SDL_Log("--------------CLEAN GAME TERMINER--------------\n");
}

void setPrintPause(SDL_bool active)
{
	if(active == SDL_TRUE)
	{
		SDL_ShowCursor(SDL_ENABLE);
	}
	else
	{
		SDL_ShowCursor(SDL_DISABLE);
	}
	printPause = active;
}

SDL_bool getPrintPause(void)
{
	return printPause;
}

SDL_bool checkCollide(SDL_Rect a, SDL_Rect b)
{
	return collide(a, b);
}

void initDefaite(void)
{
	initGroupeGui(&defaite, 0, 0, 1, 1);

	if(getLocalisation() == 0)
	{
		//int x, int y, int w, int h, int texture,SDL_Color panelColor, char *ptexte, SDL_Color texteColor, TTF_Font *font, SDL_bool pFill, int event
		defaite.liste_bouton[0] = createBouton(300, 275, 200, 50, -1, getNoir(255), "MENU PRINCIPAL", getBlanc(255), getFontHack(), SDL_TRUE, 12);
	}
	else
	{
		//int x, int y, int w, int h, char *texte, SDL_Color color, TTF_Font *font
		defaite.liste_bouton[0] = createBouton(300, 275, 200, 50, -1, getNoir(255), "MAIN MENU", getBlanc(255), getFontHack(), SDL_TRUE, 12);
	}

	//int x, int y, int w, int h, int texture, SDL_Color color, SDL_bool pFill
	defaite.liste_panel[0] = createPanel(295, 270, 210, 60, -1, getBleu(255), SDL_TRUE);

}