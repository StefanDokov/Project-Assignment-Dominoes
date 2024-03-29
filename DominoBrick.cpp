#include "DominoBrick.h"


DominoBrick::DominoBrick() {
    std::random_device rd;
    std::mt19937 gen(rd());  
    std::uniform_int_distribution<> dis(1, 6);
    int randomNumber = dis(gen);
    pValue1 = randomNumber;
    randomNumber = dis(gen); 
    pValue2 = randomNumber;
    brickX = 0;
    brickY = 0;
    hidden = false;
    direction = "down";
    arrowes = "down";
    lastX = 0;
    lastY = 0;
}


DominoBrick::DominoBrick(int a, int b) {
    
    pValue1 = a;
    pValue2 = b;
    brickX = 0;
    brickY = 0;
    hidden = false;
    direction = "down";
    arrowes = "down";
    lastX = 0;
    lastY = 0;
}

