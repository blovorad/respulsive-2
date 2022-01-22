#include "prototype.h"

static GroupeGui menu;

void initCredit(void)
{
	SDL_Log("--------------INIT CREDIT EN COURS--------------\n");
	setPrintCredit(SDL_TRUE);
	initGroupeGui(&menu, 0, 6, 1, 0);	

	initFontHack();

	if(getLocalisation() == 0)
	{
		//int x, int y, int w, int h, int texture,SDL_Color panelColor, char *ptexte, SDL_Color texteColor, TTF_Font *font, SDL_bool pFill, int event
		menu.liste_bouton[0] = createBouton(0, 400, 250, 50, -1, getNoir(255), "RETOUR SUR LE PONT", getBlanc(255), getFontHack(), SDL_TRUE, 10);

		//int x, int y, int w, int h, char *texte, SDL_Color color, TTF_Font *font
		menu.liste_texte[0] = createTexte(200, 50, 300, 50, "JEU PROGRAMMER PAR BLOVORAD", getBlanc(255),getFontHack());
		menu.liste_texte[1] = createTexte(200, 100, 200, 50, "FEATURING TON CLAVIER", getBlanc(255),getFontHack());
		menu.liste_texte[2] = createTexte(200, 150, 200, 50, "ACCEPTATION DE TON ECRAN", getBlanc(255),getFontHack());
		menu.liste_texte[3] = createTexte(200, 200, 200, 50, "ACCORD DE TA SOURIS", getBlanc(255),getFontHack());
		menu.liste_texte[4] = createTexte(250, 250, 200, 50, "AUTORISATION DE TES ECOUTEURS", getBlanc(255),getFontHack());
		menu.liste_texte[5] = createTexte(300, 300, 200, 50, "ET SURTOUT OUVERT PAR TOI ! ", getBlanc(255),getFontHack());
	}
	else
	{
		//int x, int y, int w, int h, int texture,SDL_Color panelColor, char *ptexte, SDL_Color texteColor, TTF_Font *font, SDL_bool pFill, int event
		menu.liste_bouton[0] = createBouton(0, 400, 250, 50, -1, getNoir(255), "BACK TO CONTROL ROOM", getBlanc(255), getFontHack(), SDL_TRUE, 10);

		//int x, int y, int w, int h, char *texte, SDL_Color color, TTF_Font *font
		menu.liste_texte[0] = createTexte(200, 50, 300, 50, "GAME MADE BY BLOVORAD", getBlanc(255),getFontHack());
		menu.liste_texte[1] = createTexte(200, 100, 200, 50, "FEATURING YOUR KEYBOARD", getBlanc(255),getFontHack());
		menu.liste_texte[2] = createTexte(200, 150, 200, 50, "ACCEPT BY YOUR SCREEN", getBlanc(255),getFontHack());
		menu.liste_texte[3] = createTexte(200, 200, 200, 50, "AGREEMENT BY YOUR MOUSE", getBlanc(255),getFontHack());
		menu.liste_texte[4] = createTexte(250, 250, 200, 50, "PERMIT BY YOUR EARPHONE", getBlanc(255),getFontHack());
		menu.liste_texte[5] = createTexte(300, 300, 200, 50, "AND ESPECIALLY LAUNCH BY YOU ! ", getBlanc(255),getFontHack());
	}

	cleanFontHack();
	SDL_Log("--------------INIT CREDIT TERMINER--------------\n");
}

void updateCredit(void)
{
	updateGroupeGui(&menu);
}

void drawCredit(void)
{
	drawGroupeGui(&menu);
}

void cleanCredit(void)
{
	SDL_Log("--------------CLEAN CREDIT EN COURS--------------\n");
	setPrintCredit(SDL_FALSE);
	cleanGroupeGui(&menu);
	SDL_Log("--------------CLEAN CREDIT TERMINER--------------\n");
}