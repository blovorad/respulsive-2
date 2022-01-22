#include "prototype.h"

static Ligne *line;
static int nbLine;
static SDL_bool accelerationEtat;

void initGameBackground(void)
{

	SDL_Log("----------INIT GAMEBACKGROUND EN COURS----------\n");
	nbLine = 500;

	accelerationEtat = SDL_FALSE;

	line = malloc(sizeof(Ligne) * nbLine);
	if(line == NULL)
	{
		fprintf(stderr, "malloc; %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < nbLine; i++)
	{
		line[i].couleur = getBlanc(rand() % 50 + 75);
		line[i].longueur = 1 * getScaleY();

		line[i].vitesse.x = 0;
		line[i].vitesse.y = 0;

		line[i].x1 = rand() % getWidth();
		line[i].x2 = line[i].x1;
		line[i].y1 = rand() % (getHeight() * 2);
		line[i].y2 = line[i].y1 + line[i].longueur;
		line[i].minSpeed = rand() % 3 + 1;
	}

	SDL_Log("----------INIT GAMEBACKGROUND TERMINER----------\n");
}

void updateGameBackground(void)
{
	if(accelerationEtat)
	{
		for(int i = 0; i < nbLine; i++)
		{
			if(line[i].vitesse.y < 25 * getScaleY())
			{
				line[i].vitesse.y++;
			}
			else if(line[i].vitesse.y > 25 * getScaleY())
			{
				line[i].vitesse.y = 25 * getScaleY();
			}
			if(line[i].longueur < 20 * getScaleY())
			{
				line[i].longueur++;
				line[i].y2 = line[i].y1 + line[i].longueur;
			}
			else if(line[i].longueur > 20 * getScaleY())
			{
				line[i].longueur = 20 * getScaleY();
				line[i].y2 = line[i].y1 + line[i].longueur;
			}
		}
	}
	else
	{
		for(int i = 0; i < nbLine; i++)
		{
			if(line[i].vitesse.y > line[i].minSpeed)
			{
				line[i].vitesse.y--;
			}
			else if(line[i].vitesse.y < line[i].minSpeed)
			{
				line[i].vitesse.y = line[i].minSpeed;
			}
			if(line[i].longueur > 1)
			{
				line[i].longueur--;
				line[i].y2 = line[i].y1 + line[i].longueur;
			}
			else if(line[i].longueur < 1)
			{
				line[i].longueur = 1;
				line[i].y2 = line[i].y1 + line[i].longueur;
			}
		}
	}

	for(int i = 0; i < nbLine; i++)
	{
		line[i].y1 += line[i].vitesse.y;
		line[i].y2 += line[i].vitesse.y;

		if(line[i].y1 > getHeight())
		{
			line[i].x1 = rand() % getWidth();
			line[i].x2 = line[i].x1;
			line[i].y1 = -(rand() % getHeight());
			line[i].y2 = line[i].y1 + line[i].longueur;
		}
	}
}

void drawGameBackground(void)
{
	for(int i = 0; i < nbLine; i++)
	{
		drawLine(line[i].x1, line[i].y1, line[i].x2, line[i].y2, &line[i].couleur);
	}
}

void cleanGameBackground(void)
{
	SDL_Log("----------CLEAN GAMEBACKGROUND EN COURS----------\n");
	if(line != NULL)
	{
		free(line);
		line = NULL;
	}
	SDL_Log("----------CLEAN GAMEBACKGROUND TERMINER----------\n");
}

void restartXPos(void)
{
	for(int i = 0; i < nbLine; i++)
	{
		line[i].longueur = 1 * getScaleY();

		line[i].x1 = rand() % getWidth();
		line[i].x2 = line[i].x1;
		line[i].y1 *= getScaleY();
		line[i].y2 = line[i].y1 + line[i].longueur;
	}
}

void startAcceleration(void)
{
	accelerationEtat = SDL_TRUE;
}

void stopAcceleration(void)
{
	accelerationEtat = SDL_FALSE;
}

SDL_bool getAccelerationEtat(void)
{
	return accelerationEtat;
}