#include "Pickable.h"

Pickable::Pickable(Vector3 pos, Vector3 size, Texture2D tex, Camera* camera):
			position(pos), size(size), texture(tex), camera(camera)
{
	Vector3 bodyMin{ position.x - size.x * 0.5f, position.y, position.z - size.z * 0.5f };
	Vector3 bodyMax{ position.x + size.x * 0.5f, position.y + size.y, position.z + size.z * 0.5f };

	boundingBox = BoundingBox{ bodyMin, bodyMax };
}

void Pickable::Draw()
{
	if (picked) return;

	DrawBoundingBox(boundingBox, RED);

	DrawBillboardRec(*camera, texture, frameRec, { position.x, position.y + size.y * 0.5f, position.z }, { size.y, size.y }, WHITE);

}

void Pickable::OnTriggerEnter()
{
	if (picked) return;

	picked = true;
}

BoundingBox& Pickable::GetBoundingBox()
{
	return boundingBox;
}

bool Pickable::GetWasPicked() const
{
	return picked;
}
