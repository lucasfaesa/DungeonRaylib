#pragma once
#include "CameraManager.h"
#include "World.h"

class Player {

public:
	Player() = default;
	Player(Vector3 pos, Vector3 rot);
	void ReadInput();
	void Update(const float deltaTime);
	void Draw();
private:

	void InputMovement();
	void InputLook();
	void InputJump();

	void HandleJump(float deltaTime);

	const Vector3 UpdatePlayerRotation();

	Camera* camera{ nullptr };

	static constexpr float speed = 5.f;
	static constexpr float height = 1.8f;
	static constexpr float jumpForce = 1.f;
	static constexpr float jumpDuration = 0.4f;

	Vector3* position{ nullptr };
	Vector3 rotation{ };

	Vector3 moveDelta{};
	Vector3 mouseDelta{};
	Vector2 mouseSensivity{ 0.05f , 0.05f };

	float gravity = World::gravity;

	bool isGrounded{false};
	bool canJump{ false };
	bool isJumping; // Flag to track jump state
	float jumpTimer;
};