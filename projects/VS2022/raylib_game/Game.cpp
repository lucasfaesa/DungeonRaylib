#include "Game.h"

Game::Game(bool initialized) :
	initialized(initialized)

{

	player = new Player({ Vector3{ 0.f,0.f,0.f }, Vector3{ 0.f,0.f,0.f } });
	seekBehavior = new SeekBehavior(player->GetPlayerPosition());

	for(int i=0; i < enemiesQuantity; i++)
	{
		enemiesVector->emplace_back(new Enemy({ 30.f, 0.f, 30.f }, { 1.f, 3.f, 1.f }, 
									8.2f, player->GetPlayerPosition(), 
								player->GetBodyCollideable().GetCollider(), 2.f, 30.f, *player,
											CameraManager::GetPlayerCamera()));

		(*enemiesVector)[i]->SetSeekBehavior(seekBehavior);
	}

	levelGenerator = new LevelGenerator();
	structures = new Structures(0);

	collisionsManager = new CollisionsManager(player, enemiesVector, structures, levelGenerator);

	Start();
}

void Game::Start() const
{
	levelGenerator->Start();
	DisableCursor();
}

void Game::InputRead() const 
{
	player->ReadInput();
}

void Game::Update(float deltaTime) const
{
	player->Update(deltaTime);

	for (Enemy* enemy : *enemiesVector)
	{
		enemy->Update(deltaTime);
	}

	collisionsManager->Update(deltaTime);
	
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

void Game::FixedUpdate(float deltaTime) const
{
	player->FixedUpdate(deltaTime);
}

void Game::OnApplicationClose() const
{
	for (Enemy* enemy : *enemiesVector)
	{
		enemy->OnApplicationQuit();
		enemy->~Enemy();
	}
	structures->~Structures();
}

void Game::Draw() const
{
	BeginMode3D(CameraManager::GetPlayerCamera());

	structures->Draw();
	for (Enemy* enemy : *enemiesVector)
	{
		enemy->Draw();
	}
	//levelGenerator.Draw();
	player->Draw();

	//DrawGrid(100, 1.f);

	EndMode3D();
}

void Game::DrawCanvas() const
{
	DrawFPS(10, 5);
	Logger::ResetPosition();
	player->DrawCanvas();
}

bool Game::IsInitialized() const
{
	return initialized;
}


