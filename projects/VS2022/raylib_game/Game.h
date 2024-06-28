#pragma once
#include "RectangleF.h"
#include "CameraManager.h"

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
	RectangleF rectangle;
	CameraManager cameraManager{ Camera{ 0 } };
	Camera* mainCamera{ nullptr };
};