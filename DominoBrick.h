#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

class DominoBrick {
public:
	DominoBrick();
	~DominoBrick() {};

	int pValue1;
	int pValue2;
	bool hidden;
	string direction;
	int brickX;
	int brickY;
	int lastX;
	int lastY;
	string arrowes;
private:



};