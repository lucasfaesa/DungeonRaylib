#pragma once
#include "Agent.h"
#include "Player.h"

class Enemy : public Agent {

public:
	Enemy() = default;
	Enemy(Vector3 pos, Vector3 size, float maxSpeed, Vector3& targetPos,
		const BoundingBox& targetBoudingBox, float attackRadius, float detectionRadius, Player& player, Camera& camera);

	void Update(float deltaTime) override;
	void Draw() override;
	void OnApplicationQuit();

	void AttackPlayer(float deltaTime);
	void CountAttackTimer(float deltaTime);
	void SetDistanceFromPlayer();
	float GetDistanceFromPlayer() const;
private:
	Texture2D billboardTexture = LoadTexture("../resources/enemy/frogmon_stand.png");
	Vector3 billboardUp = { 0.f, 1.f, 0.f };
	float _distanceFromPlayer;

	Player* _player;
	Camera* _camera;

	float attackDelay{ 2.f };
	float attackTimer{0.f};
	int _attackDamage{ 5 };
};