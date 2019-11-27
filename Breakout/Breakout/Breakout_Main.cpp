#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
//#include "VectorCalculation.h"
#include "Ball.h"
//#include "Brick.h"
#include "Paddle.h"
#include "UI.h"
#include "AudioResource.h"
#include "SpriteAnimation.h"
#include "LevelManager.h"
using namespace sf;

float deltaTime;

Vector2f winSize(800, 900);
Vector2f p1Size, obSize, p1Pos;
Vector2f ballDir, ballPos;
float ballRadius, ballSpeed, p1Speed, t;
int fps, frameCount, score, life, lvNO;
bool isReadyState, isEnd;

float Magnitude(Vector2f v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

Vector2f Normalize(Vector2f v) {
	return v / Magnitude(v);
}

Vector2f Lerp(Vector2f v1, Vector2f v2, float t) {
	if (t < 0) { t = 0; }
	if (t > 1) { t = 1; }
	return v1 * (1 - t) + v2 * t;
}

float Dot(Vector2f v1, Vector2f v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

void Initial() {
	winSize = Vector2f(800, 900);
	p1Size = Vector2f(160, 25);
	obSize = Vector2f(130, 40);
	p1Pos = Vector2f(winSize.x / 2, winSize.y - p1Size.y * 1.5);
	ballPos = Vector2f(winSize.x / 2, winSize.y / 2);
	ballDir = Normalize(Vector2f(0, -1));
	ballSpeed = 500;
	p1Speed = 600;
	ballRadius = 25.0f;
	score = 0;
	life = 3;
	isReadyState = true;
	isEnd = true;
	lvNO = 0;
}

RenderWindow window(VideoMode(winSize.x, winSize.y), "Pong!");

int main()
{
	Initial();
	Ball ball(ballPos, ballDir, ballRadius, ballSpeed);
	LevelManager levelManager;

	Paddle player1(p1Pos, p1Size, p1Speed, Color(0, 255, 0, 255));

	SpriteAnimation anim("Sprite_Sheet_Test.png", 8, 1, 8);
	anim.speed = 0.3;
	SpriteAnimation kojima("kojima.png", 3, 3, 8);
	kojima.position = Vector2f(winSize.x / 2, winSize.y / 2);
	kojima.speed = 3;

	AudioResource hit("Hit.wav");

	Texture backgroundTexture;
	backgroundTexture.loadFromFile("Background_Texture.png");

	Sprite background;
	background.setTexture(backgroundTexture);

	UI fpsUI(20, Vector2f(winSize.x - 100, 0));
	UI scoreUI(40, Vector2f(winSize.x / 2 - 10, 10));
	scoreUI.content = std::to_string(score);
	UI winUI(50, Vector2f(winSize.x / 2 - 280, winSize.y / 2 - 75));
	UI menuUI(40, Vector2f(190, winSize.y - 175));
	UI health(40, Vector2f(0, 20));
	menuUI.content = "Press space to start";

	Time time;
	Clock fpsClock, fpsUpdate, physicsDetect;

	while (window.isOpen())
	{
		//deltatime and fps
		deltaTime = fpsClock.getElapsedTime().asSeconds();	//time between two frame
		time += fpsClock.getElapsedTime();

		frameCount++;
		if (frameCount >= 10) {	//cauculate fps per 10 frame
			fps = frameCount / time.asSeconds();
			//fpsUI.setString("fps:" + std::to_string(fps));
			frameCount = 0;
			time = Time().Zero;
		}
		if (fpsUpdate.getElapsedTime().asSeconds() >= 0.1) {	//update fps per 0.1s
			fpsUI.content = "fps:" + std::to_string(fps);
			fpsUpdate.restart();
		}
		fpsClock.restart();

		//ready state
		if (isReadyState) {
			ball.velocity = 0;
			ball.position = player1.position - Vector2f(0, player1.size.y / 2 + ball.radius);
			ball.direction = Vector2f(0, -1);
			if (levelManager.isClear()) {
				levelManager.Creat(lvNO % 3);
			}
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				ball.velocity = ballSpeed + lvNO * 60;
				isReadyState = false;
			}
		}

		//if win 
		if (levelManager.isClear()) {	//win detection
			deltaTime = 0;
			isEnd = true;
			isReadyState = true;
			lvNO++;
			winUI.content = "			You Win! ";
			ball.velocity += 100;
		}

		//ball out of the table
		if (winSize.y < ball.position.y - ball.radius * 2) {	//ball off bottom edge
			isReadyState = true;
			isEnd = false;
			life--;
			if (life <= 0) {	//you die
				life = 3;
				isEnd = true;
				levelManager.Clear();
				winUI.content = "			You lose! \n\n		Your score is " + to_string(score);
				lvNO = 0;
				scoreUI.content = std::to_string(score = 0);
				ball.velocity = ballSpeed;
			}
		}

		//ball collision detection
		if (physicsDetect.getElapsedTime().asSeconds() >= 0.02) {	//per 0.02s detect once
			physicsDetect.restart();
			if (winSize.x < ball.position.x + ball.radius) {	//ball hit right edge
				ball.position.x = winSize.x - ball.radius;
				ball.direction.x *= -1;
				hit.Play();
			}
			if (ball.position.x - ball.radius < 0) {	// ball hit left edge
				ball.position.x = ball.radius;
				ball.direction.x *= -1;
				hit.Play();
			}
			if (ball.position.y - ball.radius < 0) {	// ball hit top edge
				ball.position.y = ball.radius;
				ball.direction.y *= -1;
				hit.Play();
			}
			if (ball.Collision(player1)) {	//ball hit player's paddle
				hit.Play();
			}
			for (int i = 0; i < levelManager.bricks.size(); i++) {	//ball hit bricks
				switch (levelManager.bricks[i].type)
				{
				case Brick::normal:
					if (ball.Collision(levelManager.bricks[i])) {
						levelManager.bricks.erase(levelManager.bricks.begin() + i);
						scoreUI.content = std::to_string(score += 1);
					}
					break;
				case Brick::strong:
					if (ball.Collision(levelManager.bricks[i])) {
						if (levelManager.bricks[i].hitPoint-- <= 0) {
							levelManager.bricks.erase(levelManager.bricks.begin() + i);
						}
						scoreUI.content = std::to_string(score += 1);
					}
					break;
				case Brick::invincible:
					ball.Collision(levelManager.bricks[i]);
					break;
				case Brick::accelerate:
					if (ball.Collision(levelManager.bricks[i])) {
						levelManager.bricks.erase(levelManager.bricks.begin() + i);
						ball.velocity += 40;
						scoreUI.content = std::to_string(score += 1);
					}
					break;
				default:ball.Collision(levelManager.bricks[i]);
					break;
				}
			}
		}
		////continuous collision // still something wrong
		//if (ball.ContinuousCollision(player1)) {	//ball hit player1's paddle
		//	hit.Play();
		//}
		//if (ball.ContinuousCollision(player2)) {	//ball hit player2's paddle
		//	hit.Play();
		//}

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		//Keyboard input
		if (Keyboard::isKeyPressed(Keyboard::Left) && player1.size.x / 2 < player1.position.x) {
			player1.MoveLeft();
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) && player1.position.x < winSize.x - player1.size.x / 2) {
			player1.MoveRight();
		}


		//update ball
		ball.Update();

		//test
		anim.Update();
		kojima.Update();

		window.clear(Color(0, 0, 0, 0));
		//gameobject
		//kojima.Draw(window);
		levelManager.UpdateLevel();
		window.draw(background);
		ball.Draw();
		player1.Draw();

		//test
		anim.Draw();

		//ui
		fpsUI.Draw();
		scoreUI.Draw();
		if (isReadyState) {
			menuUI.Draw();
			if (isEnd) {
				winUI.Draw();
			}
		}
		window.display();
	}
	return 0;
}
