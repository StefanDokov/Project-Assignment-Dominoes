#include "DominoTable.h"

DominoTable::DominoTable(): currentPlayer(nullptr), oppositePlayer(nullptr)
{
	valueToMatch = 0;
	pathfinder = { "down", "down", "down", "down", "down", "down", "down", "down", "down", "right", "up", "up", "up", "up", "up", "up", "up", "up", "up", "right", "down","down","down",
	"down", "down" ,"down","down" ,"down" ,"down" ,"right", "up", "up", "up", "up", "up", "up", "up", "up", "up", "right", "down", "down", "down", "down", "down", "down", "down", "down", "down", "right", "up", "up", "up", "up", "up", "up", "up", "up", "up", };

}

void DominoTable::addPiece(DominoBrick a)
{
	tablePieces.push_back(a);
	
}

void DominoTable::createFirstBrick()
{
	DominoBrick db;
	db.brickX = 20;
	db.brickY = 65;
	valueToMatch = db.pValue2;
	tablePieces.push_back(db);
	
}

void DominoTable::switchPlayers()
{
	tempP = currentPlayer;
	currentPlayer = oppositePlayer;
	oppositePlayer = tempP;
	tempP = nullptr;
}
