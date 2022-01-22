#include "prototype.h"

static Shoot *liste_shoot;
static int nbShoot;

void initShoot(void)
{
	SDL_Log("----------INIT SHOOT EN COURS----------\n");
	nbShoot = 100;

	liste_shoot = malloc(sizeof(Shoot)* nbShoot);
	if(liste_shoot == NULL)
	{
		fprintf(stderr, "malloc; %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < nbShoot; i++)
	{
		liste_shoot[i].alive = SDL_FALSE;
		liste_shoot[i].line.couleur = getVert(255);
		liste_shoot[i].line.longueur = 5;

		liste_shoot[i].isSuperShoot = SDL_FALSE;
		liste_shoot[i].isExplode = SDL_FALSE;
		liste_shoot[i].timerExplosion.ms = 700;
		liste_shoot[i].timerExplosion.previousTime = 0;
		liste_shoot[i].timerExplosion.currentTime = 0;
		liste_shoot[i].explosion.cx = 0;
		liste_shoot[i].explosion.cy = 0;
		liste_shoot[i].explosion.rayon = 0;
		liste_shoot[i].explosion.couleur = getJaune(255);
		liste_shoot[i].explosion.vitesse.x = 0;
		liste_shoot[i].explosion.vitesse.y = 0;

		liste_shoot[i].explosion.collider.x = 0;
		liste_shoot[i].explosion.collider.y = 0;
		liste_shoot[i].explosion.collider.w = 0;
		liste_shoot[i].explosion.collider.h = 0;
		liste_shoot[i].explosion.fill = SDL_FALSE;

	}

	SDL_Log("----------INIT SHOOT TERMINER----------\n");
}

void updateShoot(void)
{
	int max = getNombreHostile();
	for(int i = 0; i < nbShoot; i++)
	{
		if(liste_shoot[i].alive)
		{
			liste_shoot[i].line.y1 += liste_shoot[i].line.vitesse.y;
			liste_shoot[i].line.y2 += liste_shoot[i].line.vitesse.y;
			liste_shoot[i].collider.dimension.y += liste_shoot[i].line.vitesse.y;

			if(getIfHasShield())
			{
				if(checkCollide(liste_shoot[i].collider.dimension, getShieldCollider()))
				{
					if(isPlayerAlive())
					{
						removeShieldCharge(-20);
						liste_shoot[i].alive = SDL_FALSE;
					}
				}
			}
			else
			{
				if(checkCollide(liste_shoot[i].collider.dimension, getPlayerCollider()) && isPlayerAlive())
				{
					liste_shoot[i].alive = SDL_FALSE;
					launchExplosion();
					setPlayerAlive(SDL_FALSE);
					startAcceleration();
					playFx(3);
				}
			}

			for(int j = 0; j < max; j++)
			{
				if(checkCollide(getHostileCollider(j), liste_shoot[i].collider.dimension))
				{
					if(getIfIsExplode(j) == SDL_FALSE && liste_shoot[i].isSuperShoot == SDL_FALSE)
					{
						if(liste_shoot[i].line.vitesse.y < 0)
						{
							playFx(7);
							setNoAliveHostile(j);
							liste_shoot[i].alive = SDL_FALSE;
						}
					}
					if(liste_shoot[i].isSuperShoot)
					{
						playFx(0);
						liste_shoot[i].alive = SDL_FALSE;
						setNoAliveHostile(j);
						liste_shoot[i].isExplode = SDL_TRUE;
						liste_shoot[i].timerExplosion.previousTime = SDL_GetTicks();
						liste_shoot[i].explosion.cx = liste_shoot[i].line.x1;
						liste_shoot[i].explosion.cy = liste_shoot[i].line.y1;
					}
				}
			}

		}
		if(liste_shoot[i].isExplode)
		{
			liste_shoot[i].timerExplosion.currentTime = SDL_GetTicks();

			liste_shoot[i].explosion.rayon += 5 * getScaleX();
			liste_shoot[i].explosion.collider.x = liste_shoot[i].explosion.cx - liste_shoot[i].explosion.rayon;
			liste_shoot[i].explosion.collider.y = liste_shoot[i].explosion.cy - liste_shoot[i].explosion.rayon;
			liste_shoot[i].explosion.collider.w = 2 * liste_shoot[i].explosion.rayon;
			liste_shoot[i].explosion.collider.h = 2 * liste_shoot[i].explosion.rayon;

			for(int j = 0; j < max; j++)
			{
				if(checkCollide(getHostileCollider(j), liste_shoot[i].explosion.collider))
				{
					setNoAliveHostile(j);
				}
			}


			if(liste_shoot[i].timerExplosion.currentTime >= liste_shoot[i].timerExplosion.previousTime + liste_shoot[i].timerExplosion.ms)
			{
				liste_shoot[i].isExplode = SDL_FALSE;
			}
		}

		if(liste_shoot[i].line.y2 < 0)
		{
			liste_shoot[i].alive = SDL_FALSE;
		}
		else if(liste_shoot[i].line.y1 > getHeight())
		{
			liste_shoot[i].alive = SDL_FALSE;
		}
	}
}

void drawShoot(void)
{
	for(int i = 0; i < nbShoot; i++)
	{
		if(liste_shoot[i].alive)
		{
			drawLine(liste_shoot[i].line.x1, liste_shoot[i].line.y1, liste_shoot[i].line.x2, liste_shoot[i].line.y2, &liste_shoot[i].line.couleur);
		}
		if(liste_shoot[i].isSuperShoot && liste_shoot[i].isExplode)
		{
			drawDisque(liste_shoot[i].explosion);
		}
	}
}

void cleanShoot(void)
{
	SDL_Log("----------CLEAN SHOOT EN COURS----------\n");
	if(liste_shoot != NULL)
	{
		free(liste_shoot);
		liste_shoot = NULL;
	}
	SDL_Log("----------CLEAN SHOOT TERMINER----------\n");
}

void addShoot(int x, int y, int vy, SDL_bool isSuper)
{
	int i = 0;
	while((liste_shoot[i].alive == SDL_TRUE || liste_shoot[i].isExplode == SDL_TRUE) && i < nbShoot)
	{
		i++;
	}

	if(i >= nbShoot)
	{
		i = nbShoot - 1;
	}

	if(liste_shoot[i].alive == SDL_FALSE && liste_shoot[i].isExplode == SDL_FALSE)
	{
		if(isSuper)
		{
			liste_shoot[i].line.longueur = 10 * getScaleY();
		}
		else
		{
			liste_shoot[i].line.longueur = 5 * getScaleY();
		}

		liste_shoot[i].alive = SDL_TRUE;
		liste_shoot[i].line.x2 = x;
		liste_shoot[i].line.y2 = y;
		liste_shoot[i].line.x1 = x;
		liste_shoot[i].line.y1 = liste_shoot[i].line.y2 + (liste_shoot[i].line.longueur * getScaleY());

		liste_shoot[i].collider.fill = SDL_FALSE;
		liste_shoot[i].collider.couleur = getRouge(255);
		liste_shoot[i].collider.dimension.x = liste_shoot[i].line.x2;
		liste_shoot[i].collider.dimension.y = liste_shoot[i].line.y2;
		liste_shoot[i].collider.dimension.w = 1 * getScaleX();
		liste_shoot[i].collider.dimension.h = liste_shoot[i].line.longueur * getScaleY();

		liste_shoot[i].line.vitesse.x = 0;
		if(isSuper)
		{
			liste_shoot[i].line.vitesse.y = (vy * 2) * getScaleY();
		}
		else
		{
			liste_shoot[i].line.vitesse.y = vy * getScaleY();
		}
		if(isSuper)
		{
			liste_shoot[i].line.couleur = getOcre(255);
		}
		else
		{
			liste_shoot[i].line.couleur = getVert(255);
		}
		if(liste_shoot[i].line.vitesse.y > 0)
		{
			liste_shoot[i].line.couleur = getRouge(255);
		}

		liste_shoot[i].isSuperShoot = isSuper;
		liste_shoot[i].isExplode = SDL_FALSE;
		liste_shoot[i].timerExplosion.previousTime = 0;
		liste_shoot[i].timerExplosion.currentTime = 0;
		liste_shoot[i].explosion.cx = 0;
		liste_shoot[i].explosion.cy = 0;
		liste_shoot[i].explosion.rayon = 0;
		liste_shoot[i].explosion.vitesse.x = 0;
		liste_shoot[i].explosion.vitesse.y = 0;

		liste_shoot[i].explosion.collider.x = 0;
		liste_shoot[i].explosion.collider.y = 0;
		liste_shoot[i].explosion.collider.w = 0;
		liste_shoot[i].explosion.collider.h = 0;
		liste_shoot[i].explosion.fill = SDL_FALSE;
	}
}