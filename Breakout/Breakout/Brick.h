#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
using namespace sf;

extern Texture textureN, textureS, textureB, textureI, textureA;
class Brick
{
public:
	Vector2f position;
	Vector2f size;
	RectangleShape rectangle;
	Sprite sprite;
	enum BrickType{normal, strong, invincible, accelerate};
	BrickType type;
	int hitPoint = 1;

	Brick(Vector2f position, Vector2f size);
	Brick(Vector2f position);
	Brick();
	void Draw();
	//~Brick();
};

