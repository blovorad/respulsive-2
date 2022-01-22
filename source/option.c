#include "prototype.h"

static GroupeGui menu;

void initOption(void)
{
	SDL_Log("--------------INIT OPTION EN COURS--------------\n");
	setPrintOption(SDL_TRUE);
	initGroupeGui(&menu, 2, 2, 8, 0);

	initFontHack();

	if(getFullscreen() == SDL_TRUE)
	{
		menu.liste_bouton[5] = createBouton(290, 70, 210, 50, -1, getNoir(255), "FULLSCREEN ON", getBlanc(255), getFontHack(), SDL_TRUE, 13);
	}
	else
	{
		menu.liste_bouton[5] = createBouton(290, 70, 210, 50, -1, getNoir(255), "FULLSCREEN OFF", getBlanc(255), getFontHack(), SDL_TRUE, 13);
	}
	if(getCurrentResolution() == 0)
	{
		menu.liste_bouton[6] = createBouton(300, 10, 200, 50, -1, getNoir(255), "800x600", getBlanc(255), getFontHack(), SDL_TRUE, 14);
	}
	else if(getCurrentResolution() == 1)
	{
		menu.liste_bouton[6] = createBouton(300, 10, 200, 50, -1, getNoir(255), "1024x768", getBlanc(255), getFontHack(), SDL_TRUE, 14);
	}
	else if(getCurrentResolution() == 2)
	{
		menu.liste_bouton[6] = createBouton(300, 10, 200, 50, -1, getNoir(255), "1360x768", getBlanc(255), getFontHack(), SDL_TRUE, 14);
	}
	else if(getCurrentResolution() == 3)
	{
		menu.liste_bouton[6] = createBouton(300, 10, 200, 50, -1, getNoir(255), "1600x900", getBlanc(255), getFontHack(), SDL_TRUE, 14);
	}
	else if(getCurrentResolution() == 4)
	{
		menu.liste_bouton[6] = createBouton(300, 10, 200, 50, -1, getNoir(255), "1920x1080", getBlanc(255), getFontHack(), SDL_TRUE, 14);
	}

	if(getLocalisation() == 0)
	{
		//int x, int y, int w, int h, int texture,SDL_Color panelColor, char *ptexte, SDL_Color texteColor, TTF_Font *font, SDL_bool pFill, int event
		menu.liste_bouton[0] = createBouton(0, 450, 250, 50, -1, getNoir(255), "RETOUR SUR LE PONT", getBlanc(255), getFontHack(), SDL_TRUE, 3);
		menu.liste_bouton[1] = createBouton(150, 200, 100, 50, -1, getNoir(255), "MOINS", getBlanc(255), getFontHack(), SDL_TRUE, 8);
		menu.liste_bouton[2] = createBouton(550, 200, 100, 50, -1, getNoir(255), "PLUS", getBlanc(255), getFontHack(), SDL_TRUE, 7);
		menu.liste_bouton[3] = createBouton(150, 350, 100, 50, -1, getNoir(255), "MOINS", getBlanc(255), getFontHack(), SDL_TRUE, 6);
		menu.liste_bouton[4] = createBouton(550, 350, 100, 50, -1, getNoir(255), "PLUS", getBlanc(255), getFontHack(), SDL_TRUE, 5);
		menu.liste_bouton[7] = createBouton(600, 450, 200, 50, -1, getNoir(255), "FRANCAIS", getBlanc(255), getFontHack(), SDL_TRUE, 15);

		//int x, int y, int w, int h, char *texte, SDL_Color color, TTF_Font *font
		menu.liste_texte[0] = createTexte(300, 150, 200, 50, "VOLUME MUSIQUES", getBlanc(255), getFontHack());
		menu.liste_texte[1] = createTexte(300, 300, 200, 50, "VOLUME EFFETS", getBlanc(255), getFontHack());
	}
	else
	{
		//int x, int y, int w, int h, int texture,SDL_Color panelColor, char *ptexte, SDL_Color texteColor, TTF_Font *font, SDL_bool pFill, int event
		menu.liste_bouton[0] = createBouton(0, 450, 250, 50, -1, getNoir(255), "BACK TO CONTROL ROOM", getBlanc(255), getFontHack(), SDL_TRUE, 3);
		menu.liste_bouton[1] = createBouton(150, 200, 100, 50, -1, getNoir(255), "MOINS", getBlanc(255), getFontHack(), SDL_TRUE, 8);
		menu.liste_bouton[2] = createBouton(550, 200, 100, 50, -1, getNoir(255), "PLUS", getBlanc(255), getFontHack(), SDL_TRUE, 7);
		menu.liste_bouton[3] = createBouton(150, 350, 100, 50, -1, getNoir(255), "MOINS", getBlanc(255), getFontHack(), SDL_TRUE, 6);
		menu.liste_bouton[4] = createBouton(550, 350, 100, 50, -1, getNoir(255), "PLUS", getBlanc(255), getFontHack(), SDL_TRUE, 5);
		menu.liste_bouton[7] = createBouton(600, 450, 200, 50, -1, getNoir(255), "ENGLISH", getBlanc(255), getFontHack(), SDL_TRUE, 15);

		//int x, int y, int w, int h, char *texte, SDL_Color color, TTF_Font *font
		menu.liste_texte[0] = createTexte(300, 150, 200, 50, "VOLUME MUSICS", getBlanc(255), getFontHack());
		menu.liste_texte[1] = createTexte(300, 300, 200, 50, "VOLUME EFFECTS", getBlanc(255), getFontHack());
	}

	//int x, int y, int w, int h, SDL_Color color
	menu.liste_barre[0] = createBarre(275, 200, 250, 50, getBlanc(255));
	menu.liste_barre[1] = createBarre(275, 350, 250, 50, getBlanc(255));

	cleanFontHack();

	SDL_Log("--------------INIT OPTION TERMINER--------------\n");
}

void updateOption(void)
{
	menu.liste_barre[0].sprite.dimension.w = (getVolumeMusic() * menu.liste_barre[0].tailleReel.w) / 10;
	menu.liste_barre[1].sprite.dimension.w = (getVolumeFx() * menu.liste_barre[1].tailleReel.w) / 10;

	updateGroupeGui(&menu);
}

void drawOption(void)
{
	drawGroupeGui(&menu);
}

void cleanOption(void)
{
	SDL_Log("--------------CLEAN OPTION EN COURS--------------\n");
	setPrintOption(SDL_FALSE);
	cleanGroupeGui(&menu);
	SDL_Log("--------------CLEAN OPTION TERMINER--------------\n");
}

void changeBoutonFullscreen(void)
{
	initFontHack();
	if(menu.liste_bouton[5].texte.sprite.texture != NULL)
	{
		SDL_DestroyTexture(menu.liste_bouton[5].texte.sprite.texture);
		menu.liste_bouton[5].texte.sprite.texture = NULL;
	}

	if(getFullscreen() == SDL_TRUE)
	{
		menu.liste_bouton[5] = createBouton(290, 70, 210, 50, -1, getNoir(255), "FULLSCREEN ON", getBlanc(255), getFontHack(), SDL_TRUE, 13);
	}
	else
	{
		menu.liste_bouton[5] = createBouton(290, 70, 210, 50, -1, getNoir(255), "FULLSCREEN OFF", getBlanc(255), getFontHack(), SDL_TRUE, 13);
	}
	cleanFontHack();
}