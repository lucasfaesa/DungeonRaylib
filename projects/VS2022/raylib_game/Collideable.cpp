#include "Collideable.h"

Collideable::Collideable(BoundingBox box, Layers::Layer layer):
	Collider {	box}, Layer{ layer }
{
}

void Collideable::UpdateBoundingBox(Vector3 min, Vector3 max)
{
	Collider.min = min;
	Collider.max = max;
}

const BoundingBox& Collideable::GetCollider()
{
	return Collider;
}


const Layers::Layer& Collideable::GetLayer()
{
	return Layer;
}

