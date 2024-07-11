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
#include <vector>

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

	bool initialized;

	Player* player{nullptr};
	Structures* structures {nullptr};
	LevelGenerator* levelGenerator{nullptr};
	CollisionsManager* collisionsManager{ nullptr };

	static constexpr int enemiesQuantity{2};

	std::vector<Enemy*>* enemiesVector{ new std::vector<Enemy*>() };

	float fixedTimeStep{ 0.02f }; //50 times a second
	float accumulatedTime{};
};