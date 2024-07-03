#pragma once

#include "raylib.h"

class LevelGenerator {

public:
	LevelGenerator() = default;
	void Start();
	void Draw();

private:
	Image image = LoadImage("../resources/cubicmap.png");
	Texture2D cubicmap = LoadTextureFromImage(image);

	Mesh mesh = GenMeshCubicmap(image, Vector3{ 1.0f, 2.0f, 1.0f });
	Model model = LoadModelFromMesh(mesh);

	Texture2D texture{};    // Load map texture
	
	Vector3 mapPosition = { -16.0f, 2.f, -8.0f };



	
};