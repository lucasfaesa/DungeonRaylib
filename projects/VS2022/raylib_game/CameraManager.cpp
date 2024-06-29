#include "CameraManager.h"


CameraManager::CameraManager(Camera cam)
	:camera(cam)
{
    camera.position = Vector3{ 0.0f, 1.8f, 0.f };
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

Camera& CameraManager::GetCamera()
{
    return camera;
}

void CameraManager::CameraLookAt(const Vector3& pos)
{
    camera.target = pos;
}

void CameraManager::ReadInput()
{
	moveDelta = {};

	if (IsKeyDown(KEY_W))
		moveDelta.y += 1.f;
	if (IsKeyDown(KEY_S))
		moveDelta.y -= 1.f;
	if (IsKeyDown(KEY_A))
		moveDelta.x += 1.f;
	if (IsKeyDown(KEY_D))
		moveDelta.x -= 1.f;
}

void CameraManager::Update(const float deltaTime)
{
	camera.target = Vector3{ camera.position.x, camera.position.y, camera.position.z - 20 };

	camera.position.x += speed * Vector2Normalize(moveDelta).x * deltaTime;
	camera.position.z += speed * Vector2Normalize(moveDelta).y * deltaTime;
}

