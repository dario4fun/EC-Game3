#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

class Bullet
{
private:
	sf::Sprite _Shape;			// Sprite de la bala

	sf::Vector2f _Direction;	// Dirección
	float _MovementSpeed;		// Velocidad de movimiento

public:
	Bullet(sf::Texture* texture, float posX, float posY, float dirX, float dirY, float movementSpeed); // Constructor

	const sf::FloatRect GetBounds() const;	// Obtener limites

	void Update();
	void Render(sf::RenderTarget* target);

};

