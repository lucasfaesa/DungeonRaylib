#include "Player.h"

Player::Player(Vector3 pos, Vector3 rot):
	position(pos), rotation(rot)
{
	position.y = height * 0.5f;
	camera = &CameraManager::GetPlayerCamera();
}

void Player::ReadInput()
{
	moveDelta = { 0 };
	mouseDelta = { 0 };

	moveDelta.x = (IsKeyDown(KEY_W) - IsKeyDown(KEY_S));
	moveDelta.y = (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));

	mouseDelta.x += GetMouseDelta().x * mouseSensivity.x;
	mouseDelta.y += GetMouseDelta().y * mouseSensivity.y;
}

void Player::Update(const float deltaTime)
{
	if (moveDelta.x != 0 || moveDelta.y != 0) {
		moveDelta = Vector3Normalize(moveDelta);
		moveDelta.x *= deltaTime * speed;
		moveDelta.y *= deltaTime * speed;
	}

	UpdateCameraPro(camera, moveDelta, mouseDelta, 0.f);
}

void Player::Draw()
{
}
