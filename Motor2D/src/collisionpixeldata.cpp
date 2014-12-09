#include "../include/collisionpixeldata.h"
#include "../lib/stb_image.h"

CollisionPixelData::CollisionPixelData(const String& filename)
{
  int x, y,comp;
  this->filename = filename;
  width = height = 0;
  data = NULL;
  uint8 *buffer = stbi_load(filename.ToCString(), &x, &y, &comp, 4);
  if (buffer)
  {
    width= static_cast<uint16>(x);
    height = static_cast<uint16>(y);

    data = (bool *) malloc(width * height * sizeof(bool));
    if (data)
    {
      for (uint32 i = 0; i < height; i++)
        for (uint32 j = 0; j < width; j++)
          data[i * width + j] = (buffer[(i * width + j) * 4 + 3] == 0) ? false : true;
    }
    stbi_image_free(buffer);
  }
}
CollisionPixelData::~CollisionPixelData()
{
  if (data)
    free(data);
}
bool CollisionPixelData::IsValid() const
{
  return (data) ? true : false;
}