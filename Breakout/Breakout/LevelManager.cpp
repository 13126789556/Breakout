#include "LevelManager.h"

//extern Ball ball;

LevelManager::LevelManager() {
}

void LevelManager::Creat(int i) {
	ifstream levelFile("Level" + to_string(i) + ".txt");
	if (levelFile.is_open()) {
		getline(levelFile, level);
		//level.erase(level.find(' '));
		for (int i = 0; i < level.size(); i++) {
			switch (level[i]) {
			case '1': {
				Brick b;
				b.position = Vector2f(b.size.x * (i % 8 + 0.5),
					b.size.y * ((int)(i / 8) + 2.5));
				bricks.push_back(b);
				break;
			}
			case '0':
				break;
			default: {
				Brick b;
				b.position = Vector2f(b.size.x * (i % 8 + 0.5),
					b.size.y * ((int)(i / 8) + 2.5));
				bricks.push_back(b);
				break;
			}
			}
		}
	}
}

bool LevelManager::isClear() {
	if (bricks.size() == 0) { return true; }
	else { return false; }
}

void LevelManager::Clear() {
	bricks.clear();
}

void LevelManager::UpdateLevel()
{
	for (auto item : bricks) {
		//ball.Collision(item);
		item.Draw();
	}
}
