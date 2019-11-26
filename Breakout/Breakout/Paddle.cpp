#pragma once

#include "Paddle.h"

extern float deltaTime;
extern RenderWindow window;

Paddle::Paddle(Vector2f position, Vector2f size, float velocity, Color color) {
	this->position = position;
	direction = Vector2f(0, 0);
	this->size = size;
	this->originSize = size;
	this->velocity = velocity;
	paddle.setOrigin(size.x / 2, size.y / 2);
	texture.loadFromFile("Paddle_Texture.png");
	sprite.setTexture(texture);
	sprite.setOrigin(90, 25);
	sprite.setColor(color);
}

void Paddle::MoveLeft() {
	position = position + Vector2f(-1, 0) * velocity * deltaTime;
}
void Paddle::MoveRight() {
	position = position + Vector2f(1, 0) * velocity * deltaTime;
}

void Paddle::UpdateByAI(Vector2f bPos) {
	if (bPos.x < position.x) {
		MoveLeft();
	}
	else
	{
		MoveRight();
	}
}

void Paddle::Draw() {
	paddle.setSize(size);
	paddle.setPosition(position);
	sprite.setScale(size.x / 160, size.y / 30);
	sprite.setPosition(position);
	window.draw(sprite);
}
