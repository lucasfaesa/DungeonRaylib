#include "Game.h"

Game::Game(bool initiliazed):
	initialized(initialized)
{	
	rectangle = RectangleF(Vector3{ 0.0f, .5f, 8.0f }, Vector3{ 1.0f, 1.0f, 1.0f}, RED);

	mainCamera = &cameraManager.GetCamera();
	
	Start();
}

void Game::Start()
{
	//cameraManager.CameraLookAt(rectangle.)
}

void Game::InputRead()
{

}

void Game::Update(float deltaTime)
{
	rectangle.Move(deltaTime);
}

void Game::Draw()
{
	BeginMode3D(*mainCamera);

	rectangle.Draw();
	
	cameraManager.CameraLookAt(rectangle.GetPosition());

	DrawGrid(100, 1.f);

	EndMode3D();
}

bool Game::IsInitialized() const
{
	return initialized;
}

