#include "Game.h"



Game::Game()
{
    Game::window = NULL;
    Game::renderer = NULL;
    Game::running = true;
    isDiffShown = false;
    isThemeShown = false;
    theme = "cars";
    dominoPlayer = new DominoPlayer();
    dominoTable = new DominoTable();
    
    
    for (int i = 0; i < 10;i++) {
    DominoBrick d;
    dominoPlayer->addPiece(d);
    }
    
    

    DominoBrick dd;
    dominoTable->addPiece(dd);
}

Game::~Game()
{
    delete dominoPlayer;
    dominoPlayer = nullptr;
    delete dominoTable;
    dominoTable = nullptr;
    delete d1;
    d1 = nullptr;
    delete d2;
    d2 = nullptr;
}

void Game::renderPlayer(DominoPlayer* b)
{
    int ww, wh;
    SDL_GetWindowSize(window, &ww, &wh);
    int a = 50;

    for (int i = 0; i < b->myPieces.size(); i++) {
        renderBrick(&b->myPieces[i], a, wh - 150);
        a += 75;
    }
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        cout << "SDL init success\n";

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window != 0) {
            cout << "window creation success\n";
            renderer = SDL_CreateRenderer(window, -1, 0);
            if (renderer != 0) {
                cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 50);

                TextureManager::Instance()->loadTexture("assets/backgr.jpg", "background", renderer);
                TextureManager::Instance()->loadTexture("assets/beach/1.jpg", "sea_1", renderer);
                TextureManager::Instance()->loadTexture("assets/beach/2.jpg", "sea_2", renderer);
                TextureManager::Instance()->loadTexture("assets/beach/3.jpg", "sea_3", renderer);
                TextureManager::Instance()->loadTexture("assets/beach/4.jpg", "sea_4", renderer);
                TextureManager::Instance()->loadTexture("assets/beach/5.jpg", "sea_5", renderer);
                TextureManager::Instance()->loadTexture("assets/beach/6.jpg", "sea_6", renderer);
                TextureManager::Instance()->loadTexture("assets/cars/1.jpg", "cars_1", renderer);
                TextureManager::Instance()->loadTexture("assets/cars/2.jpg", "cars_2", renderer);
                TextureManager::Instance()->loadTexture("assets/cars/3.jpg", "cars_3", renderer);
                TextureManager::Instance()->loadTexture("assets/cars/4.jpg", "cars_4", renderer);
                TextureManager::Instance()->loadTexture("assets/cars/5.jpg", "cars_5", renderer);
                TextureManager::Instance()->loadTexture("assets/cars/6.jpg", "cars_6", renderer);
                TextureManager::Instance()->loadTexture("assets/flowers/1.jpg", "flowers_1", renderer);
                TextureManager::Instance()->loadTexture("assets/flowers/2.jpg", "flowers_2", renderer);
                TextureManager::Instance()->loadTexture("assets/flowers/3.jpg", "flowers_3", renderer);
                TextureManager::Instance()->loadTexture("assets/flowers/4.jpg", "flowers_4", renderer);
                TextureManager::Instance()->loadTexture("assets/flowers/5.jpg", "flowers_5", renderer);
                TextureManager::Instance()->loadTexture("assets/flowers/6.jpg", "flowers_6", renderer);
                



            }
            else {
                cout << "renderer init failed\n";
                return false;
            }
        }
        else {
            cout << "window init failed\n";
            return false;
        }
    }
    else {
        cout << "SDL init fail\n";
        return false;
    }
    cout << "init success\n";
    running = true;
    return true;

}



void Game::render()
{
    int ww, wh;
    SDL_GetWindowSize(window, &ww, &wh);
    SDL_SetRenderDrawColor(renderer, 220, 220, 220, 220);

    SDL_RenderClear(renderer);

    //SDL_RenderCopy(renderer, menuFont, NULL, &menudRect);
    //SDL_RenderCopy(renderer, difficultyFont, NULL, &difficultydRect);
    //SDL_RenderCopy(renderer, normalDifFont, NULL, &normaldRect);
    //SDL_RenderCopy(renderer, mediumDifFont, NULL, &mediumdRect);
    //SDL_RenderCopy(renderer, hardDifFont, NULL, &harddRect);
    //SDL_RenderCopy(renderer, themeFont, NULL, &themedRect);
    //SDL_RenderCopy(renderer, seaFont, NULL, &seadRect);
    //SDL_RenderCopy(renderer, carFont, NULL, &cardRect);
    //SDL_RenderCopy(renderer, flowerFont, NULL, &flowerdRect);
    //SDL_RenderCopy(renderer, okFont, NULL, &okdRect);

    //if (isDiffShown) {
    //    SDL_RenderCopy(renderer, fpointerFont, NULL, &fpointerdRect);
    //}
    //if (isThemeShown) {
    //    SDL_RenderCopy(renderer, spointerFont, NULL, &spointerdRect);
    //}

    
    
    renderOponent(dominoPlayer);

    renderPlayer(dominoPlayer);
    
    renderTable(dominoTable);


    SDL_RenderPresent(renderer);




}

void Game::update()
{




}

void Game::handleEvents()
{
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_MOUSEBUTTONDOWN: {
            int msx, msy;
            if (event.button.button == SDL_BUTTON_LEFT) {
                SDL_GetMouseState(&msx, &msy);
                int tw, th;
                int ww, wh;
                SDL_GetWindowSize(window, &ww, &wh);
                
                if (msy >= normaldRect.y && msy < mediumdRect.y) {
                    fpointerdRect.x = normaldRect.x - 30;
                    fpointerdRect.y = normaldRect.y;
                    if (!isDiffShown) {
                        isDiffShown = true;
                    }
                }
                if (msy >= mediumdRect.y && msy < harddRect.y) {
                    fpointerdRect.x = mediumdRect.x - 30;
                    fpointerdRect.y = mediumdRect.y;
                    if (!isDiffShown) {
                        isDiffShown = true;
                    }
                }
                if (msy >= harddRect.y && msy < themedRect.y) {
                    fpointerdRect.x = harddRect.x - 30;
                    fpointerdRect.y = harddRect.y;
                    if (!isDiffShown) {
                        isDiffShown = true;
                    }
                }

                if (msy >= seadRect.y && msy < cardRect.y) {
                    spointerdRect.x = seadRect.x - 30;
                    spointerdRect.y = seadRect.y;
                    if (!isThemeShown) {
                        isThemeShown = true;
                    }
                }
                if (msy >= cardRect.y && msy < flowerdRect.y) {
                    spointerdRect.x = cardRect.x - 30;
                    spointerdRect.y = cardRect.y;
                    if (!isThemeShown) {
                        isThemeShown = true;
                    }
                }
                if (msy >= flowerdRect.y && msy < flowerdRect.y + flowerdRect.h) {
                    spointerdRect.x = flowerdRect.x - 30;
                    spointerdRect.y = flowerdRect.y;
                    if (!isThemeShown) {
                        isThemeShown = true;
                    }
                }

            }
        }break;
        case SDL_MOUSEBUTTONUP: {
            int msx, msy;
            //cout << "Mouse button up\n";
            if (event.button.button == SDL_BUTTON_LEFT) {
                SDL_GetMouseState(&msx, &msy);
                cout << msx << ":" << msy << endl;



            }
        }break;
        default:
            break;
        }
    }
}

void Game::clean()
{
    cout << "cleaning game\n";
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    delete dominoPlayer;
    dominoPlayer = nullptr;
    delete dominoTable;
    dominoTable = nullptr;
    delete d1;
    d1 = nullptr;
    delete d2;
    d2 = nullptr;
}

bool Game::isRunning()
{
    return this->running;
}

void Game::renderBrick(DominoBrick* b, int x, int y)
{
    string currTheme = theme + "_" + to_string(b->pValue1);
    TextureManager::Instance()->drawTexture(currTheme, x, y, 50, 50, renderer);
    currTheme = theme + "_" + to_string(b->pValue2);
    TextureManager::Instance()->drawTexture(currTheme, x, y + 50, 50, 50, renderer);
}

void Game::renderTable(DominoTable* s)
{

    int ww, wh;
    SDL_GetWindowSize(window, &ww, &wh);
    int a = 50;

    for (int i = 0; i < s->tablePieces.size(); i++) {
        renderBrick(&s->tablePieces[i], a, wh / 2 - 100);
        a += 75;
    }
}

void Game::renderOponent(DominoPlayer* b)
{
    int ww, wh;
    SDL_GetWindowSize(window, &ww, &wh);
    int count = b->getSize();

    int a = 50;

    for (int i = 0; i < count;i++) {
        TextureManager::Instance()->drawTexture("background", a, 50, 50, 50, renderer);
        a += 75;
    }

    
    
}

bool Game::createTextureFromText(const char* text, TTF_Font* font, SDL_Texture*& texture) {
    SDL_Surface* tempSurfaceText = TTF_RenderText_Blended(font, text, { 0, 0, 139, 255 });
    if (tempSurfaceText == nullptr) {
        // Failed to render text
        return false;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);
    if (texture == nullptr) {
        // Failed to create texture from surface
        SDL_FreeSurface(tempSurfaceText);
        return false;
    }
    SDL_FreeSurface(tempSurfaceText);
    return true;
}


bool Game::ttf_init() {
    if (TTF_Init() == -1) {
        return false;
    }

    font1 = TTF_OpenFont("assets/fonts/Valorant.ttf", 75);
    font2 = TTF_OpenFont("assets/fonts/Valorant.ttf", 55);
    font3 = TTF_OpenFont("assets/fonts/Valorant.ttf", 35);

    if (font1 == NULL || font2 == NULL || font3 == NULL) {
        return false;
    }

   

    createTextureFromText("MENU", font1, menuFont);
    createTextureFromText("Difficulty:", font2, difficultyFont);
    createTextureFromText("Normal", font3, normalDifFont);
    createTextureFromText("Medium", font3, mediumDifFont);
    createTextureFromText("Hard", font3, hardDifFont);
    createTextureFromText("Theme:", font2, themeFont);
    createTextureFromText("Sea", font3, seaFont);
    createTextureFromText("Cars", font3, carFont);
    createTextureFromText("Flowers", font3, flowerFont);
    createTextureFromText(">", font3, fpointerFont);
    createTextureFromText(">", font3, spointerFont);
    createTextureFromText("OK", font3, okFont);


    SDL_Surface* tempSurfaceText = NULL;
    int ww, wh;
    SDL_GetWindowSize(window, &ww, &wh);
    int tw, th;
    SDL_QueryTexture(menuFont, 0, 0, &tw, &th);
    menudRect = { ww / 2 - tw / 2, (int)(0 + wh * 0.25 - th / 2), tw,th };

    SDL_QueryTexture(difficultyFont, 0, 0, &tw, &th);
    difficultydRect = { ww / 2 - tw / 2, (int)(0 + wh * 0.25 - th / 2) + 100, tw,th };

    SDL_QueryTexture(normalDifFont, 0, 0, &tw, &th);
    normaldRect = { ww / 2 - tw / 2, (int)(0 + wh * 0.25 - th / 2) + 150, tw,th };

    SDL_QueryTexture(mediumDifFont, 0, 0, &tw, &th);
    mediumdRect = { ww / 2 - tw / 2, (int)(0 + wh * 0.25 - th / 2) + 200, tw,th };

    SDL_QueryTexture(hardDifFont, 0, 0, &tw, &th);
    harddRect = { ww / 2 - tw / 2, (int)(0 + wh * 0.25 - th / 2) + 250, tw,th };

    SDL_QueryTexture(themeFont, 0, 0, &tw, &th);
    themedRect = { ww / 2 - tw / 2, (int)(0 + wh * 0.25 - th / 2) + 350, tw,th };

    SDL_QueryTexture(seaFont, 0, 0, &tw, &th);
    seadRect = { ww / 2 - tw / 2, (int)(0 + wh * 0.25 - th / 2) + 400, tw,th };

    SDL_QueryTexture(carFont, 0, 0, &tw, &th);
    cardRect = { ww / 2 - tw / 2, (int)(0 + wh * 0.25 - th / 2) + 450, tw,th };

    SDL_QueryTexture(flowerFont, 0, 0, &tw, &th);
    flowerdRect = { ww / 2 - tw / 2, (int)(0 + wh * 0.25 - th / 2) + 500, tw,th };

    SDL_QueryTexture(okFont, 0, 0, &tw, &th);
    okdRect = { ww / 2 - tw / 2, (int)(0 + wh * 0.25 - th / 2) + 650, tw,th };

    SDL_QueryTexture(fpointerFont, 0, 0, &tw, &th);
    fpointerdRect = { 0, 0, tw,th };
    
    SDL_QueryTexture(spointerFont, 0, 0, &tw, &th);
    spointerdRect = { 0, 0, tw,th };

    SDL_FreeSurface(tempSurfaceText);
    TTF_CloseFont(font1);


    return true;
}
