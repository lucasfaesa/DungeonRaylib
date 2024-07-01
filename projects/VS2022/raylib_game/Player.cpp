#include "Player.h"
#include <algorithm>

Player::Player(Vector3 pos, Vector3 rot)
{
	camera = &CameraManager::GetPlayerCamera();

	Vector3 bodyMin{ position.x - size.x * 0.5f, position.y, position.z - size.z * 0.5f};
	Vector3 bodyMax{ position.x + size.x * 0.5f, position.y + size.y, position.z + size.z * 0.5f };

	Vector3 groundMin{ position.x - (size.x - 0.03f) * 0.5f, position.y - 0.1f, position.z - (size.z - 0.03f) * 0.5f };
	Vector3 groundMax{ position.x + (size.x - 0.03f) * 0.5f, position.y, position.z + (size.z - 0.03f) * 0.5f };

	bodyCollideable = Collideable{ BoundingBox{ bodyMin , bodyMax } , Layers::Layer::PLAYER };
	groundCollideable = Collideable{ BoundingBox{ groundMin , groundMax } , Layers::Layer::DEFAULT };

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
	isCollidingBody = false;
	//isGrounded = false;

	lastPositionBeforeBodyCollision = position;
	lastPositionBeforeFootCollision = position.y;

	if (moveDelta.z != 0 || moveDelta.x != 0) {
		moveDelta = Vector3Normalize(moveDelta);
		moveDelta.x *= deltaTime * speed;
		moveDelta.z *= deltaTime * speed;
	}

	gravity = isGrounded ? 0.f : World::gravity;
	//gravity = 0;

	HandleJump(deltaTime);

	#pragma region debug
		DrawText(TextFormat("%.2f positionX", position.x), 40, 40, 20, GREEN);
		DrawText(TextFormat("%.2f positionY", position.y), 40, 60, 20, GREEN);
		DrawText(TextFormat("%.2f positionZ", position.z), 40, 80, 20, GREEN);

		DrawText(TextFormat("grounded %i", isGrounded), 40, 100, 20, GREEN);

		//DrawText(TextFormat("%.2f rotationX", rotation.x), 40, 100, 20, GREEN);
		//DrawText(TextFormat("%.2f rotationY", rotation.y), 40, 120, 20, GREEN);
		//DrawText(TextFormat("%.2f rotationZ", rotation.z), 40, 140, 20, GREEN);
	#pragma endregion

	UpdateCameraPro(camera, moveDelta, mouseDelta, 0.f);

	//TODO remove this later when implemented collision
	/*if (position.y <= 0 && !isGrounded && !isJumping) {
		isGrounded = true;
		canJump = true;
		isJumping = false;
		jumpTimer = 0;
		camera->position.y = size.y;
	}*/

	UpdatePlayerPosition();
	UpdatePlayerRotation();
	UpdateColliderPosition();
}


void Player::Draw()
{
	DrawBoundingBox(bodyCollideable.GetCollider(), isCollidingBody ? GREEN : RED);
	DrawBoundingBox(groundCollideable.GetCollider(), isGrounded ? GREEN : YELLOW);
}

void Player::OnCollisionOnBody()
{
	isCollidingBody = true;
	
	ForcePositionXZChange();
}

void Player::OnCollisionOnFoot(RectangleF& rect)
{
	if (isJumping) return;

	isGrounded = true;
	canJump = true;
	isJumping = false;
	jumpTimer = 0;

	float topYPos = rect.GetPosition().y + rect.GetSize().y * 0.5f;
	ForcePositionYChange(topYPos);
}

void Player::LeftCollisionOnFoot()
{
	if (isJumping) return;

	isGrounded = false;
	canJump = false;
	isJumping = false;
}

Collideable& Player::GetBodyCollideable()
{
	return bodyCollideable;
}

Collideable& Player::GetFootCollideable()
{
	return groundCollideable;
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
	if (IsKeyPressed(KEY_SPACE) && canJump && !isJumping) {
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

void Player::UpdateColliderPosition()
{
	bodyCollideable.UpdateBoundingBox(Vector3{ position.x - size.x * 0.5f, position.y, position.z - size.z * 0.5f },
									Vector3{ position.x + size.x * 0.5f, position.y + size.y, position.z + size.z * 0.5f });

	groundCollideable.UpdateBoundingBox(Vector3{ position.x - (size.x - 0.03f) * 0.5f, position.y - 0.1f, position.z - (size.z - 0.03f) * 0.5f },
										Vector3{ position.x + (size.x - 0.03f) * 0.5f, position.y, position.z + (size.z - 0.03f) * 0.5f });
}

void Player::ForcePositionXZChange()
{
	camera->position.x = lastPositionBeforeBodyCollision.x;
	camera->position.z = lastPositionBeforeBodyCollision.z;

	UpdatePlayerPosition();
	UpdateColliderPosition();
}

void Player::ForcePositionYChange(float topYPos)
{
	//									    offset to not make the body collider hit the ground//strctures from above
	camera->position.y = topYPos + size.y + 0.01f;

	UpdatePlayerPosition();
	UpdateColliderPosition();
}
