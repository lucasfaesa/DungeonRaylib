#pragma once


#include "raylib.h"
#include <vector>
#include <string>
#include <iostream>

class LevelGenerator {

public:
	LevelGenerator();
	void Start();
	void Draw();
	const std::vector<BoundingBox>& GetBoundingBoxes() const;

private:

	void InitializePlatformsArray();
	void ComputeBaseStructureCollisions();
	void ComputePlatformsCollisions();

private:

	//walls, columns...
	Image baseScenery = LoadImage("../resources/baseScenery.png");
	Texture2D baseSceneryCubicmap = LoadTextureFromImage(baseScenery);

	Vector3 baseSceneryCubeSize{ 1.0f, 15.0f, 1.0f };

	Mesh baseSceneryMesh = GenMeshCubicmap(baseScenery, baseSceneryCubeSize);
	Model baseSceneryModel = LoadModelFromMesh(baseSceneryMesh);

	Color* baseSceneryPixels = LoadImageColors(baseScenery);

	Texture2D baseSceneryTexture = LoadTexture("../resources/cubicmap_atlas2.png");
	Texture2D platformsTexture = LoadTexture("../resources/cubicmap_atlas3.png");

	Vector3 baseSceneryPosition = { -baseSceneryCubicmap.width * 0.5f, 0.f, -baseSceneryCubicmap.height * 0.5f };


	static constexpr int platformsImageQty = 13;

	//platforms
	//TODO create a data structure for this?
	std::vector<Image> platformsImages;
	std::vector<Texture2D> platformsTextures;
	std::vector<Mesh> platformsMeshes;
	std::vector<Model> platformsModels;
	std::vector<Color*> platformsPixels;


	std::vector<BoundingBox> levelBoundingBoxes;
	
};