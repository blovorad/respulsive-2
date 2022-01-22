#ifndef __STRUCTURE__H__
#define __STRUCTURE__H__

#include "define.h"

//DEBUT DES ENUMERATIONS
enum direction
{
	BAS,
	HAUT,
	GAUCHE,
	DROITE
};

enum boutonEtat
{	
	ORIGINAL,
	SELECT,
	PRESSED
};
//FIN DES ENUMERATIONS

//DEBUT DES STRUCT BASIQUES
typedef struct 
{

	double x, y;

}Vecteur;

typedef struct 
{
	
	SDL_Texture *texture;
	SDL_Rect dimension;

}Sprite;

typedef struct 
{

	int previousTime;
	int currentTime;
	int ms;

}Timer;

typedef struct 
{

	Sprite sprite;
	SDL_Color couleur;
	SDL_bool fill;
	int number;

}Tile;

typedef struct 
{
	
	Vecteur vitesse;
	Timer lifeRemaning;
	SDL_Point coordonner;
	SDL_Color couleur;
	SDL_bool used;

}Point;

typedef struct 
{

	SDL_bool z,s,q,d,space;

}Input;

typedef struct 
{

	int x1,y1,x2,y2;
	int longueur;
	SDL_Color couleur;
	Vecteur vitesse;
	int minSpeed;

}Ligne;

typedef struct 
{

	Sprite sprite;
	SDL_Color couleur;

}Texte;

typedef struct 
{
	SDL_Rect dimension;
	int texture;
	SDL_bool fill;
	SDL_Color couleur;

}Panel;

typedef struct 
{
	
	Panel panel;
	Texte texte;
	SDL_bool isHover, isPressed;

	int alpha;
	int event;

}Bouton;

typedef struct 
{
	
	SDL_bool rightButton, leftButton;
	SDL_bool oldRightButton, oldLeftButton;
	int x, y;

}Mouse;

typedef struct 
{
	
	SDL_bool isPlaying;
	Mix_Chunk *fx;
	Mix_Music *music;

}Sound;

typedef struct 
{

	SDL_Rect dimension;
	int texture;
	SDL_Color couleur;

}Background;

typedef struct 
{

	Sprite sprite;
	SDL_Rect tailleReel;
	SDL_Color couleur;
	SDL_bool empty;
	SDL_bool fill;

}Barre;

typedef struct 
{
	
	SDL_Rect dimension;
	SDL_Color couleur;
	SDL_bool fill;

}CollideBox;

typedef struct 
{

	Bouton *liste_bouton;
	Texte *liste_texte;
	Panel *liste_panel;
	Barre *liste_barre;

	int nbBouton;
	int nbTexte;
	int nbPanel;
	int nbBarre;
	
	SDL_bool visible;

}GroupeGui;

typedef struct 
{
	int cx, cy;
	int rayon;
	SDL_Color couleur;

	SDL_Rect collider;
	SDL_bool fill;

	Vecteur vitesse;

}Cercle;

//FIN DES STRUCT BASIQUE

typedef struct 
{
	
	int texture;
	SDL_Rect position;
	CollideBox collider;

	Vecteur vitesse;
	int angle;
	SDL_bool alive;

	Cercle moteur;
	Timer timerMoteur;

}Player;

typedef struct 
{
	
	int texture;
	SDL_Rect position;
	CollideBox collider;
	Timer timeToShoot;
	SDL_bool hasShoot;

	Vecteur vitesse;
	int angle;
	SDL_Color couleur;

	Cercle moteur;
	Timer timerMoteur;
	int type;

	SDL_bool alive;

	Cercle *explosion;
	int nbExplosion;
	SDL_bool isExplode;
	Timer timerExplosion;

}Hostile;

typedef struct 
{
	
	Ligne line;
	SDL_bool alive;
	SDL_bool isSuperShoot;
	CollideBox collider;

	Cercle explosion;
	SDL_bool isExplode;
	Timer timerExplosion;

}Shoot;

typedef struct 
{
	
	SDL_Rect position;
	CollideBox collider;

	int type;
	Vecteur vitesse;
	SDL_Color couleur;
	SDL_bool fill;
	SDL_bool alive;

}PowerUp;

#endif