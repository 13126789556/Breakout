#pragma once
#include <string>
#include "Brick.h"
using namespace std;
using namespace sf;

class LevelManager
{
public:
	string level;
	vector<Brick> bricks;
};

