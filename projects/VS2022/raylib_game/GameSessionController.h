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

private:
	bool isGameOver{false};
	Player* player{nullptr};
	std::vector<Enemy*>* enemiesVector{nullptr};
};