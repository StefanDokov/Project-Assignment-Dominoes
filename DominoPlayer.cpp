#include "DominoPlayer.h"


DominoPlayer::DominoPlayer() {
	name = "";
}

int DominoPlayer::getSize() {
	return myPieces.size();
}

void DominoPlayer::addPiece(DominoBrick a) {
	myPieces.push_back(a);
}

int DominoPlayer::realSize()
{
	int result = 0;

	for (auto& bricker : myPieces) {
		if (!bricker.hidden) {
			result++;
		}
	}
	return result;
}
