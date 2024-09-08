#include "Player.h"

/// <summary>
/// Inicializamos variables del player
/// </summary>
void Player::InitVariables()
{
	_MovementSpeed = 7.f;
	_AttackCooldownMax = 10.f;
	_AttackCooldown = _AttackCooldownMax;

	_HpMax = 100;
	_Hp = _HpMax;
}

/// <summary>
/// Inicializamos sprite y textura del player
/// </summary>
void Player::InitSprite()
{
	_Sprite.setTexture(_Texture);

	_Sprite.scale(.1f, .1f);
}

void Player::InitTexture()
{
	if (!_Texture.loadFromFile("./Resources/ship.png")) {

		std::cout << "Error al cargar la textura ship.png!" << " \n";
	}
}

Player::Player()
{
	InitVariables();
	InitTexture();
	InitSprite();
}

Player::~Player()
{
}

const sf::Vector2f& Player::GetPosition() const
{
	return _Sprite.getPosition();
}

sf::FloatRect Player::GetBounds() const
{
	return _Sprite.getGlobalBounds();
}

const int& Player::GetHp() const
{
	return _Hp;
}

const int& Player::GetHpMax() const
{
	return _HpMax;
}

void Player::SetPosition(const sf::Vector2f pos)
{
	_Sprite.setPosition(pos);
}

void Player::SetPosition(const float x, const float y)
{
	_Sprite.setPosition(x, y);
}

void Player::SetHp(const int hp)
{
	_Hp = hp;
}

void Player::LoseHp(const int damage)
{
	_Hp -= damage;
	if (_Hp <= 0) _Hp = 0;
}

void Player::Move(const float x, const float y)
{
	_Sprite.move(_MovementSpeed * x, _MovementSpeed * y);
}

const bool Player::CanAttack()
{
	if (_AttackCooldown >= _AttackCooldownMax) {

		_AttackCooldown = 0.f;
		return true;
	}

	return false;
}

void Player::UpdateAttack()
{
	if (_AttackCooldown < _AttackCooldownMax) {

		_AttackCooldown += .5f;
	}
}

void Player::Update()
{
	UpdateAttack();
}

void Player::Render(sf::RenderTarget* target)
{
	target->draw(_Sprite);
}
