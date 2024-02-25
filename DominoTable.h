#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "DominoPlayer.h"
#include "DominoBrick.h"
using namespace std;

class DominoTable {
public:
	DominoTable();
	~DominoTable() {};
	int tableVal1;
	int tableVal2;
	int sideAx;
	int sideBx;
	int sideAy;
	int sideBy;
	int valueToMatch;
	void addPiece(DominoBrick);
	void createFirstBrick();
	DominoPlayer* currentPlayer;
	DominoPlayer* oppositePlayer;
	vector<DominoBrick> tablePieces;
	vector<string> pathfinder;
	vector<DominoBrick> allBricks;
	void createBricks();
	void shuffleBricks();
	DominoPlayer* tempP = nullptr;
	void switchPlayers();
private:
	
	
};