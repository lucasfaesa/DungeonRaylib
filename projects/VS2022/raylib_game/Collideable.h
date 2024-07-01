#pragma once
#include "raylib.h"
#include "Layers.h"

class Collideable {
public:
	Collideable() = default;
	Collideable(BoundingBox box, Layers::Layer layer);

	void UpdateBoundingBox(Vector3 min, Vector3 max);

	const BoundingBox& GetCollider();
	const Layers::Layer& GetLayer();

private:
	BoundingBox Collider{};
	Layers::Layer Layer{};
};