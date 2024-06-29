#pragma once
#include "CameraManager.h"

class Player {

public:
	Player() = default;
	Player(Vector3 pos, Vector3 rot);
	void ReadInput();
	void Update(const float deltaTime);
	void Draw();
private:
	Camera* camera{ nullptr };

	static constexpr float speed = 5.f;
	static constexpr float height = 1.8f;

	Vector3 position;
	Vector3 rotation;

	Vector3 moveDelta{};
	Vector3 mouseDelta{};
	Vector2 mouseSensivity{ 0.05f , 0.05f };
};