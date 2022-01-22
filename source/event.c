#include "prototype.h"

void (*liste_event[DIM_EVENT])(void);

void initEvent(void)
{
	liste_event[0] = &quitGame;
	liste_event[1] = &startGame;
	liste_event[2] = &goToOption;
	liste_event[3] = &goToMenu;
	liste_event[4] = &backToMenu;
	liste_event[5] = &addVolumeFx;
	liste_event[6] = &removeVolumeFx;
	liste_event[7] = &addVolumeMusique;
	liste_event[8] = &removeVolumeMusique;
	liste_event[9] = &goToCredit;
	liste_event[10] = &backToMenuFromCredit;
	liste_event[11] = &resumeGame;
	liste_event[12] = &backToMenuFromGame;
	liste_event[13] = &setFullscreenOption;
	liste_event[14] = &setResolutionEvent;
	liste_event[15] = &localisationEvent;
}

void quitGame(void)
{
	FILE *fichier = fopen("source/fichier/config.txt", "w");
	if(fichier == NULL)
	{
		fprintf(stderr, "FILE OPEN: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if(getFullscreen() == SDL_FALSE)
	{
		fputs("0 ", fichier);
	}
	else if(getFullscreen() == SDL_TRUE)
	{
		fputs("1 ", fichier);
	}

	char fx[2];
	char musique[2];
	char espace[5] = " ";

	sprintf(fx, "%d", getVolumeFx());
	sprintf(musique, "%d", getVolumeMusic());

	fputs(musique, fichier);

	strcat(espace, fx);

	fputs(espace, fichier);

	if(getCurrentResolution() == 0)
	{
		fputs(" 0 ", fichier);
	}
	else if(getCurrentResolution() == 1)
	{
		fputs(" 1 ", fichier);
	}
	else if(getCurrentResolution() == 2)
	{	
		fputs(" 2 ", fichier);
	}
	else if(getCurrentResolution() == 3)
	{
		fputs(" 3 ", fichier);
	}
	else if(getCurrentResolution() == 4)
	{
		fputs(" 4 ", fichier);
	}

	char langue[2];

	sprintf(langue, "%d", getLocalisation());

	fputs(langue, fichier);

	fclose(fichier);
	fichier = NULL;

	setGo(SDL_FALSE);
}

void startGame(void)
{
	cleanMainMenu();
	initGame();
	startAcceleration();
}

void addVolumeMusique(void)
{
	playFx(11);
	upVolumeMusic();
}

void removeVolumeMusique(void)
{
	playFx(11);
	downVolumeMusic();
}	

void addVolumeFx(void)
{
	playFx(11);
	upVolumeFx();
}

void removeVolumeFx(void)
{
	playFx(11);
	downVolumeFx();
}

void goToOption(void)
{
	playFx(12);
	initOption();
	cleanMainMenu();
}

void goToMenu(void)
{
	playFx(12);
	initMainMenu();
	cleanOption();

	FILE *fichier = fopen("source/fichier/config.txt", "w");
	if(fichier == NULL)
	{
		fprintf(stderr, "FILE OPEN: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if(getFullscreen() == SDL_FALSE)
	{
		fputs("0 ", fichier);
	}
	else if(getFullscreen() == SDL_TRUE)
	{
		fputs("1 ", fichier);
	}

	char fx[2];
	char musique[2];
	char espace[5] = " ";

	sprintf(fx, "%d", getVolumeFx());
	sprintf(musique, "%d", getVolumeMusic());

	fputs(musique, fichier);

	strcat(espace, fx);

	fputs(espace, fichier);

	if(getCurrentResolution() == 0)
	{
		fputs(" 0 ", fichier);
	}
	else if(getCurrentResolution() == 1)
	{
		fputs(" 1 ", fichier);
	}
	else if(getCurrentResolution() == 2)
	{	
		fputs(" 2 ", fichier);
	}
	else if(getCurrentResolution() == 3)
	{
		fputs(" 3 ", fichier);
	}
	else if(getCurrentResolution() == 4)
	{
		fputs(" 4 ", fichier);
	}

	char langue[2];

	sprintf(langue, "%d", getLocalisation());

	fputs(langue, fichier);

	fclose(fichier);
	fichier = NULL;
}

void backToMenu(void)
{
	playFx(12);
	initMainMenu();
	cleanGame();
	stopAcceleration();
}

void goToCredit(void)
{
	playFx(12);
	initCredit();
	cleanMainMenu();
}

void backToMenuFromCredit(void)
{
	playFx(12);
	initMainMenu();
	cleanCredit();
}

void resumeGame(void)
{
	setPrintPause(SDL_FALSE);
	playFx(11);
}

void backToMenuFromGame(void)
{
	stopAcceleration();
	cleanGame();
	initMainMenu();
}

void setFullscreenOption(void)
{
	playFx(11);
	if(getFullscreen() == SDL_FALSE)
	{
		setFullscreen(SDL_TRUE);
	}
	else
	{
		setFullscreen(SDL_FALSE);
	}
	changeBoutonFullscreen();
}

void setResolutionEvent(void)
{
	playFx(11);

	setResolution();
	if(getCurrentResolution() == 0)
	{
		changeResolution(800, 600);
	}
	else if(getCurrentResolution() == 1)
	{
		changeResolution(1024, 768);
	}
	else if(getCurrentResolution() == 2)
	{
		changeResolution(1360, 768);
	}
	else if(getCurrentResolution() == 3)
	{
		changeResolution(1600, 900);
	}
	else if(getCurrentResolution() == 4)
	{
		changeResolution(1920, 1080);
	}
	restartXPos();
}

void localisationEvent(void)
{
	playFx(11);
	changeLocalisation();
	cleanOption();
	initOption();
}

void playEvent(int event)
{
	if(event > -1 && event < DIM_EVENT)
	{
		(*liste_event[event])();
	}
}