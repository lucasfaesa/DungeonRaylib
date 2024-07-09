#pragma once
#include "CameraManager.h"
#include "World.h"
#include "Layers.h"
#include "Collideable.h"
#include "RectangleF.h"
#include "Logger.h"

class Player {

public:
	Player() = default;
	Player(Vector3 pos, Vector3 rot);
	void ReadInput();
	void Update(const float deltaTime);
	void FixedUpdate(const float fixedDeltaTime);
	void Draw();
	void DrawCanvas();
	void OnCollisionOnBody();
	void OnCollisionOnFoot(RectangleF& collideable);
	void OnCollisionOnFoot(float topYPos);
	void LeftCollisionOnFoot();

	void TakeDamage(int value);

	Collideable& GetBodyCollideable();
	Collideable& GetFootCollideable();
	Vector3& GetPlayerPosition();

private:

	void InputMovement();
	void InputLook();
	void InputJump();

	void HandleJump(float deltaTime);

	void UpdatePlayerRotation();
	void UpdatePlayerPosition();
	void UpdateColliderPosition();
	void ForcePositionXZChange();
	void ForcePositionYChange(float topYPos);
	void ComputeVelocity(float deltaTime);

	Camera* camera{ nullptr };

	//static constexpr Layers::Layer layer = Layers::Layer::PLAYER;

	static constexpr float speed = 10.f;
	static constexpr Vector3 size{ 0.5f, 1.8f, 0.5f };
	static constexpr float jumpForce = 30.f;
	static constexpr float jumpDuration = 0.4f;

	Vector3 position{ };
	Vector3 rotation{ };
	Vector3 velocity{ };

	Vector3 lastPositionBeforeBodyCollision;
	Vector3 lastFramePosition{ };

	Vector3 moveDelta{};
	Vector3 previousMoveDelta{};
	Vector3 mouseDelta{};
	Vector2 mouseSensivity{ 0.05f , 0.05f };

	Collideable bodyCollideable;
	Collideable groundCollideable;

	float gravity = World::gravity;

	bool isGrounded{false};
	bool canJump{ false };
	bool isJumping{ false };
	float jumpTimer{};
	float terminalMoveDeltaY{ 0.3f }; //or 0.125f
	float fallSpeed{};
	float gravityRate{ 0.05f };

	float test{};

	int playerHealth = 100;

	bool isCollidingBody;
};