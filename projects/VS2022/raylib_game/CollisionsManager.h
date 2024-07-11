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
	void ComputeEnvironmentCollisions();

	void CheckCollisionsAgainstEnvironment(Player* player, RectangleF* shape, const BoundingBox& playerBoundingBoxBody,
												const BoundingBox& playerBoundingBoxFeet);
	void CheckCollisionsAgainstEnvironment(Player* player, const BoundingBox& boundingBox, const BoundingBox& playerBoundingBoxBody,
												const BoundingBox& playerBoundingBoxFeet);
	void CheckCollisionsAgainstEnvironment(Enemy* enemy, RectangleF* shape, const BoundingBox& playerBoundingBoxBody,
												const BoundingBox& playerBoundingBoxFeet);
	void CheckCollisionsAgainstEnvironment(Enemy* enemy, const BoundingBox& boundingBox, const BoundingBox& playerBoundingBoxBody,
												const BoundingBox& playerBoundingBoxFeet);

	void EnemyRadiusChecks(Enemy* enemy) const;
	void PlayerAttackOnEnemyCheck(Enemy* enemy) const;
	void PlayerWithEnemiesCollision(Enemy* enemy);
	void CheckEnemyWithEnemiesCollision(Enemy* thisEnemy, std::vector<Enemy*>& enemiesInCollision);
	void ProcessEnemyWithEnemyCollision(std::vector<Enemy*>& enemiesInCollision);
private:
	

	Player* _player{nullptr};
	std::vector<Enemy*> * _enemiesVector{nullptr};
	Structures* _structures{nullptr};
	LevelGenerator* _levelGenerator{nullptr};

	bool _collisionOnPlayerFeet {true};
	bool _collisionOnEnemyFeet {true};
};