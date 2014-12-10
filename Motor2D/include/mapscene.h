#ifndef _MAPSCENE_H
#define _MAPSCENE_H

#include "types.h"
#include "string.h"
#include "parallaxscene.h"

class Map;
class Image;

class MapScene : public ParallaxScene {
public:
  MapScene(Map* map, Image* imageBack = 0, Image* imageFront = 0);
  virtual const Map* GetMap() const;
  virtual void Update(double elapsed);
protected:
  virtual void RenderAfterBackground() const;
private:
  Map* map;
};

#endif