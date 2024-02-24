# Project-Assignment-Dominoes
Project-Assignment-Dominoes

Моля добави/покани https://github.com/MilkoBalev като collaborator (repo -> Settings -> Collaborators -> Add people -> MilkoBalev)
Поздрави,
Началното меню работи, като играта започва. За сега нямам таймер за менюто. Върви на змия като започва от горен ляв ъгъл и върви надолу, после на дясно и нагоре. За момента само показва дали Player 1 е победител или Player 2.

"void Game::renderBrick(DominoBrick* b)
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
}" 
Това ми е флипер функцията. В момента direction е посоката на която се флипва, а arrowes е посоката на която върви самото блокче. lastX и lastY трябва да ги подам, за да може render функцията за масата да знае от къде е края на последното блокче, което после използвам 
за рендер на следващото такова. В случая ако искам да имам флип бутон, просто трябва да направя функция която да върти "up","down", "left" и "right", като просто променя directiona на избраното блокче и то само се рендерира във функцията по-късно.

За момента мисля, че всичко върви коректно, като за момент не разпознаваше отделни плочки, но след известни корекции от моя страна "привидно" изглежда добре.
