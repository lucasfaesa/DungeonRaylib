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

	void UpdatePlayerRotation();
	void UpdatePlayerPosition();

	Camera* camera{ nullptr };

	static constexpr float speed = 5.f;
	static constexpr Vector3 size{ 0.8f, 1.8f, 0.8f };
	static constexpr float jumpForce = 1.f;
	static constexpr float jumpDuration = 0.4f;

	Vector3 position{ };
	Vector3 rotation{ };

	Vector3 moveDelta{};
	Vector3 mouseDelta{};
	Vector2 mouseSensivity{ 0.05f , 0.05f };

	BoundingBox boxCollider;

	float gravity = World::gravity;

	bool isGrounded{false};
	bool canJump{ false };
	bool isJumping{ false };
	float jumpTimer{};
};