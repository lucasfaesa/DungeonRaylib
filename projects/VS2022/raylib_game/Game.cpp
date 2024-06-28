#include "Game.h"

Game::Game(bool initiliazed):
	initialized(initialized)
{
	
	//rectangle = RectangleF(Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 15.0f, 15.0f, 15.0f }, GOLD);
	rectangle = RectangleF(Vector3{ 0.0f, 2.5f, 0.0f }, Vector3{ 5.0f, 5.0f, 5.0f}, RED);
	//windowWidth / 4 * 2 - 60, 100, 120, 60
	Start();
}

void Game::Start()
{

}

void Game::InputRead()
{

}

void Game::Update()
{

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

