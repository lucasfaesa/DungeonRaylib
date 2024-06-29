#pragma once
#include "raylib.h"
#include "raymath.h"
#include "rcamera.h"

class CameraManager {
public:
    static Camera& GetPlayerCamera();
    static void ReadInput();
    static void Update(const float deltaTime);
private:
    static Camera playerCamera;
};