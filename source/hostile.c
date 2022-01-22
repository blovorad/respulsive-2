#include "prototype.h"

static Hostile *liste_hostile;
static int nbHostile;
static int minVitesse;
static void shoot(int i);

void initHostile(void)
{
	SDL_Log("----------INIT HOSTILE EN COURS----------\n");
	nbHostile = 5;
	SDL_bool collision = SDL_FALSE;
	minVitesse = 2;

	liste_hostile = malloc(sizeof(Hostile) * nbHostile);
	if(liste_hostile == NULL)
	{
		fprintf(stderr, "malloc; %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < nbHostile; i++)
	{
		int type = rand() % 3;
		while(type == 0)
		{
			type = rand() % 3;
		}

		liste_hostile[i].type = type;
		if(liste_hostile[i].type == 1)
		{
			liste_hostile[i].texture = 1;
			liste_hostile[i].timeToShoot.ms = 8000;
		}
		else if(liste_hostile[i].type == 2)
		{
			liste_hostile[i].texture = 2;
			liste_hostile[i].timeToShoot.ms = 5000;
		}

		liste_hostile[i].angle = 180;
		liste_hostile[i].couleur = getRouge(255);

		liste_hostile[i].position.w = 32 * getScaleX();
		liste_hostile[i].position.h = 32 * getScaleY();
		liste_hostile[i].position.x = rand() % getWidth();
		liste_hostile[i].position.y = -(rand() % getHeight());

		liste_hostile[i].collider.couleur = getRouge(255);
		liste_hostile[i].collider.fill = SDL_FALSE;
		liste_hostile[i].collider.dimension.w = 32 * getScaleX();
		liste_hostile[i].collider.dimension.h = 28 * getScaleY();

		liste_hostile[i].timeToShoot.currentTime = 0;
		liste_hostile[i].timeToShoot.previousTime = 0;
		liste_hostile[i].hasShoot = SDL_FALSE;

		liste_hostile[i].nbExplosion = 5;
		liste_hostile[i].explosion = malloc(sizeof(Cercle) * liste_hostile[i].nbExplosion);
		if(liste_hostile[i].explosion == NULL)
		{
			fprintf(stderr, "malloc; %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		for(int j = 0; j < liste_hostile[i].nbExplosion; j++)
		{
			liste_hostile[i].explosion[j].cx = 0;
			liste_hostile[i].explosion[j].cy = 0;
			liste_hostile[i].explosion[j].couleur = getJaune(255);
			liste_hostile[i].explosion[j].rayon = 0;
			liste_hostile[i].explosion[j].vitesse.x = 0;
			liste_hostile[i].explosion[j].vitesse.y = 0;
		}
		liste_hostile[i].timerExplosion.ms = 300;
		liste_hostile[i].timerExplosion.previousTime = 0;
		liste_hostile[i].timerExplosion.currentTime = 0;
		liste_hostile[i].isExplode = SDL_FALSE;

		liste_hostile[i].alive = SDL_TRUE;

		liste_hostile[i].timerMoteur.ms = 50;
		liste_hostile[i].timerMoteur.previousTime = SDL_GetTicks();
		liste_hostile[i].timerMoteur.currentTime = 0;

		do
		{
			collision = SDL_FALSE;
			for(int j = 0; j < nbHostile; j++)
			{
				if(j != i)
				{
					if(checkCollide(liste_hostile[i].position, liste_hostile[j].position) 
						|| liste_hostile[i].position.x < liste_hostile[i].position.w 
						|| liste_hostile[i].position.x > getWidth() - liste_hostile[i].position.w
						|| liste_hostile[i].position.y > 0 - liste_hostile[i].position.h)
					{
						liste_hostile[i].position.x = rand() % getWidth();
						liste_hostile[i].position.y = -(rand() % getHeight() / 2);
						collision = SDL_TRUE;
					}
				}
			}
		}while(collision);

		liste_hostile[i].collider.dimension.x = liste_hostile[i].position.x;
		liste_hostile[i].collider.dimension.y = liste_hostile[i].position.y + 4 * getScaleY();
		/*liste_hostile[i].moteur.cx = liste_hostile[i].position.x + liste_hostile[i].position.w / 2;
		liste_hostile[i].moteur.cy = liste_hostile[i].collider.dimension.y;
		liste_hostile[i].moteur.couleur = getRouge(255);
		liste_hostile[i].moteur.vitesse.x = 0;
		liste_hostile[i].moteur.vitesse.y = 0;
		liste_hostile[i].moteur.rayon = 3 * getScaleY();*/
	}
	SDL_Log("----------INIT HOSTILE TERMINER----------\n");
}

void updateHostile(void)
{
	for(int i = 0; i < nbHostile; i++)
	{
		if(liste_hostile[i].alive)
		{
			/*liste_hostile[i].timerMoteur.currentTime = SDL_GetTicks();
			if(liste_hostile[i].timerMoteur.currentTime >= liste_hostile[i].timerMoteur.previousTime + liste_hostile[i].timerMoteur.ms)
			{
				liste_hostile[i].moteur.rayon++;
				if(liste_hostile[i].moteur.rayon > 8 * getScaleY())
				{
					liste_hostile[i].moteur.rayon = 3 * getScaleY();
				}

				liste_hostile[i].timerMoteur.previousTime = liste_hostile[i].timerMoteur.currentTime;
			}*/

			if(!getPrintPause())
			{
				liste_hostile[i].position.x += liste_hostile[i].vitesse.x;
				liste_hostile[i].position.y += liste_hostile[i].vitesse.y;
				liste_hostile[i].collider.dimension.x += liste_hostile[i].vitesse.x;
				liste_hostile[i].collider.dimension.y += liste_hostile[i].vitesse.y;
				//liste_hostile[i].moteur.cx = liste_hostile[i].position.x + liste_hostile[i].position.w / 2;
				//liste_hostile[i].moteur.cy = liste_hostile[i].collider.dimension.y;

				for(int j = 0; j < nbHostile; j++)
				{
					if(j != i)
					{
						if(checkCollide(liste_hostile[i].collider.dimension, liste_hostile[j].collider.dimension))
						{
							int x1 = liste_hostile[j].position.x + liste_hostile[j].position.w;
							int x2 = liste_hostile[i].position.x + liste_hostile[i].position.w;
							int y1 = liste_hostile[j].position.y + liste_hostile[j].position.h;
							int y2 = liste_hostile[i].position.y + liste_hostile[i].position.h;
							double angle = atan2(y2 - y1, x2 - x1);
							liste_hostile[i].vitesse.x = minVitesse * cos(angle);
						}
					}
				}

				if(liste_hostile[i].position.y > getHeight() - 200 * getScaleY())
				{
					if(isPlayerAlive())
					{
						liste_hostile[i].vitesse.y *= -1;
						if(rand() % 2 == 1)
						{
							liste_hostile[i].vitesse.x = minVitesse;
						}
						else
						{
							liste_hostile[i].vitesse.x = -minVitesse;	
						}
					}
					else
					{
						liste_hostile[i].vitesse.y = 10;
						liste_hostile[i].vitesse.x = 0;
					}
				}
				if(liste_hostile[i].position.y < 0 + 30 * getScaleY() && liste_hostile[i].vitesse.y < 0)
				{
					if(isPlayerAlive())
					{
						liste_hostile[i].vitesse.y = getVitesseType(liste_hostile[i].type);
						liste_hostile[i].vitesse.x = 0;
					}
					else
					{
						liste_hostile[i].vitesse.y = 10 * getScaleY();
					}
				}

				if(liste_hostile[i].position.x < 0)
				{
					liste_hostile[i].position.x = 0;
					liste_hostile[i].collider.dimension.x = liste_hostile[i].position.x;
					liste_hostile[i].vitesse.x *= -1;
				}
				else if(liste_hostile[i].position.x + liste_hostile[i].position.w > getWidth())
				{
					liste_hostile[i].position.x = getWidth() - liste_hostile[i].position.w;
					liste_hostile[i].collider.dimension.x = liste_hostile[i].position.x;
					liste_hostile[i].vitesse.x *= -1;
				}

				if(liste_hostile[i].position.y < 0)
				{
					if(isPlayerAlive())
					{
						liste_hostile[i].vitesse.y = 5 * getScaleY();
					}
					else
					{
						liste_hostile[i].vitesse.y = 10 * getScaleY();
					}
				}
			}

			if(liste_hostile[i].position.y + liste_hostile[i].position.h > 0)
			{
				if(liste_hostile[i].hasShoot)
				{
					liste_hostile[i].timeToShoot.currentTime = SDL_GetTicks();
					if(liste_hostile[i].timeToShoot.currentTime >= liste_hostile[i].timeToShoot.previousTime + liste_hostile[i].timeToShoot.ms)
					{
						if(!getPrintPause())
						{
							liste_hostile[i].hasShoot = SDL_FALSE;
						}
						else
						{
							liste_hostile[i].timeToShoot.previousTime = liste_hostile[i].timeToShoot.currentTime;
						}
					}
				}
				if(liste_hostile[i].hasShoot == SDL_FALSE)
				{
					if(!getPrintPause())
					{
						playFx(1);
						shoot(i);
					}
				}
			}

			if(liste_hostile[i].position.y > getHeight())
			{
				addHostile(i);
			}
		}
		else
		{
			if(!getPrintPause())
			{
				if(liste_hostile[i].isExplode)
				{
					liste_hostile[i].timerExplosion.currentTime = SDL_GetTicks();
					for(int j = 0; j < liste_hostile[i].nbExplosion; j++)
					{
						liste_hostile[i].explosion[j].rayon += 3;
					}
					if(liste_hostile[i].timerExplosion.currentTime >= liste_hostile[i].timerExplosion.previousTime + liste_hostile[i].timerExplosion.ms)
					{
						liste_hostile[i].isExplode = SDL_FALSE;
						addHostile(i);
						if(liste_hostile[i].type == 3)
						{
							addScore(30);
						}
						else
						{
							addScore(10);
						}
					}
				}
			}
		}
	}
}

void drawHostile(void)
{
	for(int i = 0; i < nbHostile; i++)
	{
		if(liste_hostile[i].alive)
		{
			//drawCercle(liste_hostile[i].moteur);
			drawTextureEx(getTexture(liste_hostile[i].texture), &liste_hostile[i].position, NULL, NULL, liste_hostile[i].angle, SDL_FLIP_NONE);
			//drawRect(&liste_hostile[i].collider.dimension, &liste_hostile[i].collider.fill, &liste_hostile[i].collider.couleur);
		}
		else
		{
			if(liste_hostile[i].isExplode)
			{
				for(int j = 0; j < liste_hostile[i].nbExplosion; j++)
				{
					drawDisque(liste_hostile[i].explosion[j]);
				}
			}
		}
	}
}

void cleanHostile(void)
{
	SDL_Log("----------CLEAN HOSTILE EN COURS----------\n");
	for(int i = 0; i < nbHostile; i++)
	{
		free(liste_hostile[i].explosion);
		liste_hostile[i].explosion = NULL;
	}
	if(liste_hostile != NULL)
	{
		free(liste_hostile);
		liste_hostile = NULL;
	}
	SDL_Log("----------CLEAN HOSTILE TERMINER----------\n");
}

void addVitesseHostile(void)
{
	for(int i = 0; i < nbHostile; i++)
	{
		if(liste_hostile[i].vitesse.y == 0)
		{
			liste_hostile[i].timeToShoot.previousTime = SDL_GetTicks();
		}
		liste_hostile[i].vitesse.x = 0;
		liste_hostile[i].vitesse.y = getVitesseType(liste_hostile[i].type);
	}
}

void addHostile(int i)
{
	SDL_bool collision = SDL_TRUE;

	if(isPlayerAlive())
	{
		if(liste_hostile[i].isExplode == SDL_FALSE)
		{
			int type = rand() % 3;
			liste_hostile[i].position.x = rand() % getWidth();
			liste_hostile[i].position.y = -(rand() % getHeight());

			while(type == 0)
			{
				type = rand() % 3;
			}

			liste_hostile[i].type = type;

			if(liste_hostile[i].type == 1)
			{
				liste_hostile[i].texture = 1;
				liste_hostile[i].timeToShoot.ms = 8000;
			}
			else if(liste_hostile[i].type == 2)
			{
				liste_hostile[i].texture = 2;
				liste_hostile[i].timeToShoot.ms = 5000;
			}

			liste_hostile[i].vitesse.x = 0;
			liste_hostile[i].vitesse.y = getVitesseType(liste_hostile[i].type);

			liste_hostile[i].alive = SDL_TRUE;
			liste_hostile[i].isExplode = SDL_FALSE;
			for(int j = 0; j < liste_hostile[i].nbExplosion; j++)
			{
				liste_hostile[i].explosion[j].rayon = 0;
			}

			liste_hostile[i].timerExplosion.previousTime = 0;
			liste_hostile[i].timerExplosion.currentTime = 0;

			liste_hostile[i].timeToShoot.currentTime = 0;
			liste_hostile[i].timeToShoot.previousTime = SDL_GetTicks();
			liste_hostile[i].hasShoot = SDL_FALSE;

			while(collision)
			{
				int j = 0;
				collision = SDL_FALSE;
				while(j < nbHostile && collision == SDL_FALSE)
				{
					if(j != i)
					{
						if(checkCollide(liste_hostile[i].position, liste_hostile[j].position) 
							|| liste_hostile[i].position.x < liste_hostile[i].position.w 
							|| liste_hostile[i].position.x > getWidth() - liste_hostile[i].position.w
							|| liste_hostile[i].position.y > 0 - liste_hostile[i].position.h)
						{
							liste_hostile[i].position.x = rand() % getWidth();
							liste_hostile[i].position.y = -(rand() % getHeight() / 2);
							collision = SDL_TRUE;
						}
					}
					j++;
				}
			}
			liste_hostile[i].collider.dimension.x = liste_hostile[i].position.x;
			liste_hostile[i].collider.dimension.y = liste_hostile[i].position.y + 4 * getScaleY();
			//liste_hostile[i].moteur.cx = liste_hostile[i].position.x + liste_hostile[i].position.w / 2;
			//liste_hostile[i].moteur.cy = liste_hostile[i].collider.dimension.y;
		}
	}
}

SDL_Rect getHostileCollider(int i)
{
	return liste_hostile[i].collider.dimension;
}

SDL_bool getIfIsExplode(int i)
{
	return liste_hostile[i].isExplode;
}

void setNoAliveHostile(int j)
{
	liste_hostile[j].alive = SDL_FALSE;
	liste_hostile[j].isExplode = SDL_TRUE;
	liste_hostile[j].timerExplosion.previousTime = SDL_GetTicks();
	for(int i = 0; i < liste_hostile[j].nbExplosion; i++)
	{
		liste_hostile[j].explosion[i].cx = liste_hostile[j].position.x + (rand() % liste_hostile[j].position.w);
		liste_hostile[j].explosion[i].cy = liste_hostile[j].position.y + (rand() % liste_hostile[j].position.h);
	}
}

int getNombreHostile(void)
{
	return nbHostile;
}

int getVitesseType(int type)
{
	if(type == 1)
	{
		return 2 * getScaleY();
	}
	else if(type == 2)
	{
		return 4 * getScaleY();
	}
	else
	{
		return 5 * getScaleY();
	}
}

static void shoot(int i)
{
	liste_hostile[i].timeToShoot.previousTime = SDL_GetTicks();
	addShoot(liste_hostile[i].position.x + liste_hostile[i].position.w / 2, (liste_hostile[i].position.y + liste_hostile[i].position.h) + liste_hostile[i].position.h / 2, 7, SDL_FALSE);
	liste_hostile[i].hasShoot = SDL_TRUE;
}

void addSomeHostile(int nombre)
{
	SDL_bool collision = SDL_FALSE;

	int oldNombre = nbHostile;
	nbHostile += nombre;

	Hostile *tmp = realloc(liste_hostile, sizeof(Hostile) * nbHostile);
	if(tmp == NULL)
	{
		fprintf(stderr, "malloc; %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
		liste_hostile = tmp;
	}

	for(int i = oldNombre; i < nbHostile; i++)
	{
		int type = rand() % 5;
		while(type == 0)
		{
			type = rand() % 5;
		}

		liste_hostile[i].type = type;
		if(liste_hostile[i].type == 1)
		{
			liste_hostile[i].texture = 1;
			liste_hostile[i].timeToShoot.ms = 7000;
		}
		else if(liste_hostile[i].type == 2)
		{
			liste_hostile[i].texture = 2;
			liste_hostile[i].timeToShoot.ms = 5000;
		}
		else if(liste_hostile[i].type == 4)
		{
			liste_hostile[i].texture = 3;
			liste_hostile[i].timeToShoot.ms = 4000;
		}
		else
		{
			liste_hostile[i].texture = 2;
			liste_hostile[i].timeToShoot.ms = 3000;
		}

		liste_hostile[i].angle = 180;
		liste_hostile[i].couleur = getRouge(255);

		liste_hostile[i].position.w = 32 * getScaleX();
		liste_hostile[i].position.h = 32 * getScaleY();
		liste_hostile[i].position.x = rand() % getWidth();
		liste_hostile[i].position.y = -(rand() % getHeight());

		liste_hostile[i].collider.couleur = getRouge(255);
		liste_hostile[i].collider.fill = SDL_FALSE;
		liste_hostile[i].collider.dimension.w = 32 * getScaleX();
		liste_hostile[i].collider.dimension.h = 28 * getScaleY();

		if(liste_hostile[i].type == 3)
		{
			liste_hostile[i].position.w = 48 * getScaleX();
			liste_hostile[i].position.h = 48 * getScaleY();
			liste_hostile[i].collider.dimension.w = 48 * getScaleX();
			liste_hostile[i].collider.dimension.h = 40 * getScaleY();
		}

		liste_hostile[i].timeToShoot.currentTime = 0;
		liste_hostile[i].timeToShoot.previousTime = 0;
		liste_hostile[i].hasShoot = SDL_FALSE;

		liste_hostile[i].nbExplosion = 5;
		liste_hostile[i].explosion = malloc(sizeof(Cercle) * liste_hostile[i].nbExplosion);
		if(liste_hostile[i].explosion == NULL)
		{
			fprintf(stderr, "malloc; %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		for(int j = 0; j < liste_hostile[i].nbExplosion; j++)
		{
			liste_hostile[i].explosion[j].cx = 0;
			liste_hostile[i].explosion[j].cy = 0;
			liste_hostile[i].explosion[j].couleur = getJaune(255);
			liste_hostile[i].explosion[j].rayon = 0;
			liste_hostile[i].explosion[j].vitesse.x = 0;
			liste_hostile[i].explosion[j].vitesse.y = 0;
		}
		liste_hostile[i].timerExplosion.ms = 300;
		liste_hostile[i].timerExplosion.previousTime = 0;
		liste_hostile[i].timerExplosion.currentTime = 0;
		liste_hostile[i].isExplode = SDL_FALSE;

		liste_hostile[i].alive = SDL_TRUE;

		liste_hostile[i].timerMoteur.ms = 50;
		liste_hostile[i].timerMoteur.previousTime = SDL_GetTicks();
		liste_hostile[i].timerMoteur.currentTime = 0;

		do
		{
			collision = SDL_FALSE;
			for(int j = 0; j < nbHostile; j++)
			{
				if(j != i)
				{
					if(checkCollide(liste_hostile[i].position, liste_hostile[j].position) 
						|| liste_hostile[i].position.x < liste_hostile[i].position.w 
						|| liste_hostile[i].position.x > getWidth() - liste_hostile[i].position.w
						|| liste_hostile[i].position.y > 0 - liste_hostile[i].position.h)
					{
						liste_hostile[i].position.x = rand() % getWidth();
						liste_hostile[i].position.y = -(rand() % getHeight() / 2);
						collision = SDL_TRUE;
					}
				}
			}
		}while(collision);

		liste_hostile[i].collider.dimension.x = liste_hostile[i].position.x;
		liste_hostile[i].collider.dimension.y = liste_hostile[i].position.y + 4 * getScaleY();
	}
}