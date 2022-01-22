#include "prototype.h"

static GroupeGui menu;
static SDL_bool printTuto;
static Timer timer;

void initTuto(void)
{
	SDL_Log("--------------INIT TUTO EN COURS--------------\n");
	printTuto = SDL_TRUE;

	timer.ms = 5000;
	timer.previousTime = SDL_GetTicks();
	timer.currentTime = 0;

	initGroupeGui(&menu, 0, 3, 0, 0);

	if(getLocalisation() == 0)
	{
		//int x, int y, int w, int h, char *texte, SDL_Color color, TTF_Font *font
		menu.liste_texte[0] = createTexte(300, 150, 200, 50, "APPUYER Q OU D POUR BOUGER", getBlanc(255), getFontHack());
		menu.liste_texte[1] = createTexte(300, 175, 200, 50, "APPUYER SUR ESPACE POUR TIRER ET SUR S TIRER UN MISSILE", getBlanc(255), getFontHack());
		menu.liste_texte[2] = createTexte(300, 200, 200, 50, "APPUYER SUR Z POUR COMMENCEZ", getBlanc(255), getFontHack());
	}
	else
	{
		//int x, int y, int w, int h, char *texte, SDL_Color color, TTF_Font *font
		menu.liste_texte[0] = createTexte(300, 150, 200, 50, "PRESS A OR D TO MOVE", getBlanc(255), getFontHack());
		menu.liste_texte[1] = createTexte(300, 175, 200, 50, "PRESS SPACE TO SHOOT AND PRESS S TO LAUNCH A MISSILE", getBlanc(255), getFontHack());
		menu.liste_texte[2] = createTexte(300, 200, 200, 50, "PRESS W TO START", getBlanc(255), getFontHack());
	}

	menu.liste_texte[0].couleur.a = 1;
	menu.liste_texte[1].couleur.a = 1;
	menu.liste_texte[2].couleur.a = 1;
	SDL_SetTextureAlphaMod(menu.liste_texte[0].sprite.texture, menu.liste_texte[0].couleur.a);
	SDL_SetTextureAlphaMod(menu.liste_texte[1].sprite.texture, menu.liste_texte[1].couleur.a);
	SDL_SetTextureAlphaMod(menu.liste_texte[2].sprite.texture, menu.liste_texte[2].couleur.a);
	
	SDL_Log("--------------INIT TUTO TERMINER--------------\n");
}

void updateTuto(void)
{
	if(menu.liste_texte[0].couleur.a < 249)
	{
		menu.liste_texte[0].couleur.a += 5;
		if(menu.liste_texte[0].couleur.a > 249)
		{
			menu.liste_texte[0].couleur.a = 254;
		}
		SDL_SetTextureAlphaMod(menu.liste_texte[0].sprite.texture, menu.liste_texte[0].couleur.a);
	}
	else if(menu.liste_texte[1].couleur.a < 249)
	{
		menu.liste_texte[1].couleur.a += 5;
		if(menu.liste_texte[1].couleur.a > 249)
		{
			menu.liste_texte[1].couleur.a = 254;
		}
		SDL_SetTextureAlphaMod(menu.liste_texte[1].sprite.texture, menu.liste_texte[1].couleur.a);
	}
	else if(menu.liste_texte[2].couleur.a < 249)
	{
		menu.liste_texte[2].couleur.a += 5;
		if(menu.liste_texte[2].couleur.a > 249)
		{
			menu.liste_texte[2].couleur.a = 254;
		}
		SDL_SetTextureAlphaMod(menu.liste_texte[2].sprite.texture, menu.liste_texte[2].couleur.a);
	}
}

void drawTuto(void)
{
	drawGroupeGui(&menu);
}

void cleanTuto(void)
{
	SDL_Log("--------------CLEAN TUTO EN COURS--------------\n");
	printTuto = SDL_FALSE;
	cleanGroupeGui(&menu);
	SDL_Log("--------------CLEAN TUTO TERMINER--------------\n");
}

SDL_bool getPrintTuto(void)
{
	return printTuto;
}