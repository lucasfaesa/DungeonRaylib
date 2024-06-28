#include "CameraManager.h"


CameraManager::CameraManager(Camera cam)
	:camera(cam)
{
    camera.position = Vector3{ 0.0f, 30.f, 30.f };
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

