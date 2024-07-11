#pragma once
#include "Agent.h"
#include "Player.h"
#include "Damageable.h"

class Enemy : public Agent, public Damageable {

public:
	Enemy() = default;
	Enemy(Vector3 pos, Vector3 size, float maxSpeed, Vector3& targetPos,
		const BoundingBox& targetBoudingBox, float attackRadius, float detectionRadius, Player& player, Camera& camera);

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

	//frame related
	Texture2D idleTexture = LoadTexture("../resources/enemy/frogmon_stand.png");
	Texture2D walkTexture = LoadTexture("../resources/enemy/frogmon_walk.png");
	Texture2D dieTexture = LoadTexture("../resources/enemy/frogmon_die.png");

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

	bool followingPlayer;

};