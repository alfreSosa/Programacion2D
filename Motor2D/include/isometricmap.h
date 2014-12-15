#ifndef _ISOMETRICMAP_H
#define _ISOMETRICMAP_H

#include "types.h"
#include "string.h"
#include "array.h"
#include "map.h"

class IsometricScene;

class IsometricMap : public Map {
public:
  IsometricMap(const String& filename, uint16 firstColId = 0);
  virtual void GenerateLayerSprites(IsometricScene* scene);
  virtual uint16 GetTileWidth() const;
  virtual void Render() const;
  virtual int32 GetLayerId(uint16 column, uint16 row);
private:
  Array<int32> topLayerIds;
};
#endif