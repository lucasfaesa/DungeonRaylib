#include "Structures.h"

Structures::Structures(int maxStructs):
	maxStructures(maxStructs)
{
	for (int i = 0; i < maxStructures; i++)
	{
		int xz = GetRandomValue(2, 4);
		Vector3 size{ xz, GetRandomValue(13,16), xz};

		Vector3 position { GetRandomValue(-40, 40), size.y * 0.5f, GetRandomValue(-40,40)};

		Color color { GetRandomValue(20, 255), GetRandomValue(40, 155), GetRandomValue(20, 255), 255 };

		structuresArray.emplace_back(Shape(position, size, color));
	}
}

void Structures::Draw()
{
	for (Shape& shape : structuresArray) {
		DrawCube(shape.GetPosition(),
			shape.GetSize().x, shape.GetSize().y, shape.GetSize().z, shape.GetColor());
	}
}

