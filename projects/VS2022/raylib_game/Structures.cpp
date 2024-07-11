#include "Structures.h"

Structures::Structures(int maxStructs):
	maxStructures(maxStructs)
{
	rectanglesArray.emplace_back(new RectangleF{ ground });
	//rectanglesArray.emplace_back(new RectangleF{ testBox });

	for (int i = 0; i < maxStructures; i++)
	{
		int xz = GetRandomValue(2, 4);
		Vector3 size{ xz, GetRandomValue(1,16), xz};

		Vector3 position { GetRandomValue(-40, 40), size.y * 0.5f, GetRandomValue(-40,40)};

		Color color { GetRandomValue(20, 255), GetRandomValue(40, 155), GetRandomValue(20, 255), 255 };

		rectanglesArray.emplace_back(new RectangleF(position, size, color));
	}
}

void Structures::Update(float deltaTime)
{
	
}

Structures::~Structures()
{
	for (Shape* shape : rectanglesArray) {
		
		delete shape;
	}

	rectanglesArray.clear();
}

void Structures::Draw()
{
	/*for (Shape* shape : rectanglesArray) {
		shape->Draw();
	}*/

	//testBox.Draw();
	//ground.Draw();
}

std::vector<RectangleF*>& Structures::GetRectangles()
{
	return rectanglesArray;
}

