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
		int minutes = static_cast<int>(gameTime / 60);  // Whole number of minutes
		float remainingSeconds = fmod(gameTime, 60.0f); // Remaining seconds (including fractional part)
		int seconds = static_cast<int>(remainingSeconds);  // Whole number of seconds
		int milliseconds = static_cast<int>((remainingSeconds - seconds) * 1000); // Milliseconds

		// Print the results
		std::string time = "Your time: " + std::to_string(minutes) + ':' + std::to_string(seconds) + ':' + std::to_string(milliseconds);

		DrawText("CONGRATULATIONS", 90.f, 330.f, 60, BLUE);
		DrawText("Thank you for playing my first game with raylib!", 120.f, 390.f, 23, WHITE);
		DrawText("Press \"R\" to Restart Game!", 225.f, 420.f, 23, WHITE);
		DrawText(time.c_str(), 200.f, 470.f, 42, WHITE);
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

void GameSessionController::Update(float deltaTime)
{
	if (!_isGameWon)
		gameTime += deltaTime;

	if (player->GetIsDead())
		GameOver();

	for (Enemy* enemy : *enemiesVector) {
		if (!enemy->GetIsDead()) {
			return;
		}
	}

	GameWon();
}




