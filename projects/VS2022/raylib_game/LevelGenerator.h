#pragma once


#include "raylib.h"
#include <vector>

class LevelGenerator {

public:
	LevelGenerator();
	void Start();
	void Draw();
	Texture2D& GetCubicmap();
	Color* GetMapPixels();
	Vector3& GetMapPosition();

private:
	Image image1 = LoadImage("../resources/cubicmap.png");
	Texture2D cubicmap1 = LoadTextureFromImage(image1);

	Mesh mesh1 = GenMeshCubicmap(image1, Vector3{ 1.0f, 15.0f, 1.0f });
	Model model1 = LoadModelFromMesh(mesh1);

	Image image2 = LoadImage("../resources/cubicmap2.png");
	Texture2D cubicmap2 = LoadTextureFromImage(image2);

	Mesh mesh2 = GenMeshCubicmapOnlyWhites(image2, Vector3{ 1.0f, 1.0f, 1.0f });
	Model model2 = LoadModelFromMesh(mesh2);

	Color* mapPixels = LoadImageColors(image1);

	Texture2D texture{};    // Load map texture
	
	Vector3 mapPosition1 = { -16.0f, 0.f, -8.0f };

	Vector3 mapPosition2 = { -16.0f, 3.f, -8.0f };


	std::vector<BoundingBox> boundingBoxes;
	
};