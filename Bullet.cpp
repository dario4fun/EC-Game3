#include "Bullet.h"

/// <summary>
/// Constructor de la bala y inicializacion de variables
/// </summary>
/// <param name="texture"> Textura de la bala </param>
/// <param name="posX"> Posicion en X </param>
/// <param name="posY"> Posición en Y </param>
/// <param name="dirX"> Direccion en X </param>
/// <param name="dirY"> Direccion en Y </param>
/// <param name="movementSpeed"> Velocidad de movimiento</param>
Bullet::Bullet(sf::Texture* texture, float posX, float posY, float dirX, float dirY, float movementSpeed)
{
	_Shape.setTexture(*texture);
	_Shape.setPosition(posX, posY);
	_Shape.setScale(0.01f, 0.01f);
	_Direction.x = dirX;
	_Direction.y = dirY;
	_MovementSpeed = movementSpeed;
}


/// <summary>
/// Funcion que devuelve la forma
/// </summary>
/// <returns></returns>
const sf::FloatRect Bullet::GetBounds() const
{
	return this->_Shape.getGlobalBounds();
}

/// <summary>
/// Movemos la bala en la direccion y velodidad que le pasemos
/// </summary>
void Bullet::Update()
{
	_Shape.move(_MovementSpeed * _Direction);
}

/// <summary>
/// Dibujamos la bala
/// </summary>
/// <param name="target"></param>
void Bullet::Render(sf::RenderTarget* target)
{
	target->draw(_Shape);
}
