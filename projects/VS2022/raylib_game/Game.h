#pragma once
#include "RectangleF.h"
#include "CameraManager.h"
#include "Structures.h"

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
	RectangleF player;

	CameraManager cameraManager { Camera{ 0 } };
	Camera* mainCamera { nullptr };
	Structures structures {20};
};