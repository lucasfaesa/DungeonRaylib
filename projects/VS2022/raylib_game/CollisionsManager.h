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
	void PlayerWithEnvironmentCollisions() const;
	void EnemyRadiusChecks(Enemy* enemy) const;
	void PlayerAttackOnEnemyCheck(Enemy* enemy) const;
	void PlayerWithEnemiesCollision(Enemy* enemy) const;
private:
	

	Player* _player{nullptr};
	std::vector<Enemy*> * _enemiesVector{nullptr};
	Structures* _structures{nullptr};
	LevelGenerator* _levelGenerator{nullptr};
};