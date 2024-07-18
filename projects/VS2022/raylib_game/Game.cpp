#include "Game.h"


Game::Game(bool initialized) :
	initialized(initialized)

{
	player = new Player( Vector3{ 50.f,0.f,75.f });

	CreateEnemies();
	CreatePotions();
	keyPickable = new Pickable({ 3.95f,13.01f, -53.74f }, { 1.f,1.f,1.f },	keyTexture, &CameraManager::GetPlayerCamera());

	levelGenerator = new LevelGenerator();
	structures = new Structures(0);

	collisionsManager = new CollisionsManager(player, enemiesVector, structures, levelGenerator, potionsVector, keyPickable);

	gameSessionController = new GameSessionController(player, enemiesVector);

	
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
	gameSessionController->ReadInput();
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

	std::sort(enemiesVector->begin(), enemiesVector->end(), [](const Enemy* a, const Enemy* b) {
		return a->GetDistanceFromPlayer() > b->GetDistanceFromPlayer();
		});


	for (Enemy* enemy : *enemiesVector)
	{
		enemy->Draw();
	}

	for (Pickable* potion : *potionsVector)
	{
		potion->Draw();
	}

	keyPickable->Draw();

	levelGenerator->Draw();

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

void Game::CreateEnemies()
{


	enemiesVector->emplace_back(new Enemy({ 5.93f, 0.f, 55.12f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ 8.73f, 0.f, 46.56f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ 60.03f, 0.f, 42.99f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ 42.63f, 10.01f, 55.85f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -2.07f, 0.f, 71.56f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -16.94f, 0.f, 59.55f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -52.78f, 3.01f, 60.09f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -53.23f, 3.01f, 20.90f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -65.59f, 4.01f, 30.79f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -65.59f, 4.01f, 36.96f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -65.59f, 4.01f, 43.30f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -65.59f, 4.01f, 48.14f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -4.50f, 0.f, 15.37f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -20.21f, 0.f, -0.50f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ 17.78f, 2.01f, 5.58f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ 7.27f, 1.01f, 5.35f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ 19.38f, 1.01f, -6.91f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ 28.07f, 0.f, -16.0f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ 30.10f, 0.f, -36.13f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -1.50f, 0.f, -33.10f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ 4.42f, 0.f, -41.10f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -16.12f, 0.f, -37.49f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -30.76f, 0.f, -28.97f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -44.73f, 0.f, -32.76f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -51.34f, 0.f, -23.41f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -57.06f, 0.f, -14.67f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -58.31f, 0.f, -46.14f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -59.98f, 0.f, -46.14f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -62.15f, 0.f, -46.14f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -64.32f, 0.f, -46.14f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -53.12f, 0.f, -55.03f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -35.25f, 6.01f, -72.63f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -38.90f, 6.01f, -69.18f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -42.15f, 6.01f, -72.28f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -45.82f, 6.01f, -69.30f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -48.87f, 6.01f, -72.72f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -51.84f, 6.01f, -68.94f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ -69.02f, 6.01f, -71.14f }, { 1.f, (float)GetRandomValue(1.5f,4.5f), 1.f }, *player));
	enemiesVector->emplace_back(new Enemy({ 48.53f, 0.f, -61.19f }, { 1.f, 9.5f, 1.f }, *player));
	for (Enemy* enemy : *enemiesVector)
	{
		enemy->SetSeekBehavior(new SeekBehavior(player->GetPlayerPosition()));
	}
}

void Game::CreatePotions()
{
	potionsVector->emplace_back(new Pickable({ 25.23f, 10.01f, 56.44f }, { 1.f,1.f,1.f },
		potionTexture, &CameraManager::GetPlayerCamera()));

	potionsVector->emplace_back(new Pickable({ -19.56f, 1.01f, 54.47f }, { 1.f,1.f,1.f },
		potionTexture, &CameraManager::GetPlayerCamera()));

	potionsVector->emplace_back(new Pickable({ -66.57f, 0.01f, 39.04f }, { 1.f,1.f,1.f },
		potionTexture, &CameraManager::GetPlayerCamera()));

	potionsVector->emplace_back(new Pickable({ 5.85f, 1.01f, -6.84f }, { 1.f,1.f,1.f },
		potionTexture, &CameraManager::GetPlayerCamera()));

	potionsVector->emplace_back(new Pickable({ 22.60f, 12.01f, -33.01f }, { 1.f,1.f,1.f },
		potionTexture, &CameraManager::GetPlayerCamera()));

	potionsVector->emplace_back(new Pickable({ -22.96f, 12.01f, -23.09f }, { 1.f,1.f,1.f },
		potionTexture, &CameraManager::GetPlayerCamera()));

	potionsVector->emplace_back(new Pickable({ -63.72f, 0.f, -32.18f }, { 1.f,1.f,1.f },
		potionTexture, &CameraManager::GetPlayerCamera()));

	potionsVector->emplace_back(new Pickable({ -66.56f, 0.f, -52.89f }, { 1.f,1.f,1.f },
		potionTexture, &CameraManager::GetPlayerCamera()));

	potionsVector->emplace_back(new Pickable({ -71.47f, 6.01f, -70.90f }, { 1.f,1.f,1.f },
		potionTexture, &CameraManager::GetPlayerCamera()));

	potionsVector->emplace_back(new Pickable({ 72.70f, 0.f, -65.70f }, { 1.f,1.f,1.f },
		potionTexture, &CameraManager::GetPlayerCamera()));
}


