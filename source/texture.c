#include "prototype.h"

static SDL_Texture *liste_texture[5];
static int nbTexture;

void initTexture(void)
{
	nbTexture = 5;
	liste_texture[0] = createTexture("source/graphics/ship.png", NULL);
	liste_texture[1] = createTexture("source/graphics/ship2.png", NULL);
	liste_texture[2] = createTexture("source/graphics/ship3.png", NULL);
	liste_texture[3] = createTexture("source/graphics/ship4.png", NULL);
	liste_texture[4] = createTexture("source/graphics/Sheet_Powerups.png", NULL);

}

SDL_Texture *createTexture(char *chemin, SDL_Rect *rect)
{
	//Variable obligatoire pour créer une texture
	SDL_Texture *texture = NULL;
	SDL_Surface *surface = IMG_Load(chemin);

	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255));

	//Controle si l'image a bien été charger dans la surface
	if(surface == NULL)	
	{
		SDL_Log("IMPOSSIBLE DE LOAD LA TEXTURE DANS LA SURFACE :%s",SDL_GetError());
		exit(EXIT_FAILURE);
	}

	//fonction qui retourne la texture si elle est créer
	texture = SDL_CreateTextureFromSurface(getRenderer(), surface);
	//plus besoin de la surface, FREE OBLIGATOIRE
	SDL_FreeSurface(surface);
	surface = NULL;

	//On regarde si pas d'erreur
	if(texture == NULL)
	{
		SDL_Log("IMPOSSIBLE DE CREATE TEXTURE POUR LA SURFACE :%s",SDL_GetError());
		exit(EXIT_FAILURE);
	}

	//Si on lui a passer un rect, alors on donne ses dimensions, sinon ça veut dire qu'on s'en fout
	if(rect != NULL)
	{
		if(SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h) != 0)
		{
			SDL_Log("IMPOSSIBLE DE PRENDRE DIMENSION TEXTURE :%s",SDL_GetError());
			exit(EXIT_FAILURE);
		}
	}

	//return de la texture que l'on a créer, on retourne l'adresse de cette texture en vrai !
	return texture;
}

SDL_Texture *getTexture(int texture)
{
	return liste_texture[texture];
}

void cleanTexture(void)
{
	SDL_Log("CLEAN TEXTURE EN COURS\n");
	for(int i = 0; i < nbTexture; i++)
	{
		if(liste_texture[i] != NULL)
		{
			SDL_DestroyTexture(liste_texture[i]);
			liste_texture[i] = NULL;
		}
	}
	SDL_Log("CLEAN TEXTURE TERMINER\n");
}