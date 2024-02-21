#include "DominoPlayer.h"


DominoPlayer::DominoPlayer() {

}

int DominoPlayer::getSize() {
	return myPieces.size();
}

void DominoPlayer::addPiece(DominoBrick a) {
	myPieces.push_back(a);
}