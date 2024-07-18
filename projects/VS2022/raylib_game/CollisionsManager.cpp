#include "CollisionsManager.h"

CollisionsManager::CollisionsManager(Player* player, std::vector<Enemy*>* enemiesVector, Structures* structures, LevelGenerator* levelGenerator, std::vector<Pickable*>* potionsVector, std::vector<Pickable*>* attackUpgradeVector) :
    _player(player), _enemiesVector(enemiesVector), _structures(structures), _levelGenerator(levelGenerator), _potionsVector(potionsVector), attackUpgradeVector(attackUpgradeVector)
{
}

void CollisionsManager::Update(float deltaTime)
{
    CheckCollisions();
}

void CollisionsManager::CheckCollisions()
{
    ComputeEnvironmentCollisions();

    //that are following the player
    std::vector<Enemy*> enemiesInCollision{};

    const BoundingBox& playerBoundingBoxBody = _player->GetBodyCollideable().GetCollider();

    for(Pickable* potion : *_potionsVector)
    {
        if (potion->GetWasPicked())
            continue;

        CheckPlayerAgainstPotions(potion, playerBoundingBoxBody);
    }

    for (Pickable* attackUpgrade : *attackUpgradeVector)
    {
        if (attackUpgrade->GetWasPicked())
            continue;

        CheckPlayerAgainstAttackUpgrade(attackUpgrade, playerBoundingBoxBody);
    }

    for (Enemy* enemy : *_enemiesVector)
    {
        if (enemy->GetIsDead())
            continue;

        PlayerWithEnemiesCollision(enemy);

        CheckEnemyWithEnemiesCollision(enemy, enemiesInCollision);

        EnemyRadiusChecks(enemy);

        PlayerAttackOnEnemyCheck(enemy);
    }

    ProcessEnemyWithEnemyCollision(enemiesInCollision);

}

void CollisionsManager::ComputeEnvironmentCollisions()
{
    _collisionOnPlayerFeet = false;

    const BoundingBox& playerBoundingBoxBody = _player->GetBodyCollideable().GetCollider();
    const BoundingBox& playerBoundingBoxFeet = _player->GetFootCollideable().GetCollider();


    for (RectangleF* shape : _structures->GetRectangles()) {

        CheckCollisionsAgainstEnvironment(_player, shape, playerBoundingBoxBody, playerBoundingBoxFeet);
    }

    for (const BoundingBox& boundingBox : _levelGenerator->GetBoundingBoxes()) {
        CheckCollisionsAgainstEnvironment(_player, boundingBox, playerBoundingBoxBody, playerBoundingBoxFeet);
    }

    if (!_collisionOnPlayerFeet)
    {
        _player->LeftCollisionOnFoot();
    }


    for(Enemy* enemy : *_enemiesVector)
    {
        if (enemy->GetIsDead())
            continue;

        _collisionOnEnemyFeet = false;

        const BoundingBox& enemyBoundingBoxBody = enemy->GetBodyBoundingBox();
        const BoundingBox& enemyBoundingBoxFeet = enemy->GetFeetBoundingBox();

        for (RectangleF* shape : _structures->GetRectangles()) {
           CheckCollisionsAgainstEnvironment(enemy, shape, enemyBoundingBoxBody, enemyBoundingBoxFeet);
        }

        for (const BoundingBox& boundingBox : _levelGenerator->GetBoundingBoxes()) {
            CheckCollisionsAgainstEnvironment(enemy, boundingBox, enemyBoundingBoxBody, enemyBoundingBoxFeet);
        }

        if (!_collisionOnEnemyFeet)
        {
            enemy->LeftCollisionOnFoot();
        }
    }
}

void CollisionsManager::CheckCollisionsAgainstEnvironment(Player* player, RectangleF* shape, const BoundingBox& playerBoundingBoxBody,
															const BoundingBox& playerBoundingBoxFeet)
{
    const BoundingBox& shapeBoundingBox = shape->GetCollideable().GetCollider();
    const auto shapeLayer = shape->GetCollideable().GetLayer();
    const auto shapePositionY = shape->GetPosition().y;
    const auto shapeSizeY = shape->GetSize().y;

   

    if (CheckCollisionBoxes(shapeBoundingBox, playerBoundingBoxBody)) {
        if (shapeLayer != Layers::Layer::GROUND)
            player->OnCollisionOnBody();
    }

    if (CheckCollisionBoxes(shapeBoundingBox, playerBoundingBoxFeet)) {
        player->OnCollisionOnFoot(shapePositionY + shapeSizeY * 0.5f);
        _collisionOnPlayerFeet = true;
    }

    /*const BoundingBox& shapeBoundingBox = shape->GetCollideable().GetCollider();
    const BoundingBox& playerBoundingBoxBody = _player->GetBodyCollideable().GetCollider();
    const BoundingBox& playerBoundingBoxFeet = _player->GetFootCollideable().GetCollider();


    if (CheckCollisionBoxes(shapeBoundingBox, playerBoundingBoxBody)) {
        if (shape->GetCollideable().GetLayer() != Layers::Layer::GROUND)
            _player->OnCollisionOnBody();
    }

    if (CheckCollisionBoxes(shapeBoundingBox, playerBoundingBoxFeet)) {
        _player->OnCollisionOnFoot(shape->GetPosition().y + shape->GetSize().y * 0.5f);
        _collisionOnPlayerFeet = true;
    }



    if (CheckCollisionBoxes(playerBoundingBoxBody, boundingBox)) {
        _player->OnCollisionOnBody();
    }

    if (CheckCollisionBoxes(boundingBox, playerBoundingBoxFeet)) {
        _player->OnCollisionOnFoot(boundingBox.max.y);
        _collisionOnPlayerFeet = true;
    }*/

}

void CollisionsManager::CheckCollisionsAgainstEnvironment(Player* player, const BoundingBox& boundingBox, const BoundingBox& playerBoundingBoxBody,
															const BoundingBox& playerBoundingBoxFeet)
{
    if (CheckCollisionBoxes(boundingBox, playerBoundingBoxBody)) {
            player->OnCollisionOnBody();
    }

    if (CheckCollisionBoxes(boundingBox, playerBoundingBoxFeet)) {
        player->OnCollisionOnFoot(boundingBox.max.y);
        _collisionOnPlayerFeet = true;
    }

    /*bool collisionBody = CheckCollisionBoxes(playerBoundingBoxBody, boundingBox);
    bool collisionFeet = CheckCollisionBoxes(boundingBox, playerBoundingBoxFeet);

    if (collisionBody) {
        player->OnCollisionOnBody();
    }

    if (collisionFeet) {
        player->OnCollisionOnFoot(boundingBox.max.y);
        _collisionOnPlayerFeet = true;
    }*/
}

void CollisionsManager::CheckCollisionsAgainstEnvironment(Enemy* enemy, RectangleF* shape, const BoundingBox& enemyBoundingBoxBody, 
															const BoundingBox& enemyBoundingBoxFeet)
{
    const BoundingBox& shapeBoundingBox = shape->GetCollideable().GetCollider();
    const auto shapeLayer = shape->GetCollideable().GetLayer();
    const auto shapePositionY = shape->GetPosition().y;
    const auto shapeSizeY = shape->GetSize().y;

    if (CheckCollisionBoxes(shapeBoundingBox, enemyBoundingBoxBody)) {
        if (shapeLayer != Layers::Layer::GROUND)
            enemy->OnCollisionOnBody();
    }

    if (CheckCollisionBoxes(shapeBoundingBox, enemyBoundingBoxFeet)) {
        enemy->OnCollisionOnFoot(shapePositionY + shapeSizeY * 0.5f);
        _collisionOnEnemyFeet = true;
    }

    /*bool collisionBody = CheckCollisionBoxes(shapeBoundingBox, enemyBoundingBoxBody);
    bool collisionFeet = CheckCollisionBoxes(shapeBoundingBox, enemyBoundingBoxFeet);

    if (collisionBody && shapeLayer != Layers::Layer::GROUND) {
        enemy->OnCollisionOnBody();
    }

    if (collisionFeet) {
        enemy->OnCollisionOnFoot(shapePositionY + shapeSizeY * 0.5f);
        _collisionOnEnemyFeet = true;
    }*/
}

void CollisionsManager::CheckCollisionsAgainstEnvironment(Enemy* enemy, const BoundingBox& boundingBox,
	const BoundingBox& enemyBoundingBoxBody, const BoundingBox& enemyBoundingBoxFeet)
{
    if(!enemy->IsFollowingPlayer())
    {
        return;
    }

    enemy->SetCalculatePhysics(true);

    if (CheckCollisionBoxes(boundingBox, enemyBoundingBoxBody)) {
            enemy->OnCollisionOnBody();
    }

    if (CheckCollisionBoxes(boundingBox, enemyBoundingBoxFeet)) {
        enemy->OnCollisionOnFoot(boundingBox.max.y);
        _collisionOnEnemyFeet = true;
    }

    /*bool collisionBody = CheckCollisionBoxes(enemyBoundingBoxBody, boundingBox);
	 bool collisionFeet = CheckCollisionBoxes(boundingBox, enemyBoundingBoxFeet);

	 if (collisionBody) {
	     enemy->OnCollisionOnBody();
	 }

	 if (collisionFeet) {
	     enemy->OnCollisionOnFoot(boundingBox.max.y);
	     _collisionOnEnemyFeet = true;
	 }*/
}

void CollisionsManager::CheckPlayerAgainstPotions(Pickable* pickable, const BoundingBox& playerBoundingBoxBody)
{
    if(CheckCollisionBoxes(pickable->GetBoundingBox(), playerBoundingBoxBody))
    {
        pickable->OnTriggerEnter();
        _player->RegenLife(35);
    }
}

void CollisionsManager::CheckPlayerAgainstAttackUpgrade(Pickable* pickable, const BoundingBox& playerBoundingBoxBody)
{
    if (CheckCollisionBoxes(pickable->GetBoundingBox(), playerBoundingBoxBody))
    {
        pickable->OnTriggerEnter();
        _player->AttackUp();
    }
}


void CollisionsManager::EnemyRadiusChecks(Enemy* enemy) const
{
    enemy->CheckTargetInsideDetectionRadius();
    enemy->CheckTargetInsideAttackRadius();
}

void CollisionsManager::PlayerAttackOnEnemyCheck(Enemy* enemy) const
{
    if (_player->IsAttacking())
    {
        float playerAttackRange = _player->GetAttackRangeAndRadius().first;
        float playerAttackRadius = _player->GetAttackRangeAndRadius().second;

        Vector3 spherePosition = Vector3Add(_player->GetPlayerPosition(),
            Vector3Scale(GetCameraForward(&_player->GetPlayerCamera()), playerAttackRange));
        spherePosition.y += 1.8f;

        bool inAttackRange = CheckCollisionBoxSphere(enemy->GetBodyBoundingBox(), spherePosition, playerAttackRadius);

        _player->PlayerInAttackRange(inAttackRange);

        if (inAttackRange)
            enemy->TakeDamage(_player->GetAttackDamage());
    }
}

void CollisionsManager::PlayerWithEnemiesCollision(Enemy* enemy)
{
    
    const BoundingBox& enemyBoundingBox = enemy->GetBodyBoundingBox();
    const BoundingBox& playerBoundingBoxBody = _player->GetBodyCollideable().GetCollider();
    const BoundingBox& playerBoundingBoxFeet = _player->GetFootCollideable().GetCollider();

    if (CheckCollisionBoxes(enemyBoundingBox, playerBoundingBoxBody)) {
        _player->OnCollisionOnBody();
    }

    if (CheckCollisionBoxes(enemyBoundingBox, playerBoundingBoxFeet)) {
        _player->OnCollisionOnFoot(enemyBoundingBox.max.y);
        _collisionOnPlayerFeet = true;

    }
}

void CollisionsManager::CheckEnemyWithEnemiesCollision(Enemy* thisEnemy, std::vector<Enemy*>& enemiesInCollision)
{

    for (Enemy* otherEnemy : *_enemiesVector)
    {
        if (thisEnemy == otherEnemy)
            continue;
        if (otherEnemy->GetIsDead())
            continue;

        const BoundingBox& thisEnemyBoundingBox = thisEnemy->GetBodyBoundingBox();
        const BoundingBox& otherEnemyBoundingBox = otherEnemy->GetBodyBoundingBox();
        
        if (CheckCollisionBoxes(thisEnemyBoundingBox, otherEnemyBoundingBox)) {

            if (thisEnemy->IsOnWaitBeforeWalkingTime())
                continue;

            enemiesInCollision.emplace_back(thisEnemy);
        }
    }


}

void CollisionsManager::ProcessEnemyWithEnemyCollision(std::vector<Enemy*>& enemiesInCollision)
{

    if (enemiesInCollision.empty())
        return;

    Enemy* closestToThePlayer{ nullptr };

    for (Enemy* loopEnemy : enemiesInCollision)
    {
        if (!closestToThePlayer ||
            (loopEnemy->IsFollowingPlayer() && loopEnemy->GetDistanceFromPlayer() < closestToThePlayer->GetDistanceFromPlayer()))
        {
            closestToThePlayer = loopEnemy;
        }
    }

    enemiesInCollision.erase(std::remove(enemiesInCollision.begin(), enemiesInCollision.end(),
												closestToThePlayer),enemiesInCollision.end());

    for (Enemy* enemy : enemiesInCollision)
    {
        enemy->WaitBeforeWalkingAgain();
    }
}
