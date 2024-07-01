#include "Player.h"
#include <algorithm>

Player::Player(Vector3 pos, Vector3 rot)
{
	camera = &CameraManager::GetPlayerCamera();

	//because de UpdateCameraPro handles the position
	position = camera->position;
	//zero Y on the foot
	position.y = 0.f;	
}

void Player::ReadInput()
{
	InputMovement();
	InputLook();
	InputJump();
}

void Player::Update(const float deltaTime)
{
	if (moveDelta.z != 0 || moveDelta.x != 0) {
		moveDelta = Vector3Normalize(moveDelta);
		moveDelta.x *= deltaTime * speed;
		moveDelta.z *= deltaTime * speed;
	}

	gravity = isGrounded ? 0.f : World::gravity;

	HandleJump(deltaTime);

	#pragma region debug
		DrawText(TextFormat("%.2f positionX", position.x), 40, 40, 20, GREEN);
		DrawText(TextFormat("%.2f positionY", position.y), 40, 60, 20, GREEN);
		DrawText(TextFormat("%.2f positionZ", position.z), 40, 80, 20, GREEN);

		DrawText(TextFormat("%.2f rotationX", rotation.x), 40, 100, 20, GREEN);
		DrawText(TextFormat("%.2f rotationY", rotation.y), 40, 120, 20, GREEN);
		DrawText(TextFormat("%.2f rotationZ", rotation.z), 40, 140, 20, GREEN);
	#pragma endregion

	UpdateCameraPro(camera, moveDelta, mouseDelta, 0.f);

	//TODO remove this later when implemented collision
	if (position.y <= 0 && !isGrounded && !isJumping) {
		isGrounded = true;
		canJump = true;
		isJumping = false;
		jumpTimer = 0;
		camera->position.y = size.y;
	}

	UpdatePlayerPosition();
	UpdatePlayerRotation();
}


void Player::Draw()
{
	Vector3 min{ position.x - size.x * 0.5f, position.y, position.z - size.z * 0.5f };
	Vector3 max{ position.x + size.x * 0.5f, position.y + size.y, position.z + size.z * 0.5f };
	boxCollider = BoundingBox{ min , max };

	DrawBoundingBox(boxCollider, RED);
}

void Player::InputMovement()
{
	moveDelta = { 0, 0, moveDelta.z };

	moveDelta.z = (IsKeyDown(KEY_W) - IsKeyDown(KEY_S));
	moveDelta.x = (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));
}

void Player::InputLook()
{
	mouseDelta = { 0 };

	mouseDelta.x += GetMouseDelta().x * mouseSensivity.x;
	mouseDelta.y += GetMouseDelta().y * mouseSensivity.y;
}

void Player::InputJump()
{
	if (IsKeyPressed(KEY_SPACE) && canJump) {
		moveDelta.y = jumpForce;
		isGrounded = false;
		canJump = false;
		isJumping = true;
	}
}

void Player::HandleJump(float deltaTime)
{
	if (isJumping) {
		jumpTimer += deltaTime;

		// Apply jump force based on timer (parabolic curve)
		//moveDelta.y = jumpForce * 0.5f * (-jumpTimer * jumpTimer + jumpTimer);

		float normalizedTime = jumpTimer / jumpDuration;
		moveDelta.y = jumpForce * 0.5f * (-normalizedTime * normalizedTime + normalizedTime);

		if (jumpTimer > jumpDuration) {
			isJumping = false; // End jump after the duration
		}
	}
	else {
		moveDelta.y -= (gravity)*deltaTime;
	}
}

void Player::UpdatePlayerRotation()
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
}

void Player::UpdatePlayerPosition()
{
	position = camera->position;
	position.y -= size.y;
}
