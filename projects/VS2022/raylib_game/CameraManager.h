#pragma once
#include "raylib.h"
#include "raymath.h"
#include "rcamera.h"

class CameraManager {
public:
	CameraManager(Camera camera);
	Camera& GetCamera();
	void CameraLookAt(const Vector3& pos);
	void ReadInput();
	void Update(const float deltaTime);
private:
	Camera mainCamera;
	static constexpr float speed = 5.f;
	Vector3 moveDelta{};
	Vector3 mouseDelta{};
	Vector2 mouseSensivity{ 0.05f , 0.05f};
};