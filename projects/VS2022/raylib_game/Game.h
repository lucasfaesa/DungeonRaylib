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

class Game {

public:
	Game() = default;
	Game(bool initialized);
	void Start();
	void InputRead();
	void Update(float deltaTime);
	void FixedUpdateCalculation(float deltaTime);
	void FixedUpdate(float deltaTime);
	void OnApplicationClose();
	void Draw();
	void DrawCanvas();
	bool IsInitialized() const;
private:
	void CheckForPlayerCollision();
	bool initialized;
	Player player;
	Structures structures {0};
	LevelGenerator levelGenerator{};

	Enemy* enemy;
	SeekBehavior* seekBehavior;

	float fixedTimeStep{ 0.02f }; //50 times a second
	float accumulatedTime{};
};