#include "CollisionsManager.h"

CollisionsManager::CollisionsManager(Player* player, std::vector<Enemy*>* enemiesVector, Structures* structures, LevelGenerator* levelGenerator) :
    _player(player), _enemiesVector(enemiesVector), _structures(structures), _levelGenerator(levelGenerator)
{
}

void CollisionsManager::Update(float deltaTime)
{
    CheckCollisions();
}

void CollisionsManager::CheckCollisions()
{
    _collisionOnPlayerFeet = false;

    ComputeEnvironmentCollisions();

    for (Enemy* enemy : *_enemiesVector)
    {
        if (enemy->GetIsDead())
            continue;

        PlayerWithEnemiesCollision(enemy);

        EnemyRadiusChecks(enemy);

        PlayerAttackOnEnemyCheck(enemy);

    }

    if (!_collisionOnPlayerFeet)
    {
        _player->LeftCollisionOnFoot();
    }

}

void CollisionsManager::ComputeEnvironmentCollisions()
{
    const BoundingBox& playerBoundingBoxBody = _player->GetBodyCollideable().GetCollider();
    const BoundingBox& playerBoundingBoxFeet = _player->GetFootCollideable().GetCollider();

    for(Enemy* enemy : *_enemiesVector)
    {
        const BoundingBox& enemyBoundingBoxBody = enemy->GetBoundingBox();

        for (RectangleF* shape : _structures->GetRectangles()) {
           CheckCollisionsAgainstEnvironment(enemy, shape, enemyBoundingBoxBody, BoundingBox{});
        }

        for (const BoundingBox& boundingBox : _levelGenerator->GetBoundingBoxes()) {
            CheckCollisionsAgainstEnvironment(enemy, boundingBox, enemyBoundingBoxBody, BoundingBox{});
        }
    }


    for (RectangleF* shape : _structures->GetRectangles()) {

        CheckCollisionsAgainstEnvironment(_player, shape, playerBoundingBoxBody, playerBoundingBoxFeet);
    }

    for (const BoundingBox& boundingBox : _levelGenerator->GetBoundingBoxes()) {
        CheckCollisionsAgainstEnvironment(_player, boundingBox, playerBoundingBoxBody, playerBoundingBoxFeet);
    }
}

void CollisionsManager::CheckCollisionsAgainstEnvironment(Player* player, RectangleF* shape, const BoundingBox& playerBoundingBoxBody,
															const BoundingBox& playerBoundingBoxFeet)
{
    const BoundingBox& shapeBoundingBox = shape->GetCollideable().GetCollider();
    const auto shapeLayer = shape->GetCollideable().GetLayer();
    const auto shapePositionY = shape->GetPosition().y;
    const auto shapeSizeY = shape->GetSize().y;

    bool collisionBody = CheckCollisionBoxes(shapeBoundingBox, playerBoundingBoxBody);
    bool collisionFeet = CheckCollisionBoxes(shapeBoundingBox, playerBoundingBoxFeet);

    if (collisionBody && shapeLayer != Layers::Layer::GROUND) {
        player->OnCollisionOnBody();
    }

    if (collisionFeet) {
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
    /*bool collisionBody = CheckCollisionBoxes(playerBoundingBoxBody, boundingBox);
    bool collisionFeet = CheckCollisionBoxes(boundingBox, playerBoundingBoxFeet);

    if (collisionBody) {
        _player->OnCollisionOnBody();
    }

    if (collisionFeet) {
        _player->OnCollisionOnFoot(boundingBox.max.y);
        _collisionOnPlayerFeet = true;
    }*/
}

void CollisionsManager::CheckCollisionsAgainstEnvironment(Enemy* enemy, RectangleF* shape,
	const BoundingBox& playerBoundingBoxBody, const BoundingBox& playerBoundingBoxFeet)
{
    const BoundingBox& shapeBoundingBox = shape->GetCollideable().GetCollider();
    const auto shapeLayer = shape->GetCollideable().GetLayer();
    const auto shapePositionY = shape->GetPosition().y;
    const auto shapeSizeY = shape->GetSize().y;

    bool collisionBody = CheckCollisionBoxes(shapeBoundingBox, playerBoundingBoxBody);
    bool collisionFeet = CheckCollisionBoxes(shapeBoundingBox, playerBoundingBoxFeet);

    if (collisionBody && shapeLayer != Layers::Layer::GROUND) {
        enemy->OnCollisionOnBody();
    }

    /*if (collisionFeet) {
        enemy->OnCollisionOnFoot(shapePositionY + shapeSizeY * 0.5f);
        _collisionOnPlayerFeet = true;
    }*/
}

void CollisionsManager::CheckCollisionsAgainstEnvironment(Enemy* enemy, const BoundingBox& boundingBox,
	const BoundingBox& playerBoundingBoxBody, const BoundingBox& playerBoundingBoxFeet)
{
    /*bool collisionBody = CheckCollisionBoxes(playerBoundingBoxBody, boundingBox);
	 bool collisionFeet = CheckCollisionBoxes(boundingBox, playerBoundingBoxFeet);

	 if (collisionBody) {
	     _player->OnCollisionOnBody();
	 }

	 if (collisionFeet) {
	     _player->OnCollisionOnFoot(boundingBox.max.y);
	     _collisionOnPlayerFeet = true;
	 }*/
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

        bool inAttackRange = CheckCollisionBoxSphere(enemy->GetBoundingBox(), spherePosition, playerAttackRadius);

        _player->PlayerInAttackRange(inAttackRange);

        if (inAttackRange)
            enemy->TakeDamage(_player->GetAttackDamage());
    }
}

void CollisionsManager::PlayerWithEnemiesCollision(Enemy* enemy)
{
    
    const BoundingBox& enemyBoundingBox = enemy->GetBoundingBox();
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
