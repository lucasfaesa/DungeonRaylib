#include "GameSessionController.h"

#include <string>


GameSessionController::GameSessionController(Player* player, std::vector<Enemy*>* enemies):
	player(player), enemiesVector(enemies)
{
}

void GameSessionController::RestartGame()
{
	_isGameOver = false;
	_isGameWon = false;

	player->OnGameRestarted();

	for (Enemy* enemy: *enemiesVector)
	{
		enemy->OnGameRestarted();
	}
}

void GameSessionController::ReadInput()
{
	if((_isGameOver || _isGameWon)  && IsKeyReleased(KEY_R))
	{
		std::cout << "Restarted game" << std::endl;
		RestartGame();
	}
}

void GameSessionController::DrawCanvas()
{
	int countDead = 0;
	int totalEnemies = enemiesVector->size();

	for (Enemy* enemy : *enemiesVector) {
		if (enemy->GetIsDead()) {
			countDead++;
		}
	}

	std::string statusText = "Enemies " + std::to_string(countDead) + "/" + std::to_string(totalEnemies);

	DrawText(statusText.c_str(), 430.f, 755.f, 23, WHITE);

	if(_isGameOver)
	{
		DrawText("GAME OVER", 200.f, 330.f, 60, RED);
		DrawText("Press \"R\" to Restart Game!", 225.f, 390.f, 23, WHITE);
	}

	if(_isGameWon)
	{
		DrawText("CONGRATULATIONS", 90.f, 330.f, 60, BLUE);
		DrawText("Thank you for playing my first game with raylib!", 120.f, 390.f, 23, WHITE);
		DrawText("Press \"R\" to Restart Game!", 225.f, 420.f, 23, WHITE);
	}

}

void GameSessionController::GameWon()
{
	player->SetGameWon();
	_isGameWon = true;
}

void GameSessionController::GameOver()
{
	_isGameOver = true;
}

void GameSessionController::Update()
{

	if (player->GetIsDead())
		GameOver();

	for (Enemy* enemy : *enemiesVector) {
		if (!enemy->GetIsDead()) {
			return;
		}
	}

	GameWon();
}




