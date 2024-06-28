#pragma once
#include "raylib.h"

class CameraManager {
public:
	CameraManager(Camera camera);
	Camera& GetCamera();
	void CameraLookAt(const Vector3& pos);
private:
	Camera camera;
};