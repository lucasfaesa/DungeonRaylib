#pragma once
#include "CameraManager.h"
#include "Structures.h"
#include "Player.h"
#include "LevelGenerator.h"
#include "Enemy.h"
#include "CollisionsManager.h"
#include "GameSessionController.h"
#include "Pickable.h"
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
	void CreatePotions();

	bool initialized;

	Player* player{nullptr};
	Structures* structures {nullptr};
	LevelGenerator* levelGenerator{nullptr};
	CollisionsManager* collisionsManager{ nullptr };

	std::vector<Pickable*>* potionsVector{ new std::vector<Pickable*>() };

	GameSessionController* gameSessionController{ nullptr };

	static constexpr int enemiesQuantity{0};

	std::vector<Enemy*>* enemiesVector{ new std::vector<Enemy*>() };

	std::vector<Vector3> enemiesPositions{};

	Pickable* keyPickable{ nullptr };

	Texture2D potionTexture = LoadTexture("../resources/pickables/Potion.png");
	Texture2D keyTexture = LoadTexture("../resources/pickables/Key.png");

	float fixedTimeStep{ 0.02f }; //50 times a second
	float accumulatedTime{};
};