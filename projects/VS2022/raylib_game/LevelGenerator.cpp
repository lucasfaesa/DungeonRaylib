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

	UnloadImage(baseScenery);

	for (int i = 0; i < platformsModels.size(); i++)
	{
		platformsModels[i].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = platformsTexture;
		UnloadImage(platformsImages[i]);
	}
}

void LevelGenerator::Draw()
{
	DrawModel(baseSceneryModel, baseSceneryPosition, 1.0f, WHITE);

	for (int i = 0; i < platformsModels.size(); i++)
	{
		DrawModel(platformsModels[i], Vector3{ baseSceneryPosition.x, (float)i, baseSceneryPosition.z }, 1.0f, WHITE);
	}

	//for (BoundingBox& box : levelBoundingBoxes) {		DrawBoundingBox(box, RED);	}
	
}

const std::vector<BoundingBox>& LevelGenerator::GetBoundingBoxes() const
{
	return levelBoundingBoxes;
}

void LevelGenerator::InitializePlatformsArray()
{
	for (int i = 1; i <= platformsImageQty; ++i) {
		std::string imagePath = "../resources/platform" + std::to_string(i) + "f.png";

		Image image = LoadImage(imagePath.c_str());

		if (image.width == 0 || image.height == 0) {
			// The image is invalid, possibly because the file does not exist
			std::cout << "Failed to load image: " << imagePath << std::endl;
			continue;  // Skip to the next iteration of the loop
		}

		Texture texture = LoadTextureFromImage(image);
		Mesh mesh = GenMeshCubicmapWithoutFloorAndCeiling(image, Vector3{ 1.0f, 1.0f, 1.0f });
		Model model = LoadModelFromMesh(mesh);
		Color* pixels = LoadImageColors(image);

		platformsImages.emplace_back(image);
		platformsTextures.emplace_back(texture);
		platformsMeshes.emplace_back(mesh);
		platformsModels.emplace_back(model);
		platformsPixels.emplace_back(pixels);
	}
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
