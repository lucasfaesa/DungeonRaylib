#pragma once

#include "Enemy.h"
#include "Player.h"
#include "raylib.h"
#include "iostream"
#include <vector>

class GameSessionController
{
public:

	GameSessionController(Player* player, std::vector<Enemy*>* enemies);
	//GameSessionController() = default;
	void RestartGame();
	void ReadInput();
	void DrawCanvas();
	void GameWon();
	void GameOver();
	void Update(float deltaTime);

private:
	Player* player{nullptr};
	std::vector<Enemy*>* enemiesVector{nullptr};

	bool _isGameWon{ false };
	bool _isGameOver{ false };

	float gameTime{};
};