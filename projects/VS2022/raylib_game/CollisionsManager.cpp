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

    PlayerWithEnvironmentCollisions();

    for (Enemy* enemy : *_enemiesVector)
    {
        if (enemy->GetIsDead())
            continue;

        PlayerWithEnemiesCollision(enemy);

        //EnemyRadiusChecks(enemy);

        //PlayerAttackOnEnemyCheck(enemy);

    }

    if (!_collisionOnPlayerFeet)
    {
        _player->LeftCollisionOnFoot();
    }

}

void CollisionsManager::PlayerWithEnvironmentCollisions()
{

    for (RectangleF* shape : _structures->GetRectangles()) {

        const BoundingBox& shapeBoundingBox = shape->GetCollideable().GetCollider();
        const BoundingBox& playerBoundingBoxBody = _player->GetBodyCollideable().GetCollider();
        const BoundingBox& playerBoundingBoxFeet = _player->GetFootCollideable().GetCollider();

        if (CheckCollisionBoxes(shapeBoundingBox, playerBoundingBoxBody)) {
            if (shape->GetCollideable().GetLayer() != Layers::Layer::GROUND)
                _player->OnCollisionOnBody();
        }

        if (CheckCollisionBoxes(shapeBoundingBox, playerBoundingBoxFeet)) {
            _player->OnCollisionOnFoot(*shape);
            _collisionOnPlayerFeet = true;
        }
    }

    /*for (const BoundingBox& boundingBox : levelGenerator.GetBoundingBoxes()) {
        if (CheckCollisionBoxes(player.GetBodyCollideable().GetCollider(), boundingBox)) {
            player.OnCollisionOnBody();
        }

        if (CheckCollisionBoxes(boundingBox, player.GetFootCollideable().GetCollider())) {
            player.OnCollisionOnFoot(Helpers::ComputeBoundingBoxCenter(boundingBox).y + Helpers::ComputeBoundingBoxSize(boundingBox).y * 0.5f);
            collisionOnFoot = true;
        }
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
