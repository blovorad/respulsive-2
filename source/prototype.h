#ifndef __PROTOTYPE__H__
#define __PROTOTYPE__H__

#include "structure.h"

//MAIN FUNCTION
extern void setGo(SDL_bool active);

//CLEANUP FUNCTION
extern void cleanUp(void);

//INIT FUNCTION
extern void init(void);

//UPDATE FUNCTION
extern void update(Input *input);

//DRAW FUNCTION
extern void draw(void);
extern void drawPlayer(void);
extern void drawRect(SDL_Rect *r, SDL_bool *fill, SDL_Color *couleur);
extern void drawTexture(SDL_Texture *texture, SDL_Rect *dst, SDL_Rect *src);
extern void drawTextureEx(SDL_Texture *texture, SDL_Rect *dst, SDL_Rect *src, SDL_Point *center, int angle, SDL_RendererFlip flip);
extern void setRenderColor(SDL_Color *couleur);
extern void drawLine(int x1, int y1, int x2, int y2, SDL_Color *couleur);
extern void drawPoint(int x, int y, SDL_Color *couleur);
extern void drawCercle(Cercle cercle);
extern void drawDisque(Cercle cercle);

//GAME FUNCTION
extern void initGame(void);
extern void updateGame(Input *input);
extern void drawGame(void);
extern void cleanGame(void);
extern void setPrintPause(SDL_bool active);
extern SDL_bool getPrintPause(void);
extern SDL_bool checkCollide(SDL_Rect a, SDL_Rect b);
extern void initDefaite(void);

//POWERUP FUNCTION
extern void initPowerUp(void);
extern void updatePowerUp(void);
extern void drawPowerUp(void);
extern void cleanPowerUp(void);
extern void getTypePowerUp(int type);
extern void addPowerUp(int type);
extern int getNbAmmoUp(void);

//PLAYER FUNCTION
extern void initPlayer(void);
extern void updatePlayer(Input *input);
extern void drawPlayer(void);
extern void cleanPlayer(void);
extern SDL_Rect getPlayerCollider(void);
extern void setPlayerAlive(SDL_bool active);
extern void giveMissileToPlayer(void);
extern void giveAmmo(void);
extern SDL_Rect getShieldCollider(void);
extern SDL_bool getIfHasShield(void);
extern void removeShieldCharge(int charge);
extern int getShieldCharge(void);
extern void addScore(int pScore);
extern void launchExplosion(void);
extern void cleanExplosion(void);
extern SDL_bool isPlayerAlive(void);

//GAMEBACKGROUND FUNCTION
extern void initGameBackground(void);
extern void updateGameBackground(void);
extern void drawGameBackground(void);
extern void cleanGameBackground(void);
extern void startAcceleration(void);
extern void stopAcceleration(void);
extern void restartXPos(void);
extern SDL_bool getAccelerationEtat(void);

//SHOOT FUNCTION
extern void initShoot(void);
extern void updateShoot(void);
extern void drawShoot(void);
extern void cleanShoot(void);
extern void addShoot(int x, int y, int vy, SDL_bool isSuper);

//HOSTILE FUNCTION
extern void initHostile(void);
extern void updateHostile(void);
extern void drawHostile(void);
extern void cleanHostile(void);
extern void addVitesseHostile(void);
extern void addHostile(int i);
extern SDL_Rect getHostileCollider(int i);
extern SDL_bool getIfIsExplode(int i);
extern void setNoAliveHostile(int j);
extern int getNombreHostile(void);
extern int getVitesseType(int type);
extern void addSomeHostile(int nombre);

//TUTO FUNCTION
extern void initTuto(void);
extern void updateTuto(void);
extern void drawTuto(void);
extern void cleanTuto(void);
extern SDL_bool getPrintTuto(void);

//MAIN MENU FUNCTION
extern void initMainMenu(void);
extern void updateMainMenu(void);
extern void drawMainMenu(void);
extern void cleanMainMenu(void);

//OPTION FUNCTION
extern void initOption(void);
extern void updateOption(void);
extern void drawOption(void);
extern void cleanOption(void);
extern void changeBoutonFullscreen(void);
extern void changeBoutonResolution(void);

//CREDIT FUNCTION
extern void initCredit(void);
extern void updateCredit(void);
extern void drawCredit(void);
extern void cleanCredit(void);

//FONT FUNCTION
extern void initFontHack(void);
extern void cleanFontHack(void);
extern TTF_Font *getFontHack(void);

//RESOLUTION MANAGER FUNCTION
extern SDL_Renderer *getRenderer(void);
extern SDL_Window *getWindow(void);
extern SDL_bool getFullscreen(void);
extern SDL_bool getOldFullscreen(void);
extern void initWindowAndRenderer(void);
extern void cleanWindowAndRenderer(void);
extern void setScale(void);
extern void setResolution(void);
extern void setFullscreen(SDL_bool active);
extern void resetResolution(int reset);
extern void changeLocalisation(void);
extern void changeResolution(int w, int h);
extern int getCurrentResolution(void);
extern int getOldCurrentResolution(void);
extern int getWidth(void);
extern int getHeight(void);
extern int getLocalisation(void);
extern float getScaleX(void);
extern float getScaleY(void);

//GUI FUNCTION
extern void cleanGroupeGui(GroupeGui *groupe);
extern void updateGroupeGui(GroupeGui *groupe);
extern void drawGroupeGui(GroupeGui *groupe);
extern void initGroupeGui(GroupeGui *menu, int barre, int texte, int bouton, int panel);
extern void drawPanel(Panel *panel);
extern void drawTexte(Texte *texte);
extern void drawBouton(Bouton *bouton);
extern void drawBarre(Barre *barre);
extern Panel createPanel(int x, int y, int w, int h, int texture, SDL_Color color, SDL_bool pFill);
extern Texte createTexte(int x, int y, int w, int h, char *texte, SDL_Color color, TTF_Font *font);
extern Barre createBarre(int x, int y, int w, int h, SDL_Color color);
extern Bouton createBouton(int x, int y, int w, int h, int texture,SDL_Color panelColor, char *ptexte, SDL_Color texteColor, TTF_Font *font, SDL_bool pFill, int event);

//SCENEMANAGER FUNCTION
extern void initSceneManager(void);
extern SDL_bool isActiveMainMenu(void);
extern SDL_bool isActiveGame(void);
extern SDL_bool isActiveOption(void);
extern SDL_bool isActiveCredit(void);
extern void setPrintOption(SDL_bool active);
extern void setPrintMainMenu(SDL_bool active);
extern void setPrintGame(SDL_bool active);
extern void setPrintCredit(SDL_bool active);

//INPUT FUNCTION
extern void getInput(Input *input);

//COLOR FUNCTION
extern SDL_Color getVert(int alpha);
extern SDL_Color getVertFoncer(int alpha);
extern SDL_Color getGris(int alpha);
extern SDL_Color getRouge(int alpha);
extern SDL_Color getBleu(int alpha);
extern SDL_Color getBlanc(int alpha);
extern SDL_Color getNoir(int alpha);
extern SDL_Color getMarron(int alpha);
extern SDL_Color getJaune(int alpha);
extern SDL_Color getOcre(int alpha);
extern SDL_Color getOrange(int alpha);

//EVENT FUNCTION
extern void initEvent(void);
extern void startGame(void);
extern void quitGame(void);
extern void goToOption(void);
extern void goToMenu(void);
extern void backToMenu(void);
extern void addVolumeMusique(void);
extern void addVolumeFx(void);
extern void removeVolumeMusique(void);
extern void removeVolumeFx(void);
extern void goToCredit(void);
extern void backToMenuFromCredit(void);
extern void resumeGame(void);
extern void backToMenuFromGame(void);
extern void setFullscreenOption(void);
extern void setResolutionEvent(void);
extern void localisationEvent(void);
extern void playEvent(int event);

//MOUSE FUNCTION
extern void initMouse(void);
extern SDL_bool getStateOfRightButton(void);
extern SDL_bool getStateOfLeftButton(void);
extern SDL_bool getStateOfOldRightButton(void);
extern SDL_bool getStateOfOldLeftButton(void);
extern void getMousePos(void);
extern void actualiseRightButton(int n);
extern void actualiseLeftButton(int n);
extern void actualiseOldRightButton(void);
extern void actualiseOldLeftButton(void);
extern int getMouseX(void);
extern int getMouseY(void);

//AUDIO FUNCTION
extern void cleanAudio(void);
extern void initAudio(int nbMusic, int nbFx);
extern void updateAudio(void);
extern void playFx(int fx);
extern void startMusic(int music, SDL_bool loop);
extern void upVolumeFx(void);
extern void downVolumeFx(void);
extern void upVolumeMusic(void);
extern void downVolumeMusic(void);
extern int getVolumeMusic(void);
extern int getVolumeFx(void);

//MATH FUNCTION
extern SDL_bool collide(SDL_Rect a, SDL_Rect b);
extern int absolue(int a, int b);
extern float getAngle(int x1, int y1, int x2, int y2);

//TEXTURE FUNCTION
extern SDL_Texture *createTexture(char *chemin, SDL_Rect *rect);
extern SDL_Texture *getTexture(int texture);
extern void initTexture(void);
extern void cleanTexture(void);

#endif