#pragma once
#include "RectangleF.h"
#include "CameraManager.h"
#include "Structures.h"
#include "Player.h"

class Game {

public:
	Game() = default;
	Game(bool initialized);
	void Start();
	void InputRead();
	void Update(float deltaTime);
	void Draw();
	bool IsInitialized() const;
private:
	bool initialized;
	Player player;
	Structures structures {20};
};