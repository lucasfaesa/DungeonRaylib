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

	void Update(float deltaTime);

private:
	void CheckCollisions();
	void PlayerWithEnvironmentCollisions();
	void EnemyRadiusChecks(Enemy* enemy) const;
	void PlayerAttackOnEnemyCheck(Enemy* enemy) const;
	void PlayerWithEnemiesCollision(Enemy* enemy);
private:
	

	Player* _player{nullptr};
	std::vector<Enemy*> * _enemiesVector{nullptr};
	Structures* _structures{nullptr};
	LevelGenerator* _levelGenerator{nullptr};

	bool _collisionOnPlayerFeet {true};
};