#pragma once
#include "CameraManager.h"
#include "World.h"
#include "Layers.h"
#include "Collideable.h"
#include "RectangleF.h"
#include "Logger.h"
#include "Damageable.h"
#include <utility>

class Player : public Damageable{

public:
	Player() = default;
	Player(Vector3 pos);
	void ReadInput();
	void Update(const float deltaTime);
	void FixedUpdate(const float fixedDeltaTime);
	void Draw();
	void DrawCanvas();
	void OnCollisionOnBody();
	void OnCollisionOnFoot(float topYPos);
	void LeftCollisionOnFoot();

	std::pair<float, float> GetAttackRangeAndRadius() const;

	void TakeDamage(int value) override;

	Collideable& GetBodyCollideable();
	Collideable& GetFootCollideable();
	Vector3& GetPlayerPosition();
	Camera& GetPlayerCamera() const;

	bool IsAttacking() const;
	void PlayerInAttackRange(bool status);
	int GetAttackDamage() const;
	bool GetIsDefending() const;

	void OnGameRestarted();

	void RegenLife(int value);

	void AddKey();
private:

	void InputMovement();
	void InputLook();
	void InputJump();
	void InputAttack();
	void InputDefense();

	void HandleJump(float deltaTime);

	void UpdatePlayerRotation();
	void UpdatePlayerPosition();
	void UpdateColliderPosition();
	void ForcePositionXZChange();
	void ForcePositionYChange(float topYPos);
	void ComputeVelocity(float deltaTime);
	void CountAnimationFrames(float deltaTime);

	void ChangeToSwordAttackSpriteSheet();
	void ChangeToSwordIdleSpriteSheet();

	void AttackInitiated();
	void AttackEnded();

	void DefenseInitiated();
	void DefenseEnded();

	void ChangeToShieldIdleSpriteSheet();
	void ChangeToShieldUpSpriteSheet();

private:
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

	bool isCollidingBody;

	static constexpr int attackTotalFrames{ 5 };
	static constexpr int idleTotalFrames{ 1 };

	Texture2D sword_idle_texture = LoadTexture("../resources/player/sword_idle2.png");
	Texture2D sword_attack_texture = LoadTexture("../resources/player/sword_attack.png");
	Texture2D shield_idle_texture = LoadTexture("../resources/player/shield_idle.png");
	Texture2D shield_up_texture = LoadTexture("../resources/player/shield_up.png");
	Texture2D HUD_shield_impact_feedback = LoadTexture("../resources/player/HUD_shield_impact_feedback.png");
	Texture2D HUD_player_damaged_feedback = LoadTexture("../resources/player/HUD_player_damaged_feedback.png");
	Texture2D Key_Texture = LoadTexture("../resources/pickables/Key.png");

	Rectangle frameRec = { 0.0f, 0.0f, static_cast<float>(sword_idle_texture.width) / idleTotalFrames, static_cast<float>(sword_idle_texture.height) };

	Rectangle keyFrameRec = { 0.f, 0.f, 300.f,300.f };

	int currentFrame{ 0 };
	int framesCounter{ 0 };
	
	int attackFramesSpeed{ 12 };
	int idleFramesSpeed{ 1 };

	int currentAnimationFrameSpeed{ 1 };
	int currentAnimationTotalFrames{ 1 };
	Texture2D* currentSwordTexture{ &sword_idle_texture };
	Texture2D* currentShieldTexture{ &shield_idle_texture };
	Texture2D* currentHUDTexture{ &HUD_shield_impact_feedback };

	bool isAttacking{ false };
	float attackRadius{ 0.3f };
	float attackRange{ 1.4f };
	bool inAttackRange{ false };
	int attackDamage{ 35 };

	bool isDefending{ false };

	bool drawFeedbackHud{false};
	float feedbackHudDisplayTime{ 0.13f };
	double feedbackHudTimer{};

	Vector3 _initialPosition{};

	bool _playerGotKey{ false };
};