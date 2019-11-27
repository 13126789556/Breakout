#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include "Brick.h"
#include "Ball.h"

using namespace sf;
using namespace std;

class LevelManager
{
public:
	string level;
	vector<Brick> bricks;
	Vector2f pos;

	LevelManager();
	void Creat(int i);
	bool isClear();
	void Clear();
	void UpdateLevel();
};

