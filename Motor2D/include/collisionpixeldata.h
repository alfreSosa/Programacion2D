#ifndef _COLLISIONPIXELDATA_H
#define _COLLISIONPIXELDATA_H

#include "types.h"
#include "string.h"

class CollisionPixelData {
public:
  CollisionPixelData(const String& filename);
  virtual ~CollisionPixelData();
  virtual bool IsValid() const;
  virtual const String& GetFilename() const { return filename; }
  virtual uint16 GetWidth() const { return width; }
  virtual uint16 GetHeight() const { return height; }
  virtual bool GetData(uint32 x, uint32 y) const { return data[y * width + x]; }
private:
  String filename;
  uint16 width, height;
  bool* data;
};
#endif