#include "CameraManager.h"


CameraManager::CameraManager(Camera cam)
	:mainCamera(cam)
{
	mainCamera.position = Vector3{ 0.0f, 1.8f, 0.f };
	mainCamera.target = Vector3{ 0.0f, 0.0f, 20.0f };
	mainCamera.up = Vector3{ 0.0f, 1.0f, 0.0f };
	mainCamera.fovy = 90.f;
	mainCamera.projection = CAMERA_PERSPECTIVE;
}

Camera& CameraManager::GetCamera()
{
    return mainCamera;
}

void CameraManager::CameraLookAt(const Vector3& pos)
{
	mainCamera.target = pos;
}

void CameraManager::ReadInput()
{
	moveDelta = { 0 };
	mouseDelta = { 0 };

	moveDelta.x = (IsKeyDown(KEY_W) - IsKeyDown(KEY_S));
	moveDelta.y = (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));

	mouseDelta.x += GetMouseDelta().x * mouseSensivity.x;
	mouseDelta.y += GetMouseDelta().y * mouseSensivity.y;
}

void CameraManager::Update(const float deltaTime)
{
	//UpdateCamera(&mainCamera, CAMERA_FIRST_PERSON);
	
	if (moveDelta.x != 0 || moveDelta.y != 0) {
		moveDelta = Vector3Normalize(moveDelta);
		moveDelta.x *= deltaTime * speed;
		moveDelta.y *= deltaTime * speed;
	}
			
	UpdateCameraPro(&mainCamera,moveDelta,mouseDelta, 0.f);

	
	 
	//UpdateCamera(&camera, 1);
	/*camera.target = Vector3{camera.position.x, camera.position.y, camera.position.z - 20};

	camera.position.x += speed * Vector2Normalize(moveDelta).x * deltaTime;
	camera.position.z += speed * Vector2Normalize(moveDelta).y * deltaTime;*/
}

