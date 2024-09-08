#pragma once

#ifndef GAME_H
#define GAME_H

#include "Renderer.h"
#include "AudioManager.h"
#include "FontManager.h"

#include<ctime>
#include<vector>
#include<sstream>
#include<map>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class Game {

public:

	Game();											// Constructor

	void Update(float dt);							// Controlador del juego

	void Draw(Renderer& renderer);					// Renderizado del juego

	void InitGameWindow(sf::RenderWindow* window);  // Este metodo se llama para traer la ventana del motor a la clase juego

private:

	sf::RenderWindow* _Window;			// Variable para almacenar la ventana del motor

	FontManager _FontManager;			// Font manager del motor
	AudioManager _AudioManager;			// AudioManager del motor

	std::map<std::string, sf::Texture*> _Textures; // Diccionario donde guardamos las texturas
	std::vector<Bullet*> _Bullets;					// Lista de balas que vamos invocando

	sf::Text _PointText;		// Texto de los puntos
	sf::Text _EndText;			// Texto fin de juego

	sf::Texture _WorldBackGroundTexture;
	sf::Sprite _WorldBackGround;

	unsigned _Points;

	Player* _Player;
	sf::RectangleShape _PlayerHpBar;
	sf::RectangleShape _PlayerHpBarBakcGround;

	float _SpawnTimer;
	float _SpawnTimeMax;
	std::vector<Enemy*> _Enemies;

	void InitVariables();				// Metodo para inicializar variables
	void InitTextures();
	void InitGUI();
	void InitWorld();
	void InitSystems();
	void InitPlayer();
	void InitEnemies();

	void UpdateInput();
	void UpdateGUI();
	void UpdateWorld();
	void UpdateCollision();
	void UpdateBullets();
	void UpdateEnemies();
	void UpdateCombat();

	void RenderGUI();
	void RenderWorld();
};

#endif
