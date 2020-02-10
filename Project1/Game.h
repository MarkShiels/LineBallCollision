#include <iostream>
#include <SFML/Graphics.hpp>
#include "include/Thor/Vectors.hpp"

class Game
{

public:
	
	sf::RenderWindow	window;
	sf::CircleShape		ball;

	sf::Vector2f		ballVelocity;
	sf::Vector2f		gravity;

	const float			maxSpeed{5};

	sf::Vector2f		p1;
	sf::Vector2f		p2;
	sf::Vertex			line[2];

	Game();
	~Game();

	void	init();
	void	run();
	void	update();
	void	updateBall();
	void	checkCollision();
	void	render();
};
