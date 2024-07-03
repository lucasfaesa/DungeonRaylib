#include "LevelGenerator.h"

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
	DrawModel(model2, mapPosition2, 1.0f, WHITE);
}
