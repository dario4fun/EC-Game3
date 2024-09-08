#pragma once

#include <SFML/Graphics.hpp>

class Enemy
{
private:

	unsigned _PointCount;		// Contador de puntos

	sf::CircleShape _Shape;		// Forma del enemy

	int _Type;					// Tipo
	float _Speed;				// Velocidad
	int _Hp;					// Vida
	int _HpMax;					// VidaMaxima
	int _Damage;				// Daño
	int _Points;				// Puntos

	void InitVariables();		// Iniciamos Variables
	void InitShape();			// Iniciamos forma

public:
	Enemy(float posX, float posY);	// Contructor

	const sf::FloatRect GetBounds() const;		// obtener forma
	const int& GetPoints() const;				// Obtener puntos
	const int& GetDamage() const;				// Obtener Daño

	void Update();
	void Render(sf::RenderTarget* target);
};

