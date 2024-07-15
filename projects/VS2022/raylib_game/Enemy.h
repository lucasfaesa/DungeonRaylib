#pragma once
#include "Agent.h"
#include "Player.h"
#include "Damageable.h"

class Enemy : public Agent, public Damageable {

public:
	Enemy() = default;
	Enemy(Vector3 pos, Vector3 size, Player& player);

	void Update(float deltaTime) override;
	void Draw() override;
	void OnApplicationQuit();

	void AttackPlayer(float deltaTime);
	void CountAttackTimer(float deltaTime);
	float GetDistanceFromPlayer() const;

	void SetDead() override;

	void OnCollisionOnBody();
	void OnCollisionOnFoot(float topYPos);
	void LeftCollisionOnFoot();

	void WaitBeforeWalkingAgain();
	bool IsOnWaitBeforeWalkingTime();
	bool IsFollowingPlayer();

	void SetCalculatePhysics(bool status);

	void TakeDamage(int value) override;

	void OnGameRestarted();

	//frame related
	static Texture2D walkTexture;
	static Texture2D idleTexture;
	static Texture2D dieTexture;

	

private:
	enum class State { IDLE, WALKING, DEAD };

	void ChangeCurrentState(State newState);
	void CountAnimationFrames(float deltaTime);
	void ForcePositionXZChange();
	void ForcePositionYChange(float topYPos);

private:

	Player* _player;
	Camera* _camera;

	float attackDelay{ 2.f };
	float attackTimer{0.f};
	int _attackDamage{ 5 };

	State currentState{ State::IDLE };


	Rectangle frameRec;

	Vector3 billboardUp = { 0.f, 1.f, 0.f };

	int currentFrame{ 0 };

	int framesCounter{ 0 };

	//per second
	int walkFramesSpeed{ 4 };
	int dyingFramesSpeed{ 4 };
	int idleFramesSpeed{ 1 };

	static constexpr int walkTotalFrames{ 4 };
	static constexpr int dyingTotalFrames{ 5 };
	static constexpr int idleTotalFrames{ 1 };

	int currentAnimationFrameSpeed{ 1 };
	int currentAnimationTotalFrames{ 1 };
	Texture2D* currentTexture{ &idleTexture };

	bool preparingToDie{ false };

	bool isCollidingBody{ false };
	Vector3 lastPositionBeforeBodyCollision{};


	float waitBeforeWalkingDuration{0.3f};
	float waitBeforeWalkingTimer;

	bool followingPlayer{false};

	bool calculatePhysics{false};

	bool damageTook{false};
	float damageFeedbackDuration = 0.05f;
	float damageTookTime{0.f};

	Color drawColor{ WHITE };

	Vector3 initialPosition{};
};