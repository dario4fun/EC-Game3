#include "Game.h"

/// <summary>
/// Almacenamos la ventana del motor en la clase por si la necesitamos para algo
/// </summary>
/// <param name="window"></param>
void Game::InitGameWindow(sf::RenderWindow* window)
{
	_Window = window;

	InitPlayer();
	InitGUI();
}

/// <summary>
/// En esta funcion se cargan las variables de inicio del juego
/// </summary>
void Game::InitVariables()
{
	_FontManager.LoadFonts();

	_AudioManager.LoadSound("shot", "./Resources/shot.wav");
	_AudioManager.LoadMusic("./Resources/music.mp3");
}

// Constructor donde se inizializa el juego
Game::Game()
{

	InitVariables();
	InitTextures();
	InitWorld();
	InitSystems();
	InitEnemies();

	_AudioManager.PlayMusic();
}


void Game::InitPlayer()
{
	_Player = new Player();
	_Player->SetPosition(sf::Vector2f((_Window->getSize().x / 2) - _Player->GetBounds().width, (_Window->getSize().y / 2) + _Player->GetBounds().height));
}

void Game::InitEnemies()
{

	_SpawnTimeMax = 50.f;;
	_SpawnTimer = _SpawnTimeMax;
}

void Game::InitTextures()
{
	_Textures["BULLET"] = new sf::Texture();
	_Textures["BULLET"]->loadFromFile("./Resources/bullet.png");
}

void Game::InitGUI()
{

	_PointText.setFont(_FontManager.GetFont("Choco"));
	_PointText.setCharacterSize(24);
	_PointText.setFillColor(sf::Color::White);
	_PointText.setPosition(sf::Vector2f(650.f, 20.f));

	_EndText.setFont(_FontManager.GetFont("Choco"));
	_EndText.setCharacterSize(48);
	_EndText.setFillColor(sf::Color::Red);
	_EndText.setPosition(sf::Vector2f(
		_Window->getSize().x / 2.f - _EndText.getGlobalBounds().width / 2.f,
		_Window->getSize().y / 2.f - _EndText.getGlobalBounds().height / 2.f
	));
	_EndText.setString("GAME OVER!");

	_PlayerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	_PlayerHpBar.setFillColor(sf::Color::Red);
	_PlayerHpBar.setPosition(50.f, 20.f);

	_PlayerHpBarBakcGround = _PlayerHpBar;
	_PlayerHpBarBakcGround.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::InitWorld()
{

	if (!_WorldBackGroundTexture.loadFromFile("./Resources/bg.png")) {

		std::cout << "Error al cargar la imagen del background" << " \n";
	}

	_WorldBackGround.setTexture(_WorldBackGroundTexture);
}

void Game::InitSystems()
{
	_Points = 0;
}

void Game::UpdateInput()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _Player->Move(-1.f, 0.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _Player->Move(1.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) _Player->Move(0.f, -1.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) _Player->Move(0.f, 1.f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _Player->CanAttack()) {

		_Bullets.push_back(new Bullet(_Textures["BULLET"],
			_Player->GetPosition().x + _Player->GetBounds().width / 2.f,
			_Player->GetPosition().y,
			0.f, -1.f, 5.f));

		_AudioManager.PlaySound("shot");
	}

}

void Game::UpdateGUI()
{
	std::stringstream ss;

	ss << " Points: " << _Points << " \n";

	_PointText.setString(ss.str());

	float _PlayerPercertBar = static_cast<float>(_Player->GetHp()) / _Player->GetHpMax();
	_PlayerHpBar.setSize(sf::Vector2f(300.f * _PlayerPercertBar, _PlayerHpBar.getSize().y));
}

void Game::UpdateWorld()
{
}

void Game::UpdateCollision()
{

	if (_Player->GetBounds().left < 0.f) _Player->SetPosition(0.f, _Player->GetBounds().top);
	else if (_Player->GetBounds().left + _Player->GetBounds().width > _Window->getSize().x) _Player->SetPosition(_Window->getSize().x - _Player->GetBounds().width, _Player->GetBounds().top);

	if (_Player->GetBounds().top < 0.f) _Player->SetPosition(_Player->GetBounds().left, 0.f);
	else if (_Player->GetBounds().top + _Player->GetBounds().height > _Window->getSize().y) _Player->SetPosition(_Player->GetBounds().left, _Window->getSize().y - _Player->GetBounds().height);
}

void Game::UpdateBullets()
{

	unsigned _Count = 0;

	for (auto* bullet : _Bullets) {

		bullet->Update();

		if (bullet->GetBounds().top + bullet->GetBounds().height < 0.f) {

			delete _Bullets.at(_Count);
			_Bullets.erase(_Bullets.begin() + _Count);
		}

		++_Count;
	}
}

void Game::UpdateEnemies()
{

	_SpawnTimer += 0.5f;

	if (_SpawnTimer >= _SpawnTimeMax) {

		_Enemies.push_back(new Enemy(rand() % _Window->getSize().x - 20.f, -100.f));
		_SpawnTimer = 0.f;
	}

	unsigned _Count = 0;

	for (auto* enemy : _Enemies) {

		enemy->Update();

		if (enemy->GetBounds().top > _Window->getSize().y) {

			delete _Enemies.at(_Count);
			_Enemies.erase(_Enemies.begin() + _Count);

		}
		else if (enemy->GetBounds().intersects(_Player->GetBounds())) {

			_Player->LoseHp(_Enemies.at(_Count)->GetDamage());
			delete _Enemies.at(_Count);
			_Enemies.erase(_Enemies.begin() + _Count);

		}

		++_Count;
	}

}

void Game::UpdateCombat()
{

	for (int i = 0; i < _Enemies.size(); ++i) {

		bool _EnemyRemoved = false;

		for (size_t b = 0; b < _Bullets.size() && !_EnemyRemoved; b++) {

			if (_Enemies[i]->GetBounds().intersects(_Bullets[b]->GetBounds())) {

				_Points += _Enemies[i]->GetPoints();

				delete _Enemies[i];
				_Enemies.erase(_Enemies.begin() + i);

				delete _Bullets[b];
				_Bullets.erase(_Bullets.begin() + b);

				_EnemyRemoved = true;
			}
		}
	}
}

/// <summary>
/// Funcion que se encarga de la logica del juego
/// </summary>
/// <param name="dt"> delta time </param>
void Game::Update(float dt)
{
	UpdateInput();

	_Player->Update();

	UpdateCollision();

	UpdateBullets();

	UpdateEnemies();

	UpdateCombat();

	UpdateGUI();

	UpdateWorld();
}

void Game::RenderGUI()
{
	_Window->draw(_PointText);
	_Window->draw(_PlayerHpBarBakcGround);
	_Window->draw(_PlayerHpBar);

	if (_Player->GetHp() <= 0) {

		_Window->draw(_EndText);
	}
}

void Game::RenderWorld()
{
	_Window->draw(_WorldBackGround);
}


/// <summary>
/// Funcion que se encarga de dibujar todos los elementos del juego
/// </summary>
/// <param name="renderer"></param>
void Game::Draw(Renderer& renderer)
{
	this->RenderWorld();

	_Player->Render(_Window);

	for (auto* bullet : _Bullets) {

		bullet->Render(_Window);
	}

	for (auto* enemy : _Enemies) {

		enemy->Render(_Window);
	}

	RenderGUI();
}