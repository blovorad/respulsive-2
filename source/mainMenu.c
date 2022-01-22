#include "prototype.h"

static SDL_bool anime;

static GroupeGui menu;

void initMainMenu(void)
{
	SDL_Log("--------------INIT MAIN MENU EN COURS--------------\n");
	setPrintMainMenu(SDL_TRUE);
	initGroupeGui(&menu, 0, 7, 4, 2);

	initFontHack();
	anime = SDL_TRUE;

	if(getLocalisation() == 0)
	{
		//int x, int y, int w, int h, int texture,SDL_Color panelColor, char *ptexte, SDL_Color texteColor, TTF_Font *font, SDL_bool pFill, int event
		menu.liste_bouton[0] = createBouton(0, 200, 250, 50, -1, getNoir(255), "EN AVANT", getBlanc(255), getFontHack(), SDL_TRUE, 1);
		menu.liste_bouton[1] = createBouton(0, 250, 250, 50, -1, getNoir(255), "SALLE DES MACHINES", getBlanc(255), getFontHack(), SDL_TRUE, 2);
		menu.liste_bouton[2] = createBouton(0, 300, 250, 50, -1, getNoir(255), "EQUIPAGE", getBlanc(255), getFontHack(), SDL_TRUE, 9);
		menu.liste_bouton[3] = createBouton(0, 350, 250, 50, -1, getNoir(255), "DORTOIR", getBlanc(255), getFontHack(), SDL_TRUE, 0);

		//int x, int y, int w, int h, int texture, SDL_Color color, SDL_bool pFill
		menu.liste_panel[0] = createPanel(0, 199, 252, 202, -1, getBlanc(255), SDL_FALSE);
		menu.liste_panel[1] = createPanel(-200, 50, 200, 100, -1, getBlanc(255), SDL_TRUE);

		//int x, int y, int w, int h, char *texte, SDL_Color color, TTF_Font *font
		menu.liste_texte[0] = createTexte(0, 50, 200, 50, "BIENVENU", getNoir(255), getFontHack());
		menu.liste_texte[1] = createTexte(0, 75, 200, 50, "DANS", getNoir(255), getFontHack());
		menu.liste_texte[2] = createTexte(0, 100, 200, 50, "REPULSIVE II", getNoir(255), getFontHack());
		menu.liste_texte[3] = createTexte(400, 175, 200, 50, "LA PLANETE CAPITAL EST ATTAQUER PAR LA MENACE ROUGE", getBlanc(255), getFontHack());
		menu.liste_texte[4] = createTexte(400, 200, 200, 50, "ETANT LE SEUL VAISSEAU DISPONIBLE", getBlanc(255), getFontHack());
		menu.liste_texte[5] = createTexte(400, 225, 200, 50, "VOTRE DEVOIR EST DE DEFENDRE LA PLANETE", getBlanc(255), getFontHack());
		menu.liste_texte[6] = createTexte(400, 250, 200, 50, "LE SORT DE LA PLANETE NE DEPEND QUE DE VOUS ET VOTRE PUISSANCE", getBlanc(255), getFontHack());
	}
	else
	{
		//int x, int y, int w, int h, int texture,SDL_Color panelColor, char *ptexte, SDL_Color texteColor, TTF_Font *font, SDL_bool pFill, int event
		menu.liste_bouton[0] = createBouton(0, 200, 250, 50, -1, getNoir(255), "FORWARD", getBlanc(255), getFontHack(), SDL_TRUE, 1);
		menu.liste_bouton[1] = createBouton(0, 250, 250, 50, -1, getNoir(255), "MACHINE ROOM", getBlanc(255), getFontHack(), SDL_TRUE, 2);
		menu.liste_bouton[2] = createBouton(0, 300, 250, 50, -1, getNoir(255), "CREW", getBlanc(255), getFontHack(), SDL_TRUE, 9);
		menu.liste_bouton[3] = createBouton(0, 350, 250, 50, -1, getNoir(255), "DORMITORY", getBlanc(255), getFontHack(), SDL_TRUE, 0);

		//int x, int y, int w, int h, int texture, SDL_Color color, SDL_bool pFill
		menu.liste_panel[0] = createPanel(0, 199, 252, 202, -1, getBlanc(255), SDL_FALSE);
		menu.liste_panel[1] = createPanel(-200, 50, 200, 100, -1, getBlanc(255), SDL_TRUE);

		//int x, int y, int w, int h, char *texte, SDL_Color color, TTF_Font *font
		menu.liste_texte[0] = createTexte(0, 50, 200, 50, "WELCOME", getNoir(255), getFontHack());
		menu.liste_texte[1] = createTexte(0, 75, 200, 50, "IN", getNoir(255), getFontHack());
		menu.liste_texte[2] = createTexte(0, 100, 200, 50, "REPULSIVE II", getNoir(255), getFontHack());
		menu.liste_texte[3] = createTexte(400, 175, 200, 50, "CAPITAL PLANET IS UNDER ATACK BY RED THREAT", getBlanc(255), getFontHack());
		menu.liste_texte[4] = createTexte(400, 200, 200, 50, "YOU ARE THE ONLY SHIP AVAILABLE", getBlanc(255), getFontHack());
		menu.liste_texte[5] = createTexte(400, 225, 200, 50, "YOUR DUTY IS TO DEFEND THE PLANET", getBlanc(255), getFontHack());
		menu.liste_texte[6] = createTexte(400, 250, 200, 50, "THE FATE OF THE PLANET DEPEND ONLY OF YOU AND YOUR TALENT", getBlanc(255), getFontHack());
	}

	cleanFontHack();

	SDL_Log("--------------INIT MAIN MENU TERMINER--------------\n");
}

void updateMainMenu(void)
{
	if(anime != SDL_FALSE)
	{
		if(menu.liste_panel[1].dimension.x < 0)
		{
			menu.liste_panel[1].dimension.x += (5 * getScaleX());
		}
		else
		{
			menu.liste_panel[1].dimension.x = 0;
			anime = SDL_FALSE;
		}
	}
	updateGroupeGui(&menu);
}

void drawMainMenu(void)
{
	drawGroupeGui(&menu);
}

void cleanMainMenu(void)
{
	SDL_Log("--------------CLEAN MAIN MENU EN COURS--------------\n");
	setPrintMainMenu(SDL_FALSE);
	cleanGroupeGui(&menu);
	SDL_Log("--------------CLEAN MAIN MENU TERMINER--------------\n");
}
