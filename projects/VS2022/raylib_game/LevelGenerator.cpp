#include "LevelGenerator.h"



LevelGenerator::LevelGenerator()
{
	for (int y = 0; y < cubicmap1.height; y++)
	{
		for (int x = 0; x < cubicmap1.width; x++)
		{
			/*if (mapPixels[y * cubicmap1.width + x].r == 255) {

				//Vector3 min{ x - 1.f * 0.5f, y, mapPosition1.z - 1.f * 0.5f };
				//Vector3 max{ x + 1.f * 0.5f, y + 15.f, mapPosition1.z + 1.f * 0.5f };
				Vector3 min{ x - 1.f * 0.5f, y, x - 1.f * 0.5f };
				Vector3 max{ x + 1.f * 0.5f, y + 15.f, x + 1.f * 0.5f };
				boundingBoxes.emplace_back(BoundingBox{ min, max });
			}*/

			if (mapPixels[y * cubicmap1.width + x].r == 255) {
				// Calculate bounding box corners
				Vector3 min{
					mapPosition1.x + (x - 0.5f),
					mapPosition1.y,
					mapPosition1.z + (y - 0.5f)
				};
				Vector3 max{
					mapPosition1.x + (x + 0.5f),
					mapPosition1.y + 15.0f,
					mapPosition1.z + (y + 0.5f)
				};

				// Create and store bounding box
				boundingBoxes.emplace_back(BoundingBox{ min, max });
			}
		}
	}
}

void LevelGenerator::Start()
{
	Texture2D texture = LoadTexture("../resources/cubicmap_atlas.png");    // Load map texture
	model1.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;    // Set map diffuse texture
	model2.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;    // Set map diffuse texture

	UnloadImage(image1);     // Unload cubesmap image from RAM, already uploaded to VRAM
	UnloadImage(image2);     // Unload cubesmap image from RAM, already uploaded to VRAM
}

void LevelGenerator::Draw()
{
	DrawModel(model1, mapPosition1, 1.0f, WHITE);
	//DrawModel(model2, mapPosition2, 1.0f, WHITE);

	for (BoundingBox& box : boundingBoxes) {
		DrawBoundingBox(box, RED);
	}
	
}

Texture2D& LevelGenerator::GetCubicmap()
{
	return cubicmap1;
}

Color* LevelGenerator::GetMapPixels()
{
	return mapPixels;
}

Vector3& LevelGenerator::GetMapPosition()
{
	return mapPosition1;
}

const std::vector<BoundingBox>& LevelGenerator::GetBoundingBoxes() const
{
	return boundingBoxes;
}
