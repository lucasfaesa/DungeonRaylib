#pragma once
#include "raylib.h"
#include "raymath.h"

class CameraManager {
public:
	CameraManager(Camera camera);
	Camera& GetCamera();
	void CameraLookAt(const Vector3& pos);
	void ReadInput();
	void Update(const float deltaTime);
private:
	Camera camera;
	static constexpr float speed = 15.f;
	Vector2 moveDelta{};
};