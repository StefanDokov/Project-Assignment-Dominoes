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
	void addPiece(DominoBrick);
	void createFirstBrick();
	DominoPlayer* currentPlayer;
	DominoPlayer* oppositePlayer;
	vector<DominoBrick> tablePieces;
private:
	
	
};