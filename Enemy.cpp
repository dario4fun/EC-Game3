#include "Enemy.h"

/// <summary>
/// Funcion que incializa los valores de un enemigo
/// </summary>
void Enemy::InitVariables()
{
	_PointCount = rand() % 8 + 3;
	_Type = 0;
	_HpMax = static_cast<int>(_PointCount);
	_Hp = _HpMax;
	_Damage = _PointCount;
	_Points = _PointCount;
	_Speed = static_cast<float>(_PointCount / 2);
}

/// <summary>
/// MEtod que inicia la forma
/// </summary>
void Enemy::InitShape()
{
	_Shape.setRadius(_PointCount * 3);
	_Shape.setPointCount(_PointCount);
	_Shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

/// <summary>
/// Constructor y posicionamiento
/// </summary>
/// <param name="posX"></param>
/// <param name="posY"></param>
Enemy::Enemy(float posX, float posY)
{

	InitVariables();
	InitShape();

	_Shape.setPosition(posX, posY);

}

/// <summary>
/// Funcion para obtener la forma
/// </summary>
/// <returns></returns>
const sf::FloatRect Enemy::GetBounds() const
{
	return _Shape.getGlobalBounds();
}

/// <summary>
/// Funcion para obtener los puntos
/// </summary>
/// <returns></returns>
const int& Enemy::GetPoints() const
{
	return _PointCount;
}

const int& Enemy::GetDamage() const
{
	return _Damage;
}

/// <summary>
/// Movemos al enemigo
/// </summary>
void Enemy::Update()
{
	_Shape.move(0.f, _Speed);
}


/// <summary>
/// Dibujamos al enemigo
/// </summary>
/// <param name="target"></param>
void Enemy::Render(sf::RenderTarget* target)
{
	target->draw(_Shape);
}
