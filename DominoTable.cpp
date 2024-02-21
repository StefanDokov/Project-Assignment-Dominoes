#include "DominoTable.h"

DominoTable::DominoTable(): currentPlayer(nullptr), oppositePlayer(nullptr)
{
	
}

void DominoTable::addPiece(DominoBrick a)
{
	tablePieces.push_back(a);
}
