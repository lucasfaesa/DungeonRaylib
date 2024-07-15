#pragma once
#include "raylib.h"

class Pickable
{
public:

	Pickable() = default;
	Pickable(Vector3 pos, Vector3 size, Texture2D tex, Camera* camera);

	virtual void Draw();
	virtual void OnTriggerEnter();
	BoundingBox& GetBoundingBox();
	bool GetWasPicked() const;

private:
	BoundingBox boundingBox{};

	Texture2D texture{};
	Rectangle frameRec{ 0.0f, 0.0f, 300.f, 300.f};
	Camera* camera{nullptr};

	Vector3 position;
	Vector3 size;

	bool picked{false};
};
