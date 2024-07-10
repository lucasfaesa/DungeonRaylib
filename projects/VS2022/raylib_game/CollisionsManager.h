#pragma once

#include "Player.h"
#include "Enemy.h"
#include "Structures.h"
#include "LevelGenerator.h"
#include <vector>

class CollisionsManager {
public:

	CollisionsManager() = default;
	CollisionsManager(Player* player, std::vector<Enemy*>* enemiesVector, Structures* structures, LevelGenerator* levelGenerator);

	void Update(float deltaTime) const;

private:
	void CheckCollisions() const;

private:
	bool checkPlayerCollisions{ true };
	bool checkEnemyCollisions{ true };
	bool checkEnvironmentCollisions{ true };

	Player* _player{nullptr};
	std::vector<Enemy*> * _enemiesVector{nullptr};
	Structures* _structures{nullptr};
	LevelGenerator* _levelGenerator{nullptr};
};