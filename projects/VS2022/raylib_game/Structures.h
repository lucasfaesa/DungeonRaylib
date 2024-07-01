#pragma once

#include <vector>
#include "Shape.h"
#include "RectangleF.h"

class Structures {

public:
	Structures() = default;
	Structures(int maxStructs);
	~Structures();
	void Draw();
private:
	int const maxStructures{ 20 };
	std::vector<Shape *> structuresArray{};
	RectangleF testBox{ Vector3{ 4.f, 0.9f, 0.f }, Vector3{ 0.8f, 1.8f, 0.8f }, ORANGE };
};
