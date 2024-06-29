#pragma once

#include <vector>
#include "Shape.h"

class Structures {

public:
	Structures() = default;
	Structures(int maxStructs);
	void Draw();
private:
	int const maxStructures{ 20 };
	std::vector<Shape> structuresArray{};
};
