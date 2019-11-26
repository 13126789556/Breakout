#pragma once

#include "Brick.h"

extern RenderWindow window;

Brick::Brick(Vector2f position, Vector2f size) {
	this->position = position;
	this->size = size;
	texture.loadFromFile("Brick.png");
	sprite.setTexture(texture);
	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.setScale(this->size.x / texture.getSize().x,
		this->size.y / texture.getSize().y);
	sprite.setColor(Color(255, 255, 255, 255));
	type = normal;
}
Brick::Brick(Vector2f position) {
	this->position = position;
	texture.loadFromFile("Brick.png");
	size = (Vector2f)texture.getSize();
	sprite.setTexture(texture);
	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.setScale(this->size.x / texture.getSize().x,
		this->size.y / texture.getSize().y);
	sprite.setColor(Color(255, 255, 255, 255));
	type = normal;
}
Brick::Brick() {
	texture.loadFromFile("Brick.png");
	size = (Vector2f)texture.getSize();
	position = Vector2f(size.x / 2, size.y / 2);
	sprite.setTexture(texture);
	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.setScale(this->size.x / texture.getSize().x,
		this->size.y / texture.getSize().y);
	sprite.setColor(Color(255, 255, 255, 255));
	type = normal;
}

void Brick::Draw() {
	sprite.setTexture(texture);
	sprite.setPosition(position);
	window.draw(sprite);
}

//Brick::~Brick() {
//
//}