#pragma once
#include "RectangleF.h"
#include "CameraManager.h"
#include "Structures.h"
#include "Player.h"
#include "Logger.h"
#include "LevelGenerator.h"
#include "Helpers.h"
#include "Agent.h"
#include "SeekBehavior.h"
#include "Enemy.h"
#include "CollisionsManager.h"
#include "GameSessionController.h"
#include <vector>
#include <algorithm>

class Game {

public:
	Game() = default;
	Game(bool initialized);
	void Start() const;
	void InputRead() const;
	void Update(float deltaTime) const;
	void FixedUpdateCalculation(float deltaTime);
	void FixedUpdate(float deltaTime) const;
	void OnApplicationClose() const;
	void Draw() const;
	void DrawCanvas() const;
	bool IsInitialized() const;
private:

	void CreateEnemies();

	bool initialized;

	Player* player{nullptr};
	Structures* structures {nullptr};
	LevelGenerator* levelGenerator{nullptr};
	CollisionsManager* collisionsManager{ nullptr };

	GameSessionController* gameSessionController{ nullptr };

	static constexpr int enemiesQuantity{0};

	std::vector<Enemy*>* enemiesVector{ new std::vector<Enemy*>() };

	std::vector<Vector3> enemiesPositions{};

	float fixedTimeStep{ 0.02f }; //50 times a second
	float accumulatedTime{};
};