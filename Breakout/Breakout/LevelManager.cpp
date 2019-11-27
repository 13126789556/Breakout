#include "LevelManager.h"

//extern Ball ball;

LevelManager::LevelManager() {
}

void LevelManager::Creat(int i) {
	ifstream levelFile("Level" + to_string(i) + ".txt");
	level.clear();
	if (levelFile.is_open()) {
		//getline(levelFile, level);
		string temp;
		while (getline(levelFile, temp)) {
			level += temp;
		}
		for (int i = 0; i < level.size(); i++) {
			switch (level[i]) {
			case 'n': {
				Brick b;
				b.type = Brick::normal;
				b.position = Vector2f(b.size.x * (i % 8 + 0.5),
					b.size.y * ((int)(i / 8) + 2.5));
				bricks.push_back(b);
				break;
			}
			case 's': {
				Brick b;
				b.type = Brick::strong;
				b.position = Vector2f(b.size.x * (i % 8 + 0.5),
					b.size.y * ((int)(i / 8) + 2.5));
				bricks.push_back(b);
				break;
			}
			case 'i': {
				Brick b;
				b.type = Brick::invincible;
				b.position = Vector2f(b.size.x * (i % 8 + 0.5),
					b.size.y * ((int)(i / 8) + 2.5));
				bricks.push_back(b);
				break;
			}
			case 'a': {
				Brick b;
				b.type = Brick::accelerate;
				b.position = Vector2f(b.size.x * (i % 8 + 0.5),
					b.size.y * ((int)(i / 8) + 2.5));
				bricks.push_back(b);
				break;
			}
			case '0':
				break;
			}
		}
	}
}

bool LevelManager::isClear() {
	//if (bricks.size() == 0) { return true; }
	//else { return false; }
	for (int i = 0; i < bricks.size(); i++) {
		if (bricks[i].type != Brick::invincible) {
			return false;
		}
	}
	return true;
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
