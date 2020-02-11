#include <iostream>
#include <SFML/Graphics.hpp>
#include "include/Thor/Vectors.hpp"
#include <cmath>
#include <math.h>


class Game
{

public:
	
	bool checked{false};

	sf::RenderWindow	window;
	sf::CircleShape		ball;
	sf::RectangleShape	box;

	sf::Vector2f		ballVelocity;
	sf::Vector2f		gravity;

	const float			maxSpeed{5};
	float				pAngle;

	sf::Vector2f		p0;
	sf::Vector2f		p1;
	sf::Vector2f		ballCenterOffset;
	sf::Vector2f		movementVector;
	sf::Vertex			line[2];
	sf::Vector2f		tempVel;
	sf::Vector2f		tempP0;
	sf::Vector2f		tempP1;
	Game();
	~Game();

	void	init();
	void	run();
	void	update();
	void	updateBall();
	void	checkCollision();
	void	render();
};
