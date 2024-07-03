#include "LevelGenerator.h"

void LevelGenerator::Start()
{
	

	Texture2D texture = LoadTexture("../resources/cubicmap_atlas.png");    // Load map texture
	model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;    // Set map diffuse texture

	UnloadImage(image);     // Unload cubesmap image from RAM, already uploaded to VRAM
}

void LevelGenerator::Draw()
{
	DrawModel(model, mapPosition, 1.0f, RED);
}
