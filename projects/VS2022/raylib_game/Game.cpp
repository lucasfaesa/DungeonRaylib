#include "Game.h"

Game::Game(bool initiliazed):
	initialized(initialized)
	
{		
	Start();

	player = {Vector3{ 0.f,0.f,0.f }, Vector3{ 0.f,0.f,0.f }};
}

void Game::Start()
{
	DisableCursor();
}

void Game::InputRead()
{
	player.ReadInput();
}

void Game::Update(float deltaTime)
{
	player.Update(deltaTime);

	bool collisionOnFoot{ false };

	for (RectangleF * shape : structures.GetRectangles()) {
		if (CheckCollisionBoxes(shape->GetCollideable().GetCollider(), player.GetBodyCollideable().GetCollider())) {
			if(shape->GetCollideable().GetLayer() != Layers::Layer::GROUND)
				player.OnCollisionOnBody();
		}

		if (CheckCollisionBoxes(shape->GetCollideable().GetCollider(), player.GetFootCollideable().GetCollider())) {
			player.OnCollisionOnFoot(*shape);
			collisionOnFoot = true;
		}
	}

	if (!collisionOnFoot)
		player.LeftCollisionOnFoot();
	
}

void Game::OnApplicationClose()
{
	structures.~Structures();
}

void Game::Draw()
{
	BeginMode3D(CameraManager::GetPlayerCamera());

	player.Draw();
	structures.Draw();

	DrawGrid(100, 1.f);

	EndMode3D();
}

bool Game::IsInitialized() const
{
	return initialized;
}

void Game::CheckForPlayerCollision()
{
}

