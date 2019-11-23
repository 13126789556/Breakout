#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
using namespace sf;
class Brick
{
public:
	Vector2f size, position;
	RectangleShape rectangle;
	Texture texture;
	Sprite sprite;

	Brick(Vector2f position, Vector2f size);
	void Draw(RenderWindow& win);
	~Brick();
};

