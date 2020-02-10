#include "Game.h"


Game::Game()
{
	window.create(sf::VideoMode(800, 600), "CircleLineCollision");

	init();
}

Game::~Game()
{
}

void Game::init()
{
	p1 = sf::Vector2f(300.f, 300.f);
	p2 = sf::Vector2f(500.f, 300.f);

	line[0] = sf::Vertex(p1);
	line[1] = sf::Vertex(p2);

	ball.setRadius(10);
	ball.setFillColor(sf::Color::White);
	ball.setOrigin(ball.getRadius(), ball.getRadius());
	ball.setPosition(400, 50);

	gravity = sf::Vector2f(0, .25);
	ballVelocity = sf::Vector2f(0, 0);
}

void Game::run()
{

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;


	sf::Clock clock;

	clock.restart();

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		timeSinceLastUpdate += clock.restart();

		if (timeSinceLastUpdate > timePerFrame)
		{
			update();
			timeSinceLastUpdate = sf::Time::Zero;
		}

		render();
	}
}

void Game::update()
{
	updateBall();
	checkCollision();
}

void Game::updateBall()
{
	ballVelocity += gravity;

	if (ballVelocity.y > maxSpeed)
	{
		ballVelocity = sf::Vector2f(ballVelocity.x, maxSpeed);
	}

	ball.setPosition(ball.getPosition() + ballVelocity);

}

void Game::checkCollision()
{
	line[0].position -= line[0].position;
	line[1].position -= line[0].position;

	ball.setPosition -= line[0].position;

	float angle = thor::polarAngle(p2);

}

void Game::render()
{
	window.clear(sf::Color::Black);

	window.draw(ball);

	window.draw(line, 2, sf::Lines);

	window.display();
}



