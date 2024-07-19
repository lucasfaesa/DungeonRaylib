#include "Structures.h"

Structures::Structures(int maxStructs):
	maxStructures(maxStructs)
{
	rectanglesArray.emplace_back(new RectangleF{ ground });
	//rectanglesArray.emplace_back(new RectangleF{ testBox });
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

