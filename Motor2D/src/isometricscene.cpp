#include "../include/isometricscene.h"
#include "../include/isometricmap.h"
#include "../include/image.h"

IsometricScene::IsometricScene(IsometricMap *map, Image *imageBack, Image* imageFront) : MapScene(map, imageBack, imageFront)
{
  map->GenerateLayerSprites(this);
}

IsometricSprite* IsometricScene::CreateSprite(Image *image, Layer layer)
{
  IsometricSprite* spr = new IsometricSprite(image);
  AddSprite(spr, layer);
  return spr;
}
void IsometricScene::Update(double elapsed)
{
  MapScene::Update(elapsed);
  GetSprites(LAYER_BACK).Sort(&CompareSprites);
  GetSprites(LAYER_MIDDLE).Sort(&CompareSprites);
  GetSprites(LAYER_FRONT).Sort(&CompareSprites);
}

bool IsometricScene::CompareSprites(Sprite*& first, Sprite*& second)
{
  return (first->GetScreenY() <= second->GetScreenY()) ? true : false;
}