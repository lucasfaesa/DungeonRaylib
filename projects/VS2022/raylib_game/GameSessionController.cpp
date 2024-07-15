#include "GameSessionController.h"


GameSessionController::GameSessionController(Player* player, std::vector<Enemy*>* enemies):
	player(player), enemiesVector(enemies)
{
}

void GameSessionController::RestartGame()
{
	//isGameOver = false;
	player->OnGameRestarted();

	for (Enemy* enemy: *enemiesVector)
	{
		enemy->OnGameRestarted();
	}
}

void GameSessionController::ReadInput()
{
	if(/*player->GetIsDead()  &&*/ IsKeyReleased(KEY_R))
	{
		std::cout << "Restarted game" << std::endl;
		RestartGame();
	}
}




