#include "Player.h"
#include <algorithm>

Player::Player(Vector3 pos, Vector3 rot)
{
	camera = &CameraManager::GetPlayerCamera();

	//because de UpdateCameraPro handles the position
	position = &camera->position;
}

void Player::ReadInput()
{
	HandleMovement();
	HandleLook();
	HandleJump();
}

void Player::Update(const float deltaTime)
{
	if (moveDelta.z != 0 || moveDelta.x != 0) {
		moveDelta = Vector3Normalize(moveDelta);
		moveDelta.x *= deltaTime * speed;
		moveDelta.z *= deltaTime * speed;
	}

	gravity = isGrounded ? 0.f : World::gravity;

	//moveDelta.y -= gravity * deltaTime;

	if (isJumping) {
		jumpTimer += deltaTime;

		// Apply jump force based on timer (parabolic curve)
		moveDelta.y = jumpForce * (-jumpTimer * jumpTimer + jumpTimer);
	}
	else {
		moveDelta.y -= gravity * deltaTime;
	}

	

	DrawText(TextFormat("%.2f positionX", position->x), 40, 40, 20, GREEN);
	DrawText(TextFormat("%.2f positionY", position->y), 40, 60, 20, GREEN);
	DrawText(TextFormat("%.2f positionZ", position->z), 40, 80, 20, GREEN);

	DrawText(TextFormat("%.2f rotationX", rotation.x), 40, 100, 20, GREEN);
	DrawText(TextFormat("%.2f rotationY", rotation.y), 40, 120, 20, GREEN);
	DrawText(TextFormat("%.2f rotationZ", rotation.z), 40, 140, 20, GREEN);

	UpdateCameraPro(camera, moveDelta, mouseDelta, 0.f);


	if (position->y <= height * 0.5f && !isGrounded) {
		isGrounded = true;
		canJump = true;
		isJumping = false;
		jumpTimer = 0;
		position->y = height * 0.5f;
	}
	UpdatePlayerRotation();
}


void Player::Draw()
{
}

void Player::HandleMovement()
{
	moveDelta = { 0, 0, moveDelta.z };

	moveDelta.z = (IsKeyDown(KEY_W) - IsKeyDown(KEY_S));
	moveDelta.x = (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));
}

void Player::HandleLook()
{
	mouseDelta = { 0 };

	mouseDelta.x += GetMouseDelta().x * mouseSensivity.x;
	mouseDelta.y += GetMouseDelta().y * mouseSensivity.y;
}

void Player::HandleJump()
{
	if (IsKeyDown(KEY_SPACE) && canJump) {
		moveDelta.y = jumpForce;
		isGrounded = false;
		canJump = false;
		isJumping = true;
	}
}

const Vector3 Player::UpdatePlayerRotation()
{
	// Get the forward vector
	Vector3 forward = GetCameraForward(camera);

	// Yaw (rotation around Y-axis)
	rotation.y = atan2f(forward.x, forward.z) * RAD2DEG;

	// Pitch (rotation around X-axis)
	rotation.x = asinf(forward.y) * RAD2DEG;

	// Roll (rotation around Z-axis)
	Vector3 right = GetCameraRight(camera);
	rotation.z = atan2f(right.y, right.x) * RAD2DEG;

	return rotation;
	
}
