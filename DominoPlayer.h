#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "DominoBrick.h"
using namespace std;

class DominoPlayer {
public:
	DominoPlayer();
	int getSize();
	void addPiece(DominoBrick);
	vector<DominoBrick> myPieces;

private:

	

};