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
	p0 = sf::Vector2f(300.f, 300.f);
	p1 = sf::Vector2f(500.f, 450.f);

	line[0] = sf::Vertex(p0);
	line[1] = sf::Vertex(p1);

	ballCenterOffset = sf::Vector2f(ball.getRadius(),ball.getRadius());

	ball.setRadius(10);
	ball.setFillColor(sf::Color::Red);
	ball.setOrigin(ball.getRadius(), ball.getRadius());
	ball.setPosition(400, 50);

	box.setSize(sf::Vector2f(ball.getRadius()*2, ball.getRadius()*2));
	box.setOrigin(ball.getRadius(), ball.getRadius());
	box.setPosition(ball.getPosition());

	gravity = sf::Vector2f(0, .25f);
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
	if (!checked)
	{
		checkCollision();
	}
	
	updateBall();
}

void Game::updateBall()
{
	ballVelocity += gravity;

	if (ballVelocity.y > maxSpeed)
	{
		ballVelocity = sf::Vector2f(ballVelocity.x, maxSpeed);
	}

	ball.setPosition(ball.getPosition() + ballVelocity);
	box.setPosition(ball.getPosition());
}

void Game::checkCollision()
{
	tempVel = ball.getPosition() + ballVelocity;
	movementVector = line[0].position;

	line[0].position -= movementVector;
	line[1].position -= movementVector;

	ball.setPosition(ball.getPosition() - movementVector);

	pAngle = thor::polarAngle(line[1].position);

	thor::rotate(tempVel, -pAngle);

	sf::Vector2f ballPos = sf::Vector2f(ball.getPosition().x, ball.getPosition().y);

	thor::rotate(line[1].position, -pAngle);
	thor::rotate(ballPos, -pAngle);
	ball.setPosition(ballPos);
	box.setPosition(ball.getPosition());
	
	if (tempVel.y > 0)
	{
		if ((box.getPosition().x - ball.getRadius()) > line[1].position.x || (box.getPosition().x + ball.getRadius()) < 0)
		{
			std::cout << "no collision" << std::endl;
		}
		else if(box.getPosition().y + ball.getRadius() >= 0)
		{
			std::cout << "collision" << std::endl;
			checked = true;
		}
		else
		{
			std::cout << "no collision" << std::endl;
		}
	}
	else
	{
		std::cout << "no collision" << std::endl;
	}

	thor::rotate(line[1].position, pAngle);
	thor::rotate(ballPos, pAngle);
	ball.setPosition(ballPos);
	box.setPosition(ball.getPosition());

	line[0].position += movementVector;
	line[1].position += movementVector;

	ball.setPosition(ball.getPosition() + movementVector);


}

void Game::render()
{
	window.clear(sf::Color::Black);

	window.draw(box);
	window.draw(ball);

	window.draw(line, 2, sf::Lines);

	window.display();
}



