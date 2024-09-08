#pragma once

#include<iostream>	
#include"Bullet.h";


class Player
{
private:
	sf::Sprite _Sprite;			// Sprite 
	sf::Texture _Texture;		// Textura

	float _MovementSpeed;		// Velocida de movimiento
	float _AttackCooldown;		// Contador de tiempo entre ataques
	float _AttackCooldownMax;	// Tiempo entre ataques maximo

	int _Hp;					// Vida del jugador
	int _HpMax;					// Vida maxima

	void InitVariables();		// Inivializamos variables
	void InitSprite();			// Inicializamos sprite
	void InitTexture();			// Inicializamos textura

public:
	Player();	// Constructor
	~Player();

	const sf::Vector2f& GetPosition() const;		// Obtener posicion
	sf::FloatRect GetBounds() const;				// Obtener forma
	const int& GetHp() const;						// Obtener Vida
	const int& GetHpMax() const;					// Obtener vida maxima

	void SetPosition(const sf::Vector2f pos);		// actualizamos posicion
	void SetPosition(const float x, const float y);	// actualizamos posicion
	void SetHp(const int hp);						// añadimos vida
	void LoseHp(const int damage);					// hacemos daño

	void Move(const float x, const float y);		// Movemos al player
	const bool CanAttack();							// Control del ataque

	void UpdateAttack();
	void Update();
	void Render(sf::RenderTarget* target);
};

