#include "Game.h"

Game::Game(bool initiliazed):
	initialized(initialized)
{
	
	
	rectangle = RectangleF(Vector3{ 0.0f, .5f, 0.0f }, Vector3{ 1.0f, 1.0f, 1.0f}, RED);
	
	Start();
}

void Game::Start()
{

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
	rectangle.Draw();
	DrawGrid(100, 1.f);
}

bool Game::IsInitialized() const
{
	return initialized;
}

