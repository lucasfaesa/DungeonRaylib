#include "CollisionsManager.h"

CollisionsManager::CollisionsManager(Player* player, std::vector<Enemy*>* enemiesVector, Structures* structures, LevelGenerator* levelGenerator):
	_player(player), _enemiesVector(enemiesVector), _structures(structures), _levelGenerator(levelGenerator)
{
}

void CollisionsManager::Update(float deltaTime)
{
    CheckCollisions();
}

void CollisionsManager::CheckCollisions()
{
    if(checkPlayerCollisions)
    {
        bool collisionOnFoot{ false };

        for (RectangleF* shape : _structures->GetRectangles()) {
            if (CheckCollisionBoxes(shape->GetCollideable().GetCollider(), _player->GetBodyCollideable().GetCollider())) {
                if (shape->GetCollideable().GetLayer() != Layers::Layer::GROUND)
                    _player->OnCollisionOnBody();
            }

            if (CheckCollisionBoxes(shape->GetCollideable().GetCollider(), _player->GetFootCollideable().GetCollider())) {
                _player->OnCollisionOnFoot(*shape);
                collisionOnFoot = true;
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

        if (!collisionOnFoot)
            _player->LeftCollisionOnFoot();
    }

    for (Enemy* enemy : *_enemiesVector)
    {
        enemy->CheckTargetInsideDetectionRadius();
        enemy->CheckTargetInsideAttackRadius();
    }

    
}