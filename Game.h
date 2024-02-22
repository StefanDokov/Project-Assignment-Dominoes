#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include "TextureManager.h"
#include "DominoBrick.h"
#include "DominoPlayer.h"
#include "DominoTable.h"
#include <iostream>
using namespace std;

class Game {
public:
	Game();
	~Game();
	void renderPlayer(DominoPlayer*);
	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	bool ttf_init();
	void render();
	void update();
	void handleEvents();
	void clean();
	bool isRunning();
	void renderBrick(DominoBrick* b);
	void renderTable(DominoTable*);
	string theme;
	void renderOponent(DominoPlayer*);
	bool createTextureFromText(const char* text, TTF_Font* font, SDL_Texture*& texture);
private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	bool running;
	int mouseDownX, mouseDownY;
	
	SDL_Texture* menuFont,
		* difficultyFont,
		* normalDifFont,
		* mediumDifFont,
		* hardDifFont,
		* themeFont,
		* seaFont,
		* carFont,
		* flowerFont,
		* fpointerFont,
		* spointerFont,
		* okFont,
		* loseFont,
		* betFont;
	SDL_Rect menudRect,
		difficultydRect,
		normaldRect,
		mediumdRect,
		harddRect,
		themedRect,
		seadRect,
	    cardRect,
		flowerdRect,
		fpointerdRect,
		spointerdRect,
		okdRect,
		losedRect,
		betdRect;
	bool isDiffShown;
	bool isThemeShown;
	bool selected;
	int selectedItem;
	DominoPlayer* dominoPlayer = nullptr;
	DominoTable* dominoTable = nullptr;
	DominoBrick* d1 = nullptr;
	DominoBrick* d2 = nullptr;
	TTF_Font* font1,
		* font2,
		* font3;
};
