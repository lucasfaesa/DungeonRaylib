#pragma once

#include <vector>
#include "Shape.h"
#include "RectangleF.h"

class Structures {

public:
	Structures() = default;
	Structures(int maxStructs);
	void Update(float deltaTime);
	~Structures();
	void Draw();
	std::vector<RectangleF *>& GetRectangles();
private:
	int const maxStructures{ 20 };
	std::vector<RectangleF *> rectanglesArray{};

	RectangleF ground{ Vector3{ 0.f, /*-0.2f*/ -10.f , 0.f }, Vector3{ 100.0f, 0.4f, 100.0f }, BLUE , Layers::Layer::GROUND };

	RectangleF testBox{ Vector3{ 4.f, 1.f, 0.f }, Vector3{ 0.8f, 2.f, 0.8f }, ORANGE };
};
