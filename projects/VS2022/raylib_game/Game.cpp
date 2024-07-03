#include "Game.h"

Game::Game(bool initiliazed):
	initialized(initialized)
	
{		
	Start();

	player = {Vector3{ 0.f,0.f,0.f }, Vector3{ 0.f,0.f,0.f }};
}

void Game::Start()
{
	levelGenerator.Start();
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

void Game::FixedUpdateCalculation(float deltaTime)
{
	// Accumulate elapsed time.
	accumulatedTime += deltaTime;

	// Process fixed updates at fixed time steps.
	while (accumulatedTime >= fixedTimeStep) {
		FixedUpdate(fixedTimeStep);
		accumulatedTime -= fixedTimeStep;
	}
}

void Game::FixedUpdate(float deltaTime)
{
	player.FixedUpdate(deltaTime);
}

void Game::OnApplicationClose()
{
	structures.~Structures();
}

void Game::Draw()
{
	BeginMode3D(CameraManager::GetPlayerCamera());

	structures.Draw();
	levelGenerator.Draw();
	player.Draw();

	DrawGrid(100, 1.f);

	EndMode3D();
}

void Game::DrawCanvas()
{
	DrawFPS(10, 5);
	Logger::ResetPosition();
	player.DrawCanvas();
}

bool Game::IsInitialized() const
{
	return initialized;
}

void Game::CheckForPlayerCollision()
{
}

