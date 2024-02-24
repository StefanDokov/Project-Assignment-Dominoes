#include "Game.h"



Game::Game()
{
    Game::window = NULL;
    Game::renderer = NULL;
    Game::running = true;
    isDiffShown = false;
    isThemeShown = false;
    selected = false;
    selectedItem = -1;
    theme = "";
    menuBool = true;
    startGame = false;
    difficulty = 0;
    gameOver = false;
    p1Winner = false;
    p2Winner = false;
    isDraw = false;
}

Game::~Game()
{
    
    delete dominoPlayer1;
    dominoPlayer1 = nullptr;
    delete dominoPlayer2;
    dominoPlayer2 = nullptr;
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
    int a = 20;

    for (int i = 0; i < b->myPieces.size(); i++) {
        if (!b->myPieces[i].hidden) {
            b->myPieces[i].brickX = a;
            b->myPieces[i].brickY = wh - 90;
            renderBrick(&b->myPieces[i]);
        }
        a += 35;
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

    if (menuBool) {
        SDL_RenderCopy(renderer, menuFont, NULL, &menudRect);
        SDL_RenderCopy(renderer, difficultyFont, NULL, &difficultydRect);
        SDL_RenderCopy(renderer, normalDifFont, NULL, &normaldRect);
        SDL_RenderCopy(renderer, mediumDifFont, NULL, &mediumdRect);
        SDL_RenderCopy(renderer, hardDifFont, NULL, &harddRect);
        SDL_RenderCopy(renderer, themeFont, NULL, &themedRect);
        SDL_RenderCopy(renderer, seaFont, NULL, &seadRect);
        SDL_RenderCopy(renderer, carFont, NULL, &cardRect);
        SDL_RenderCopy(renderer, flowerFont, NULL, &flowerdRect);
        SDL_RenderCopy(renderer, okFont, NULL, &okdRect);

        if (isDiffShown) {
            SDL_RenderCopy(renderer, fpointerFont, NULL, &fpointerdRect);
        }
        if (isThemeShown) {
            SDL_RenderCopy(renderer, spointerFont, NULL, &spointerdRect);
        }

    }
    else {
        renderOponent(dominoTable->oppositePlayer);

        renderPlayer(dominoTable->currentPlayer);

        renderTable(dominoTable);

        if (gameOver) {
            if (isDraw) {
                SDL_RenderCopy(renderer, drawFont, NULL, &drawdRect);

              }
            if (p1Winner) {
                SDL_RenderCopy(renderer, p1winnerFont, NULL, &p1winnerdRect);

            }
            if (p2Winner) {
                SDL_RenderCopy(renderer, p2winnerFont, NULL, &p2winnerdRect);

            }
        }

        
    }

    SDL_RenderPresent(renderer);




}

void Game::update()
{
    if (startGame) {
        if (difficulty == 0) {
            difficulty = 10;
        }

        if (theme == "") {
            string themeArr[3] = { "sea", "cars", "flowers" };
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, 2);
            int randomNumber = dis(gen);
            theme = themeArr[randomNumber];
        }
        dominoPlayer1 = new DominoPlayer();
        dominoPlayer1->name = "Player1";
        dominoPlayer2 = new DominoPlayer();
        dominoPlayer2->name = "Player2";
        dominoTable = new DominoTable();

        for (int i = 0; i < difficulty;i++) {
            DominoBrick d;
            dominoPlayer1->addPiece(d);
        }

        for (int i = 0; i < difficulty;i++) {
            DominoBrick d;
            dominoPlayer2->addPiece(d);
        }

        dominoTable->createFirstBrick();
        dominoTable->currentPlayer = dominoPlayer1;
        dominoTable->oppositePlayer = dominoPlayer2;

        startGame = false;
    }
    if (!menuBool) {

        if (hasNoMoves(dominoPlayer1) && hasNoMoves(dominoPlayer2) && dominoPlayer1->realSize() == dominoPlayer2->realSize()) {
            isDraw = true;
            gameOver = true;
        }
        if (hasNoMoves(dominoPlayer1) && !hasNoMoves(dominoPlayer2) && dominoPlayer1->realSize() >= dominoPlayer2->realSize()) {

            p2Winner = true;

            gameOver = true;

        }

        if (hasNoMoves(dominoPlayer2) && !hasNoMoves(dominoPlayer1) && dominoPlayer2->realSize() >= dominoPlayer1->realSize()) {
            p1Winner = true;
            gameOver = true;
        }

        
    }
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
                if (!menuBool) {
                    if (msy < wh && msy >= (wh - 90) && msx >= 20) {
                        for (int i = 0; i < dominoTable->currentPlayer->myPieces.size();i++) {
                            if (dominoTable->currentPlayer->myPieces[i].brickX <= msx && msx <= dominoTable->currentPlayer->myPieces[i].lastX && dominoTable->currentPlayer->myPieces[i].brickY <= msy && dominoTable->currentPlayer->myPieces[i].lastY >= msy) {
                                if (dominoTable->currentPlayer->myPieces[i].hidden) {
                                    return;
                                }
                                selectedItem = i;
                                selected = true;
                                return;
                            }
                        }
                    }
                    if (dominoTable->tablePieces.back().arrowes == "down" || dominoTable->tablePieces.back().arrowes == "right") {
                        if ((msx >= dominoTable->sideBx - 25 && msx <= dominoTable->sideBx) && (msy <= dominoTable->sideBy && msy >= dominoTable->sideBy - 25)) {

                            if (selected) {
                                if (selectedItem < 0) {
                                    return;
                                }
                                DominoBrick dd = dominoTable->currentPlayer->myPieces[selectedItem];
                                int nextPath = dominoTable->tablePieces.size();

                                cout << dominoTable->pathfinder[nextPath] << endl;
                                if (dominoTable->pathfinder[nextPath] == "down" && (dd.pValue1 == dominoTable->valueToMatch || dd.pValue2 == dominoTable->valueToMatch) && dominoTable->tablePieces.back().arrowes == "down") {
                                    if (dd.pValue2 == dominoTable->valueToMatch && dd.pValue1 != dominoTable->valueToMatch) {
                                        dd.direction = "up";
                                        dominoTable->valueToMatch = dd.pValue1;
                                    }
                                    else {
                                        dominoTable->valueToMatch = dd.pValue2;

                                    }
                                    //
                                    dd.brickX = dominoTable->sideBx - 25;
                                    dd.brickY = dominoTable->sideBy;
                                    //
                                    dd.arrowes = dominoTable->pathfinder[nextPath];

                                    //
                                    dominoTable->addPiece(dd);
                                    dominoTable->currentPlayer->myPieces[selectedItem].hidden = true;
                                    selected = false;
                                    selectedItem = -1;
                                    dominoTable->switchPlayers();
                                    return;
                                }
                                if (dominoTable->pathfinder[nextPath] == "right" && (dd.pValue1 == dominoTable->valueToMatch || dd.pValue2 == dominoTable->valueToMatch)) {
                                    if (dd.pValue2 == dominoTable->valueToMatch && dd.pValue1 != dominoTable->valueToMatch) {
                                        dd.direction = "left";
                                        dominoTable->valueToMatch = dd.pValue1;
                                    }
                                    else if (dd.pValue2 != dominoTable->valueToMatch && dd.pValue1 == dominoTable->valueToMatch) {
                                        dd.direction = "right";
                                        dominoTable->valueToMatch = dd.pValue2;
                                    }
                                    else if (dd.pValue2 == dd.pValue1) {
                                        dd.direction = "right";
                                        dominoTable->valueToMatch = dd.pValue2;
                                    }
                                    dd.arrowes = dominoTable->pathfinder[nextPath];
                                    dd.brickX = dominoTable->sideBx;
                                    dd.brickY = dominoTable->sideBy - 25;

                                    //
                                    dominoTable->addPiece(dd);
                                    dominoTable->currentPlayer->myPieces[selectedItem].hidden = true;
                                    selected = false;
                                    selectedItem = -1;
                                    dominoTable->switchPlayers();
                                    return;
                                }
                                if (dominoTable->pathfinder[nextPath] == "up" && (dd.pValue1 == dominoTable->valueToMatch || dd.pValue2 == dominoTable->valueToMatch)) {
                                    cout << "up" << endl;
                                    if (dd.pValue2 == dominoTable->valueToMatch && dd.pValue1 != dominoTable->valueToMatch) {

                                        dominoTable->valueToMatch = dd.pValue1;
                                    }
                                    else {
                                        dd.direction = "up";
                                        dominoTable->valueToMatch = dd.pValue2;
                                    }
                                    //
                                    dd.brickX = dominoTable->sideBx - 25;
                                    dd.brickY = dominoTable->sideBy - 75;
                                    //
                                    dd.arrowes = dominoTable->pathfinder[nextPath];

                                    //
                                    dominoTable->addPiece(dd);
                                    dominoTable->currentPlayer->myPieces[selectedItem].hidden = true;
                                    selected = false;
                                    selectedItem = -1;
                                    dominoTable->switchPlayers();
                                    return;
                                }
                                if (dominoTable->pathfinder[nextPath] == "down" && (dd.pValue1 == dominoTable->valueToMatch || dd.pValue2 == dominoTable->valueToMatch) && dominoTable->tablePieces.back().arrowes == "right") {
                                    cout << "up" << endl;
                                    if (dd.pValue2 == dominoTable->valueToMatch && dd.pValue1 != dominoTable->valueToMatch) {
                                        dd.direction = "up";
                                        dominoTable->valueToMatch = dd.pValue1;
                                    }
                                    else {
                                        
                                        dominoTable->valueToMatch = dd.pValue2;
                                    }
                                    //
                                    dd.brickX = dominoTable->sideBx;
                                    dd.brickY = dominoTable->sideBy - 25;
                                    //
                                    dd.arrowes = dominoTable->pathfinder[nextPath];

                                    //
                                    dominoTable->addPiece(dd);
                                    dominoTable->currentPlayer->myPieces[selectedItem].hidden = true;
                                    selected = false;
                                    selectedItem = -1;
                                    dominoTable->switchPlayers();
                                    return;
                                }
                            }
                        }

                    }
                
                //xx
                if (dominoTable->tablePieces.back().arrowes == "up") {
                        
                    if ((msx >= dominoTable->sideBx - 25 && msx <= dominoTable->sideBx) && (msy >= dominoTable->sideBy && msy <= dominoTable->sideBy + 25)) {
                        cout << "up2" << endl;
                        if (selected) {
                            if (selectedItem < 0) {
                                return;
                            }
                            DominoBrick dd = dominoTable->currentPlayer->myPieces[selectedItem];
                            int nextPath = dominoTable->tablePieces.size();

                            
                            if (dominoTable->pathfinder[nextPath] == "up" && (dd.pValue1 == dominoTable->valueToMatch || dd.pValue2 == dominoTable->valueToMatch)) {
                                if (dd.pValue2 == dominoTable->valueToMatch && dd.pValue1 != dominoTable->valueToMatch) {
                                    
                                    dominoTable->valueToMatch = dd.pValue1;
                                }
                                else {
                                    dd.direction = "up";
                                    dominoTable->valueToMatch = dd.pValue2;

                                }
                                //
                                dd.brickX = dominoTable->sideBx - 25;
                                dd.brickY = dominoTable->sideBy - 50;
                                //
                                dd.arrowes = dominoTable->pathfinder[nextPath];

                                //
                                dominoTable->addPiece(dd);
                                dominoTable->currentPlayer->myPieces[selectedItem].hidden = true;
                                selected = false;
                                selectedItem = -1;
                                dominoTable->switchPlayers();
                                return;
                            }
                            if (dominoTable->pathfinder[nextPath] == "right" && (dd.pValue1 == dominoTable->valueToMatch || dd.pValue2 == dominoTable->valueToMatch)) {
                                if (dd.pValue2 == dominoTable->valueToMatch && dd.pValue1 != dominoTable->valueToMatch) {
                                    dd.direction = "left";
                                    dominoTable->valueToMatch = dd.pValue1;
                                }
                                else {
                                    dd.direction = "right";
                                    dominoTable->valueToMatch = dd.pValue2;

                                }
                                //
                                dd.brickX = dominoTable->sideBx - 25;
                                dd.brickY = dominoTable->sideBy - 25;
                                //
                                dd.arrowes = dominoTable->pathfinder[nextPath];

                                //
                                dominoTable->addPiece(dd);
                                dominoTable->currentPlayer->myPieces[selectedItem].hidden = true;
                                selected = false;
                                selectedItem = -1;
                                dominoTable->switchPlayers();
                                return;
                            }

                        }
                    }
                    return;
                }
                
            } //xx
        
                if (menuBool) {
                    if (msy >= normaldRect.y && msy < mediumdRect.y) {
                        fpointerdRect.x = normaldRect.x - 30;
                        fpointerdRect.y = normaldRect.y;
                        if (!isDiffShown) {
                            isDiffShown = true;
                        }
                            difficulty = 10;
                                     
                    }
                    if (msy >= mediumdRect.y && msy < harddRect.y) {
                        fpointerdRect.x = mediumdRect.x - 30;
                        fpointerdRect.y = mediumdRect.y;
                        if (!isDiffShown) {
                            isDiffShown = true;
                        }
                            difficulty = 20;
      
                        
                    }
                    if (msy >= harddRect.y && msy < themedRect.y) {
                        fpointerdRect.x = harddRect.x - 30;
                        fpointerdRect.y = harddRect.y;
                        if (!isDiffShown) {
                            isDiffShown = true;
                        }
                            difficulty = 30;
           
                    }

                    if (msy >= seadRect.y && msy < cardRect.y) {
                        spointerdRect.x = seadRect.x - 30;
                        spointerdRect.y = seadRect.y;
                        if (!isThemeShown) {
                            isThemeShown = true;
                        }
                            theme = "sea";
      
                        
                    }
                    if (msy >= cardRect.y && msy < flowerdRect.y) {
                        spointerdRect.x = cardRect.x - 30;
                        spointerdRect.y = cardRect.y;
                        if (!isThemeShown) {
                            isThemeShown = true;
                        }
                            theme = "cars";
                            
     
                    }
                    if (msy >= flowerdRect.y && msy < flowerdRect.y + flowerdRect.h) {
                        spointerdRect.x = flowerdRect.x - 30;
                        spointerdRect.y = flowerdRect.y;
                        if (!isThemeShown) {
                            isThemeShown = true;
                        }
                            theme = "flowers";
             
                    }
                    if (msy >= okdRect.y && msy < okdRect.y + okdRect.h) {
                        
                        startGame = true;
                        menuBool = false;
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
    delete dominoPlayer1;
    dominoPlayer1 = nullptr;
    delete dominoPlayer2;
    dominoPlayer2 = nullptr;
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

void Game::renderBrick(DominoBrick* b)
{
    if (b->direction == "down") {

        string currTheme = theme + "_" + to_string(b->pValue1);
        TextureManager::Instance()->drawTexture(currTheme, b->brickX, b->brickY, 25, 25, 0, renderer, SDL_FLIP_VERTICAL);
        currTheme = theme + "_" + to_string(b->pValue2);
        TextureManager::Instance()->drawTexture(currTheme, b->brickX, b->brickY + 25, 25, 25, 0, renderer);


        if (b->arrowes == "down") {

        b->lastX = b->brickX + 25;
        b->lastY = b->brickY + 50;
        }
        if (b->arrowes == "up") {
            b->lastX = b->brickX + 25;
            b->lastY = b->brickY;
        }
        
       

    }
    if (b->direction == "left") {
        
        string currTheme = theme + "_" + to_string(b->pValue1);
        TextureManager::Instance()->drawTexture(currTheme, b->brickX + 25, b->brickY, 25, 25, -90, renderer);
        currTheme = theme + "_" + to_string(b->pValue2);
        TextureManager::Instance()->drawTexture(currTheme, b->brickX, b->brickY , 25, 25, 90, renderer);
        b->lastX = b->brickX + 50;
        b->lastY = b->brickY + 25;
    }

    if (b->direction == "right") {
        string currTheme = theme + "_" + to_string(b->pValue1);
        TextureManager::Instance()->drawTexture(currTheme, b->brickX, b->brickY, 25, 25, 90, renderer);
        currTheme = theme + "_" + to_string(b->pValue2);
        TextureManager::Instance()->drawTexture(currTheme, b->brickX + 25, b->brickY, 25, 25, -90, renderer);
        
        b->lastX = b->brickX + 50;
        b->lastY = b->brickY + 25;
        
        
    }
    if (b->direction == "up") {
        
        string currTheme = theme + "_" + to_string(b->pValue1);
        TextureManager::Instance()->drawTexture(currTheme, b->brickX, b->brickY + 25, 25, 25, 0, renderer);
        currTheme = theme + "_" + to_string(b->pValue2);
        TextureManager::Instance()->drawTexture(currTheme, b->brickX, b->brickY, 25, 25, 0, renderer, SDL_FLIP_VERTICAL);
        
        if (b->arrowes == "down") {

            b->lastX = b->brickX + 25;
            b->lastY = b->brickY + 50;
        }
        if (b->arrowes == "up") {
            b->lastX = b->brickX + 25;
            b->lastY = b->brickY;
        }
        
        
    }
}

void Game::renderTable(DominoTable* s)
{

    int ww, wh;
    SDL_GetWindowSize(window, &ww, &wh);
    
    for (int i = 0; i < s->tablePieces.size(); i++) {
        
        renderBrick(&s->tablePieces[i]);
        
    }
    DominoBrick last = s->tablePieces.back();
    dominoTable->sideBx = last.lastX;
    dominoTable->sideBy = last.lastY;
}

bool Game::hasNoMoves(DominoPlayer* b)
{
    for (auto& brick: b->myPieces) {
        if ((brick.pValue1 == dominoTable->valueToMatch || brick.pValue2 == dominoTable->valueToMatch) && !brick.hidden) {
            
            return false;
        }
    }
    return true;
}

void Game::renderOponent(DominoPlayer* b)
{
    int ww, wh;
    SDL_GetWindowSize(window, &ww, &wh);
    int displayCount = 0;
    for (auto& brick: b->myPieces) {
        
        if (!brick.hidden) {
            displayCount++;
        }
        
    }

    int a = 20;
   
    for (int i = 0; i < displayCount;i++) {
        TextureManager::Instance()->drawTexture("background", a, 20, 25, 25, 0, renderer);
        a += 35;
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

    font1 = TTF_OpenFont("assets/fonts/Valorant.ttf", 65);
    font2 = TTF_OpenFont("assets/fonts/Valorant.ttf", 45);
    font3 = TTF_OpenFont("assets/fonts/Valorant.ttf", 25);

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
    createTextureFromText("Player 1 is Winner", font2, p1winnerFont);
    createTextureFromText("Player 2 is Winner", font2, p2winnerFont);
    createTextureFromText("Draw", font2, drawFont);
   
    

    SDL_Surface* tempSurfaceText = NULL;
    int ww, wh;
    SDL_GetWindowSize(window, &ww, &wh);
    int tw, th;
    SDL_QueryTexture(menuFont, 0, 0, &tw, &th);
    menudRect = { ww / 2 - tw / 2, (int)(0 + wh * 0.15 - th / 2), tw,th };

    SDL_QueryTexture(difficultyFont, 0, 0, &tw, &th);
    difficultydRect = { ww / 2 - tw / 2, (int)(0 + wh * 0.15 - th / 2) + 70, tw,th };

    SDL_QueryTexture(normalDifFont, 0, 0, &tw, &th);
    normaldRect = { ww / 2 - tw / 2, (int)(0 + wh * 0.15 - th / 2) + 120, tw,th };

    SDL_QueryTexture(mediumDifFont, 0, 0, &tw, &th);
    mediumdRect = { ww / 2 - tw / 2, (int)(0 + wh * 0.15 - th / 2) + 160, tw,th };

    SDL_QueryTexture(hardDifFont, 0, 0, &tw, &th);
    harddRect = { ww / 2 - tw / 2, (int)(0 + wh * 0.15 - th / 2) + 200, tw,th };

    SDL_QueryTexture(themeFont, 0, 0, &tw, &th);
    themedRect = { ww / 2 - tw / 2, (int)(0 + wh * 0.15 - th / 2) + 300, tw,th };

    SDL_QueryTexture(seaFont, 0, 0, &tw, &th);
    seadRect = { ww / 2 - tw / 2, (int)(0 + wh * 0.15 - th / 2) + 350, tw,th };

    SDL_QueryTexture(carFont, 0, 0, &tw, &th);
    cardRect = { ww / 2 - tw / 2, (int)(0 + wh * 0.15 - th / 2) + 390, tw,th };

    SDL_QueryTexture(flowerFont, 0, 0, &tw, &th);
    flowerdRect = { ww / 2 - tw / 2, (int)(0 + wh * 0.15 - th / 2) + 430, tw,th };

    SDL_QueryTexture(okFont, 0, 0, &tw, &th);
    okdRect = { ww / 2 - tw / 2, (int)(0 + wh * 0.15 - th / 2) + 500, tw,th };

    SDL_QueryTexture(fpointerFont, 0, 0, &tw, &th);
    fpointerdRect = { 0, 0, tw,th };
    
    SDL_QueryTexture(spointerFont, 0, 0, &tw, &th);
    spointerdRect = { 0, 0, tw,th };

    SDL_QueryTexture(p1winnerFont, 0, 0, &tw, &th);
    p1winnerdRect = { ww / 2 - tw / 2, wh / 2 - th / 2, tw,th };

    SDL_QueryTexture(p2winnerFont, 0, 0, &tw, &th);
    p2winnerdRect = { ww / 2 - tw / 2, wh / 2 - th / 2, tw,th };

    SDL_QueryTexture(drawFont, 0, 0, &tw, &th);
    drawdRect = { ww / 2 - tw / 2, wh / 2 - th / 2, tw,th };

    SDL_FreeSurface(tempSurfaceText);
    TTF_CloseFont(font1);


    return true;
}
