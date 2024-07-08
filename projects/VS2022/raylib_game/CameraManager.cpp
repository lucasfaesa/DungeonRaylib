#include "CameraManager.h"


// Define static member variable
Camera CameraManager::playerCamera = Camera{
    Vector3{ 50.f, 1.8f, 77.f },  // position
    Vector3{ 0.0f, 0.0f, 20.0f }, // target
    Vector3{ 0.0f, 1.0f, 0.0f },  // up
    90.f,                        // fovy
    CAMERA_PERSPECTIVE           // projection
};

Camera& CameraManager::GetPlayerCamera()
{
    return playerCamera;
}

void CameraManager::ReadInput()
{
    // Implement input reading for camera controls
}

void CameraManager::Update(const float deltaTime)
{
    // Implement camera update logic
}
