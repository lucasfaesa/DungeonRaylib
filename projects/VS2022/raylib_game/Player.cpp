#include "Player.h"
#include <algorithm>
#include "rlgl.h"

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

	lastPositionBeforeBodyCollision = position;
	lastFramePosition = position;
	previousMoveDelta = moveDelta;

	if (moveDelta.z != 0 || moveDelta.x != 0) {
		moveDelta = Vector3Normalize(moveDelta);
		moveDelta.x *= deltaTime * speed;
		moveDelta.z *= deltaTime * speed;
	}

	//gravity = isGrounded ? 0.f : World::gravity;
	gravity = 0;

	HandleJump(deltaTime);

	UpdateCameraPro(camera, moveDelta, mouseDelta, 0.f);

	UpdatePlayerPosition();
	UpdatePlayerRotation();
	UpdateColliderPosition();
	ComputeVelocity(deltaTime);
}

void Player::FixedUpdate(const float fixedDeltaTime)
{
	
	
}


void Player::Draw()
{
	DrawBoundingBox(bodyCollideable.GetCollider(), isCollidingBody ? GREEN : RED);
	DrawBoundingBox(groundCollideable.GetCollider(), isGrounded ? GREEN : YELLOW);
}

void Player::DrawCanvas()
{
	Logger::Log("position x: %.2f, position y: %.2f, position z: %.2f", position.x, position.y, position.z);
	Logger::Log("grounded %i", isGrounded);
	Logger::Log("velocity x: %.2f, velocity y: %.2f, velocity z: %.2f", velocity.x, velocity.y, velocity.z);
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
	fallSpeed = 0;
	moveDelta.y = 0;

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
	moveDelta = { 0, moveDelta.y, 0 };

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
	moveDelta.y = 0;

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

		if (jumpTimer >= jumpDuration) {
			isJumping = false; // End jump after the duration
			std::cout << "max height: " << test << std::endl;
		}
		else {
			float normalizedTime = jumpTimer / jumpDuration;
			float jumpCurve = normalizedTime * (1 - normalizedTime); // Calculate the parabola
			moveDelta.y = jumpForce * deltaTime * jumpCurve;

			if (position.y > test)
				test = position.y;
		}
	}
	else if (!isGrounded) {
		fallSpeed += gravity * gravityRate * deltaTime;

		moveDelta.y -= fallSpeed;

		test = 0;
	}

	//std::cout << fallSpeed << std::endl;

	if (abs(moveDelta.y) > terminalMoveDeltaY) {
		moveDelta.y = (moveDelta.y > 0) ? terminalMoveDeltaY : -terminalMoveDeltaY;
	}

	//std::cout << moveDelta.y << std::endl;

	
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
	bodyCollideable.UpdateBoundingBox(Vector3{position.x - size.x * 0.5f, position.y, position.z - size.z * 0.5f},
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

void Player::ComputeVelocity(float deltaTime)
{
	velocity.x = (position.x - lastFramePosition.x) / deltaTime;
	velocity.y = (position.y - lastFramePosition.y) / deltaTime;
	velocity.z = (position.z - lastFramePosition.z) / deltaTime;
}
