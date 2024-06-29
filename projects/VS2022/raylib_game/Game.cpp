#include "Game.h"

Game::Game(bool initiliazed):
	initialized(initialized)
{	
	player = RectangleF(Vector3{ 0.0f, .5f, 8.0f }, Vector3{ 1.0f, 1.0f, 1.0f}, RED);

	mainCamera = &cameraManager.GetCamera();
	
	Start();
}

void Game::Start()
{
	DisableCursor();
	//cameraManager.CameraLookAt(rectangle.)
}

void Game::InputRead()
{
	player.ReadInput();
	cameraManager.ReadInput();
}

void Game::Update(float deltaTime)
{
	cameraManager.Update(deltaTime);
	//player.Move(deltaTime);
}

void Game::Draw()
{
	BeginMode3D(*mainCamera);

	player.Draw();
	structures.Draw();

	//cameraManager.CameraLookAt(player.GetPosition());

	DrawGrid(100, 1.f);

	EndMode3D();
}

bool Game::IsInitialized() const
{
	return initialized;
}

