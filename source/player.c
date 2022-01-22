#include "prototype.h"

static Player player;

static SDL_bool hasShoot;
static SDL_bool oldSpace;
static SDL_bool launchSuperShoot;
static SDL_bool estEnSurchauffe;
static SDL_bool hasShield;

static Cercle shield;
static int shieldCharge;

static GroupeGui playerHUD;

static Timer timerSuperShoot;
static Timer shootTimer;

static Cercle *liste_balle;
static Cercle *liste_explosion;
static int nbExplosion;
static int nbBalle;
static int score;

static void chargingSuperShoot(void);
static void initPlayerHUD(void);
static void updatePlayerHUD(void);
static void moveBarreSurchauffe(int dx);
static void movePlayer(Input *input);
static void shootPlayer(Input *input);

void initPlayer(void)
{
	SDL_Log("----------INIT PLAYER EN COURS----------\n");

	nbBalle = 5;
	score = 0;
	liste_balle = malloc(sizeof(Cercle) * nbBalle);
	if(liste_balle == NULL)
	{
		fprintf(stderr, "malloc; %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < nbBalle; i++)
	{
		liste_balle[i].vitesse.x = 0;
		liste_balle[i].vitesse.y = 0;
		liste_balle[i].rayon = 4 * getScaleX();
		liste_balle[i].cy = 592 * getScaleY();

		liste_balle[i].couleur = getBlanc(255);
	}

	liste_balle[0].cx = 255 * getScaleX();
	liste_balle[1].cx = 265 * getScaleX();
	liste_balle[2].cx = 275 * getScaleX();
	liste_balle[3].cx = 285 * getScaleX();
	liste_balle[4].cx = 295 * getScaleX();

	initPlayerHUD();

	launchSuperShoot = SDL_FALSE;
	estEnSurchauffe = SDL_FALSE;
	hasShoot = SDL_FALSE;
	oldSpace = SDL_FALSE;

	shootTimer.previousTime = 0;
	shootTimer.currentTime = 0;
	shootTimer.ms = 40;

	player.texture = 0;

	player.angle = 0;

	player.position.w = 32 * getScaleX();
	player.position.h = 32 * getScaleY();
	player.position.x = 400 * getScaleX() - player.position.w / 2;
	player.position.y = 530 * getScaleY() - player.position.h / 2;

	player.collider.dimension.x = player.position.x;
	player.collider.dimension.y = player.position.y;
	player.collider.dimension.w = 32 * getScaleX();
	player.collider.dimension.h = 28 * getScaleY();

	player.collider.fill = SDL_FALSE;
	player.collider.couleur = getRouge(255);

	player.vitesse.x = 0;
	player.vitesse.y = 0;
	setPlayerAlive(SDL_TRUE);

	timerSuperShoot.ms = 1000;
	timerSuperShoot.currentTime = 0;
	timerSuperShoot.previousTime = 0;

	player.timerMoteur.ms = 50;
	player.timerMoteur.previousTime = SDL_GetTicks();
	player.timerMoteur.currentTime = 0;

	/*player.moteur.cx = player.position.x + player.position.w / 2;
	player.moteur.cy = player.collider.dimension.y + player.collider.dimension.h;
	player.moteur.couleur = getBlanc(255);
	player.moteur.vitesse.x = 0;
	player.moteur.vitesse.y = 0;
	player.moteur.rayon = 3 * getScaleY();*/

	hasShield = SDL_TRUE;
	shieldCharge = 100;
	shield.cx = player.position.x + player.position.w / 2;
	shield.cy = player.position.y + player.position.h / 2;
	shield.rayon = 20 * getScaleX();
	shield.collider.x = player.position.x - 2;
	shield.collider.y = player.position.y - 2;
	shield.collider.w = shield.rayon * 2;
	shield.collider.h = shield.rayon * 2;
	shield.vitesse.x = 0;
	shield.vitesse.y = 0;
	shield.couleur = getBleu(255);
	shield.fill = SDL_FALSE;
	SDL_Log("----------INIT PLAYER TERMINER----------\n");
}

void updatePlayer(Input *input)
{
	updatePlayerHUD();

	if(player.alive)
	{
		/*player.timerMoteur.currentTime = SDL_GetTicks();
		if(player.timerMoteur.currentTime >= player.timerMoteur.previousTime + player.timerMoteur.ms)
		{
			player.moteur.rayon++;
			if(player.moteur.rayon > 8 * getScaleY())
			{
				player.moteur.rayon = 3 * getScaleY();
			}

			player.timerMoteur.previousTime = player.timerMoteur.currentTime;
		}*/

		shootPlayer(input);

		movePlayer(input);

		if(!getPrintTuto())
		{
			if(getNbAmmoUp() < 1 && liste_balle[4].couleur.g < 1)
			{
				addPowerUp(1);
			}
		}

		oldSpace = input->space;
	}
	else
	{
		SDL_ShowCursor(SDL_ENABLE);
		for(int i = 0; i < nbExplosion; i++)
		{
			liste_explosion[i].cx += liste_explosion[i].vitesse.x;
			liste_explosion[i].cy += liste_explosion[i].vitesse.y;
		}
	}
}

void drawPlayer(void)
{
	for(int i = 0; i < nbBalle; i++)
	{
		drawDisque(liste_balle[i]);
	}
	drawGroupeGui(&playerHUD);
	if(player.alive)
	{
		//drawCercle(player.moteur);
		if(hasShield)
		{
			drawCercle(shield);
		}
		drawTextureEx(getTexture(player.texture), &player.position, NULL, NULL, player.angle, SDL_FLIP_NONE);
	}
	else
	{
		for(int i = 0; i < nbExplosion; i++)
		{
			drawDisque(liste_explosion[i]);
		}
	}
}

void cleanPlayer(void)
{
	SDL_Log("----------CLEAN PLAYER EN COURS----------\n");
	if(liste_balle != NULL)
	{
		free(liste_balle);
		liste_balle = NULL;
	}
	cleanExplosion();
	cleanGroupeGui(&playerHUD);
	SDL_Log("----------CLEAN PLAYER TERMINER----------\n");
}

SDL_Rect getPlayerCollider(void)
{
	return player.collider.dimension;
}

void setPlayerAlive(SDL_bool active)
{
	player.alive = active;
}

SDL_bool isPlayerAlive(void)
{
	return player.alive;
}

static void chargingSuperShoot(void)
{
	timerSuperShoot.currentTime = SDL_GetTicks();
	if(timerSuperShoot.currentTime >= timerSuperShoot.previousTime + timerSuperShoot.ms)
	{
		playFx(10);
		addShoot(player.position.x + player.position.w / 2, player.position.y - player.position.h / 2, -7, SDL_TRUE);

		if(liste_balle[nbBalle - 1].couleur.g > 0)
		{
			liste_balle[nbBalle - 1].couleur = getRouge(255);
		}
		else
		{
			for(int i = 0; i < nbBalle - 1; i++)
			{
				if(liste_balle[i].couleur.g > 0 && liste_balle[i + 1].couleur.g < 1)
				{
					liste_balle[i].couleur = getRouge(255);
				}
			}
		}
		launchSuperShoot = SDL_FALSE;
	}
}

static void initPlayerHUD(void)
{
	initGroupeGui(&playerHUD, 4, 6, 0, 1);

	//int x, int y, int w, int h, SDL_Color color
	playerHUD.liste_barre[0] = createBarre(500, 585, 300, 15, getBlanc(255));
	playerHUD.liste_barre[1] = createBarre(500, 585, 300, 15, getBlanc(255));
	playerHUD.liste_barre[2] = createBarre(0, 585, 200, 15, getBleu(255));
	playerHUD.liste_barre[3] = createBarre(0, 585, 200, 15, getBleu(255));

	if(getLocalisation() == 0)
	{
		//int x, int y, int w, int h, char *texte, SDL_Color color, TTF_Font *font
		playerHUD.liste_texte[0] = createTexte(730, 570, 50, 15, "SURCHAUFFE", getBlanc(255), getFontHack());
		playerHUD.liste_texte[1] = createTexte(670, 570, 100, 15, "ATTENTION SURCHAUFFE", getRouge(255), getFontHack());
		playerHUD.liste_texte[2] = createTexte(250, 570, 50, 15, "MISSILE", getBlanc(255), getFontHack());
		playerHUD.liste_texte[3] = createTexte(5, 570, 50, 15, "BOUCLIER", getBlanc(255), getFontHack());
	}
	else
	{
		playerHUD.liste_texte[0] = createTexte(750, 570, 50, 15, "HEAT", getBlanc(255), getFontHack());
		playerHUD.liste_texte[1] = createTexte(690, 570, 100, 15, "WARNING HEAT", getRouge(255), getFontHack());
		playerHUD.liste_texte[2] = createTexte(250, 570, 50, 15, "MISSILE", getBlanc(255), getFontHack());
		playerHUD.liste_texte[3] = createTexte(2, 570, 50, 15, "SHIELD", getBlanc(255), getFontHack());	
	}

	playerHUD.liste_texte[4] = createTexte(375, 587, 50, 15, "SCORE :", getBlanc(255), getFontHack());
	playerHUD.liste_texte[5] = createTexte(425, 587, 50, 15, "0", getBlanc(255), getFontHack());

	//int x, int y, int w, int h, int texture, SDL_Color color, SDL_bool pFill
	playerHUD.liste_panel[0] = createPanel(250, 585, 52, 15, -1, getBlanc(255), SDL_FALSE);

	playerHUD.liste_texte[1].couleur.a = 0;
	SDL_SetTextureAlphaMod(playerHUD.liste_texte[1].sprite.texture, playerHUD.liste_texte[1].couleur.a);

	playerHUD.liste_barre[0].sprite.dimension.w = 0;
	playerHUD.liste_barre[1].fill = SDL_FALSE;
	playerHUD.liste_barre[3].fill = SDL_FALSE;
}

static void updatePlayerHUD(void)
{
	updateGroupeGui(&playerHUD);
	if(playerHUD.liste_barre[0].sprite.dimension.w > playerHUD.liste_barre[0].tailleReel.w - 30 * getScaleX())
	{
		if(playerHUD.liste_texte[0].couleur.g != 0)
		{
			playerHUD.liste_texte[0].couleur = getRouge(0);
			playerHUD.liste_texte[1].couleur.a = 255;
			playerHUD.liste_barre[0].couleur = getRouge(255);
			playerHUD.liste_barre[1].couleur = getRouge(255);
			SDL_SetTextureAlphaMod(playerHUD.liste_texte[0].sprite.texture, playerHUD.liste_texte[0].couleur.a);
			SDL_SetTextureAlphaMod(playerHUD.liste_texte[1].sprite.texture, playerHUD.liste_texte[1].couleur.a);
		}
	}
	else if(playerHUD.liste_barre[0].sprite.dimension.w > playerHUD.liste_barre[0].tailleReel.w - 130 * getScaleX())
	{
		if(playerHUD.liste_texte[0].couleur.g != 127)
		{
			playerHUD.liste_texte[0].couleur = getOrange(255);
			playerHUD.liste_barre[0].couleur = playerHUD.liste_texte[0].couleur;
			playerHUD.liste_barre[1].couleur = playerHUD.liste_texte[0].couleur;
			playerHUD.liste_texte[1].couleur.a = 0;
			SDL_SetTextureAlphaMod(playerHUD.liste_texte[0].sprite.texture, playerHUD.liste_texte[0].couleur.a);
			SDL_SetTextureAlphaMod(playerHUD.liste_texte[1].sprite.texture, playerHUD.liste_texte[1].couleur.a);
			SDL_SetTextureColorMod(playerHUD.liste_texte[0].sprite.texture, playerHUD.liste_texte[0].couleur.r, playerHUD.liste_texte[0].couleur.g, playerHUD.liste_texte[0].couleur.b);
		}
	}
	else
	{
		if(playerHUD.liste_texte[0].couleur.b < 255)
		{
			playerHUD.liste_texte[0].couleur = getBlanc(255);
			playerHUD.liste_barre[0].couleur = playerHUD.liste_texte[0].couleur;
			playerHUD.liste_barre[1].couleur = playerHUD.liste_texte[0].couleur;
			SDL_SetTextureColorMod(playerHUD.liste_texte[0].sprite.texture, playerHUD.liste_texte[0].couleur.r, playerHUD.liste_texte[0].couleur.g, playerHUD.liste_texte[0].couleur.b);
		}
	}
}

static void moveBarreSurchauffe(int dx)
{
	playerHUD.liste_barre[0].sprite.dimension.w += dx;
	if(playerHUD.liste_barre[0].sprite.dimension.w < 0)
	{
		playerHUD.liste_barre[0].sprite.dimension.w = 0;
		if(estEnSurchauffe)
		{
			estEnSurchauffe = SDL_FALSE;
		}
	}
	else if(playerHUD.liste_barre[0].sprite.dimension.w > playerHUD.liste_barre[0].tailleReel.w)
	{
		playFx(9);
		estEnSurchauffe = SDL_TRUE;
		playerHUD.liste_barre[0].sprite.dimension.w = playerHUD.liste_barre[0].tailleReel.w;
	}
}

void giveMissileToPlayer(void)
{
	int i = 0;
	SDL_bool give = SDL_FALSE;

	while(i < nbBalle && give == SDL_FALSE)
	{
		if(liste_balle[i].couleur.g < 1)
		{
			give = SDL_TRUE;
			liste_balle[i].couleur = getBlanc(255);
		}
		i++;
	}
}

void giveAmmo(void)
{
	for(int i = 0; i < nbBalle; i++)
	{
		if(liste_balle[i].couleur.g < 1)
		{
			liste_balle[i].couleur = getBlanc(255);
		}
	}
}

SDL_Rect getShieldCollider(void)
{
	return shield.collider;
}

SDL_bool getIfHasShield(void)
{
	return hasShield;
}

void removeShieldCharge(int charge)
{
	shieldCharge += charge;
	if(shieldCharge <= 0)
	{
		hasShield = SDL_FALSE;
		shieldCharge = 0;
	}
	if(hasShield == SDL_FALSE && shieldCharge > 0)
	{
		hasShield = SDL_TRUE;
	}
	if(shieldCharge >= 100)
	{
		shieldCharge = 100;
	}
	playerHUD.liste_barre[2].sprite.dimension.w = (shieldCharge * 2) * getScaleX();
}

int getShieldCharge(void)
{
	return shieldCharge;
}

static void movePlayer(Input *input)
{
	if(input->q)
	{
		player.vitesse.x = -8 * getScaleX();
	}
	else if(input->d)
	{
		player.vitesse.x = 8 * getScaleX();
	}
	else
	{
		player.vitesse.x = 0;
	} 


	player.position.x += player.vitesse.x;
	player.collider.dimension.x = player.position.x;
	//player.moteur.cx = player.position.x + player.position.w / 2;
	shield.cx = player.position.x + player.position.w / 2;
	shield.collider.x = player.position.x - 2;

	if(player.position.x > getWidth() - player.position.w)
	{
		player.position.x = getWidth() - player.position.w;
		player.collider.dimension.x = player.position.x;
		//player.moteur.cx = player.position.x + player.position.w / 2;
		shield.cx = player.position.x + player.position.w / 2;
		shield.collider.x = player.position.x - 2;
	}
	else if(player.position.x < 0)
	{
		player.position.x = 0;
		player.collider.dimension.x = player.position.x;
		//player.moteur.cx = player.position.x + player.position.w / 2;
		shield.cx = player.position.x + player.position.w / 2;
		shield.collider.x = player.position.x - 2;
	}
}

static void shootPlayer(Input *input)
{
	if(input->space && launchSuperShoot == SDL_FALSE && hasShoot == SDL_FALSE && estEnSurchauffe == SDL_FALSE)
	{
		playFx(2);
		addShoot(player.position.x + player.position.w / 2, player.position.y - player.position.h / 2, -7, SDL_FALSE);
		moveBarreSurchauffe(5 * getScaleX());
		shootTimer.previousTime = SDL_GetTicks();
		hasShoot = SDL_TRUE;
	}
	if(hasShoot)
	{
		shootTimer.currentTime = SDL_GetTicks();
		if(shootTimer.currentTime >= shootTimer.previousTime + shootTimer.ms)
		{
			hasShoot = SDL_FALSE;
		}
	}
	else if(hasShoot == SDL_FALSE)
	{
		if(estEnSurchauffe)
		{
			moveBarreSurchauffe(-3 * getScaleX());
		}
		moveBarreSurchauffe(-2 * getScaleX());
	}

	if(input->s && launchSuperShoot == SDL_FALSE && liste_balle[0].couleur.g > 1)
	{
		playFx(8);
		launchSuperShoot = SDL_TRUE;
		timerSuperShoot.previousTime = SDL_GetTicks();
	}

	if(launchSuperShoot)
	{
		chargingSuperShoot();
	}
}

void addScore(int pScore)
{
	score += pScore;

	if(score == 2000)
	{
		addSomeHostile(2);
	}
	else if(score == 3000)
	{
		addSomeHostile(5);
	}
	else if(score % 100 == 0)
	{
		addSomeHostile(1);
	}

	char scoreTexte[3];
	sprintf(scoreTexte, "%d", score);

	if(playerHUD.liste_texte[5].sprite.texture != NULL)
	{
		SDL_DestroyTexture(playerHUD.liste_texte[5].sprite.texture);
		playerHUD.liste_texte[5].sprite.texture = NULL;
	}

	playerHUD.liste_texte[5] = createTexte(425, 587, 50, 15, scoreTexte, getBlanc(255), getFontHack());
}

void launchExplosion(void)
{
	nbExplosion = 50;
	liste_explosion = malloc(sizeof(Cercle) * nbExplosion);
	if(liste_explosion == NULL)
	{
		fprintf(stderr, "malloc; %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < nbExplosion; i++)
	{
		liste_explosion[i].cx = player.position.x + player.position.w / 2;
		liste_explosion[i].cy = player.position.y + player.position.h / 2;
		liste_explosion[i].rayon = 1;

		if(rand() % 2 == 1)
		{
			liste_explosion[i].vitesse.x = rand() % 10 + 5;
		}
		else
		{
			liste_explosion[i].vitesse.x = -(rand() % 10 + 5);
		}
		if(rand() % 2 == 1)
		{
			liste_explosion[i].vitesse.y = rand() % 10 + 5;
		}
		else
		{
			liste_explosion[i].vitesse.y = -(rand() % 10 + 5);
		}
		liste_explosion[i].couleur = getVert(255);
	}
}

void cleanExplosion(void)
{
	nbExplosion = 0;
	if(liste_explosion != NULL)
	{
		free(liste_explosion);
		liste_explosion = NULL;
	}
}

