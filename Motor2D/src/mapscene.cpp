#include "../include/mapscene.h"
#include "../include/map.h"
#include "../include/image.h"
#include "../include/renderer.h"

MapScene::MapScene(Map* map, Image* imageBack, Image* imageFront) : ParallaxScene(imageBack,imageFront)
{
  map = (map) ? map: NULL;
}

const Map * MapScene::GetMap() const 
{
  return map;
}
void MapScene::Update(double elapsed)
{
  ParallaxScene::Update(elapsed, map);
}
void MapScene::RenderAfterBackground() const 
{
  map->Render();
}
