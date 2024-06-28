#pragma once
#include "RectangleF.h"

class Game {

public:
	Game() = default;
	Game(bool initialized);
	void Start();
	void InputRead();
	void Update(float deltaTime);
	void Draw();
	bool IsInitialized() const;
private:
	bool initialized;
	RectangleF rectangle;
};