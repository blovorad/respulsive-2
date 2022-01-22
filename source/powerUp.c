#include "prototype.h"

static PowerUp *liste_powerUp;
static int nbPowerUp;
static int nbAmmoUp;
static int nbShieldUp;
static SDL_Rect shield;
static SDL_Rect ammo;

static void activePowerUp(int type);

void initPowerUp(void)
{
	SDL_Log("----------INIT POWERUP EN COURS----------\n");
	nbPowerUp = 5;
	nbAmmoUp = 0;
	nbShieldUp = 0;

	shield.x = 16;
	shield.y = 8;
	shield.w = 43;
	shield.h = 43;

	ammo.x = 118;
	ammo.y = 17;
	ammo.w = 43;
	ammo.h = 43;

	liste_powerUp = malloc(sizeof(PowerUp) * nbPowerUp);
	if(liste_powerUp == NULL)
	{
		fprintf(stderr, "malloc; %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < nbPowerUp; i++)
	{
		liste_powerUp[i].alive = SDL_FALSE;
		liste_powerUp[i].fill = SDL_TRUE;
		liste_powerUp[i].type = 0;
		liste_powerUp[i].couleur = getNoir(255);
		liste_powerUp[i].collider.couleur = getRouge(255);
		liste_powerUp[i].collider.fill = SDL_FALSE;
		liste_powerUp[i].vitesse.x = 0;
		liste_powerUp[i].vitesse.y = 0;
	}
	SDL_Log("----------INIT POWERUP TERMINER----------\n");
}

void updatePowerUp(void)
{
	for(int i = 0; i < nbPowerUp; i++)
	{
		if(liste_powerUp[i].alive)
		{
			liste_powerUp[i].position.x += liste_powerUp[i].vitesse.x;
			liste_powerUp[i].position.y += liste_powerUp[i].vitesse.y;
			liste_powerUp[i].collider.dimension.x += liste_powerUp[i].vitesse.x;
			liste_powerUp[i].collider.dimension.y += liste_powerUp[i].vitesse.y;

			if(collide(getPlayerCollider(), liste_powerUp[i].collider.dimension))
			{
				if(isPlayerAlive())
				{
					playFx(6);
					activePowerUp(liste_powerUp[i].type);
					liste_powerUp[i].alive = SDL_FALSE;
				}
			}
			else if(liste_powerUp[i].position.y > getHeight())
			{
				if(liste_powerUp[i].type == 1)
				{
					nbAmmoUp--;
				}
				else if(liste_powerUp[i].type == 2)
				{
					nbShieldUp--;
				}
				liste_powerUp[i].alive = SDL_FALSE;
			}
		}
	}
	if(getShieldCharge() < 100 && nbShieldUp == 0)
	{
		addPowerUp(2);
	}
}

void drawPowerUp(void)
{
	for(int i = 0; i < nbPowerUp; i++)
	{
		if(liste_powerUp[i].alive)
		{
			if(liste_powerUp[i].type == 2)
			{
				drawTexture(getTexture(4), &liste_powerUp[i].position, &shield);
			}
			else
			{
				drawTexture(getTexture(4), &liste_powerUp[i].position, &ammo);
			}
		}
	}
}

void cleanPowerUp(void)
{
	SDL_Log("----------CLEAN POWERUP EN COURS----------\n");
	if(liste_powerUp != NULL)
	{
		free(liste_powerUp);
		liste_powerUp = NULL;
	}
	SDL_Log("----------CLEAN POWERUP TERMINER----------\n");
}

void addPowerUp(int type)
{
	int i = 0;
	SDL_bool ajout = SDL_FALSE;

	if(isPlayerAlive())
	{
		while(i < nbPowerUp && ajout == SDL_FALSE)
		{
			if(liste_powerUp[i].alive == SDL_FALSE)
			{
				liste_powerUp[i].type = type;
				liste_powerUp[i].position.w = 20 * getScaleX();
				liste_powerUp[i].position.h = 20 * getScaleY();
				liste_powerUp[i].position.x = rand() % getWidth();
				liste_powerUp[i].position.y = (-300 * getScaleY()) - liste_powerUp[i].position.h;
				liste_powerUp[i].alive = SDL_TRUE;

				if(liste_powerUp[i].position.x > getWidth() - liste_powerUp[i].position.w)
				{
					liste_powerUp[i].position.x = getWidth() - liste_powerUp[i].position.w;
				}

				liste_powerUp[i].collider.dimension = liste_powerUp[i].position;

				if(type == 1)
				{
					nbAmmoUp++;
					liste_powerUp[i].couleur = getMarron(255);
					liste_powerUp[i].vitesse.x = 0;
					liste_powerUp[i].vitesse.y = 5;
				}
				if(type == 2)
				{
					nbShieldUp++;
					liste_powerUp[i].couleur = getBleu(255);
					liste_powerUp[i].vitesse.x = 0;
					liste_powerUp[i].vitesse.y = 5;
				}

				ajout = SDL_TRUE;
			}
			i++;
		}
	}
}

static void activePowerUp(int type)
{
	if(type == 1)
	{
		nbAmmoUp--;
		giveMissileToPlayer();
	}
	else if(type == 2)
	{
		nbShieldUp--;
		removeShieldCharge(20);
	}
}

int getNbAmmoUp(void)
{
	return nbAmmoUp;
}