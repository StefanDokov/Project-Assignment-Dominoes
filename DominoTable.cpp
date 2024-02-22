#include "DominoTable.h"

DominoTable::DominoTable(): currentPlayer(nullptr), oppositePlayer(nullptr)
{
	
}

void DominoTable::addPiece(DominoBrick a)
{
	tablePieces.push_back(a);
}

void DominoTable::createFirstBrick()
{
	DominoBrick db;
	db.pValue2 = db.pValue1;
	db.direction = "right";
	db.brickX = 50;
	db.brickY = 350;
	tablePieces.push_back(db);
	
}
