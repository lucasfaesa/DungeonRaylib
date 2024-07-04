#include "LevelGenerator.h"



LevelGenerator::LevelGenerator()
{
	InitializePlatformsArray();

	ComputeBaseStructureCollisions();
	ComputePlatformsCollisions();
}

void LevelGenerator::Start()
{
	baseSceneryModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = baseSceneryTexture;    // Set map diffuse texture
	platformsModels[0].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = baseSceneryTexture;    // Set map diffuse texture

	UnloadImage(baseScenery);     // Unload cubesmap image from RAM, already uploaded to VRAM
	UnloadImage(platformsImages[0]);     // Unload cubesmap image from RAM, already uploaded to VRAM
}

void LevelGenerator::Draw()
{
	DrawModel(baseSceneryModel, baseSceneryPosition, 1.0f, WHITE);
	DrawModel(platformsModels[0], Vector3{baseSceneryPosition.x, 0.f, baseSceneryPosition.z}, 1.0f, WHITE);

	for (BoundingBox& box : levelBoundingBoxes) {
		DrawBoundingBox(box, RED);
	}
	
}

const std::vector<BoundingBox>& LevelGenerator::GetBoundingBoxes() const
{
	return levelBoundingBoxes;
}

void LevelGenerator::InitializePlatformsArray()
{
	platformsImages.emplace_back(LoadImage("../resources/platform1f.png"));
	platformsTextures.emplace_back(LoadTextureFromImage(platformsImages[platformsImages.size() - 1]));
	platformsMeshes.emplace_back(GenMeshCubicmapWithoutFloorAndCeiling(platformsImages[platformsImages.size() - 1], Vector3{ 1.0f, 1.0f, 1.0f }));
	platformsModels.emplace_back(LoadModelFromMesh(platformsMeshes[platformsMeshes.size() - 1]));
	platformsPixels.emplace_back(LoadImageColors(platformsImages[platformsImages.size() - 1]));
}

void LevelGenerator::ComputeBaseStructureCollisions()
{
	for (int y = 0; y < baseSceneryCubicmap.height; y++)
	{
		for (int x = 0; x < baseSceneryCubicmap.width; x++)
		{
			//creating collisions for the strucuture, white pixels
			if (baseSceneryPixels[y * baseSceneryCubicmap.width + x].r == 255) {
				// Calculate bounding box corners
				Vector3 min{ baseSceneryPosition.x + (x - 0.5f), baseSceneryPosition.y, baseSceneryPosition.z + (y - 0.5f) };
				Vector3 max{ baseSceneryPosition.x + (x + 0.5f), baseSceneryPosition.y + baseSceneryCubeSize.y, baseSceneryPosition.z + (y + 0.5f) };

				levelBoundingBoxes.emplace_back(BoundingBox{ min, max });
			}

			//creating collisions for the ground, black pixels
			// TODO remove this later, make the ground a big plane
			if (baseSceneryPixels[y * baseSceneryCubicmap.width + x].r == 0) {
				Vector3 min{ baseSceneryPosition.x + (x - 0.5f), baseSceneryPosition.y - 1.0f, baseSceneryPosition.z + (y - 0.5f) };
				Vector3 max{ baseSceneryPosition.x + (x + 0.5f), baseSceneryPosition.y, baseSceneryPosition.z + (y + 0.5f) };

				levelBoundingBoxes.emplace_back(BoundingBox{ min, max });
			}
		}
	}
}

void LevelGenerator::ComputePlatformsCollisions()
{
	for (int t = 0; t < platformsTextures.size(); t++)
	{
		for (int y = 0; y < platformsTextures[t].height; y++)
		{
			for (int x = 0; x < platformsTextures[t].width; x++)
			{
				//creating collisions for the platoform, non transparent pixels only
				if (platformsPixels[t][y * platformsTextures[t].width + x].a > 0) {
					// Calculate bounding box corners
																	//"t", the heights adds the iteration value for every object in the platforms array
																	//so for the first item in the array, the box will be at height 0f, for the
																	//second 1f, and so on
					Vector3 min{ baseSceneryPosition.x + (x - 0.5f),  t ,	baseSceneryPosition.z + (y - 0.5f) };
					Vector3 max{ baseSceneryPosition.x + (x + 0.5f),  t + (1.f),	baseSceneryPosition.z + (y + 0.5f) };

					levelBoundingBoxes.emplace_back(BoundingBox{ min, max });
				}
			}
		}
	}	
}
