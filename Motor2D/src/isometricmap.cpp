#include "../include/isometricmap.h"
#include "../lib/rapidxml.hpp"
#include "../include/image.h"
#include "../include/math.h"
#include "../include/renderer.h"
#include "../include/isometricscene.h"

using namespace rapidxml;

IsometricMap::IsometricMap(const String& filename, uint16 firstColId) : Map(filename,firstColId)
{
  String contenido = String::Read(filename);
  if (contenido != ""){
    xml_document<> doc;
    //NODO MAPA
    doc.parse<0>((char *)contenido.ToCString());
    xml_node<>* map = doc.first_node("map");
    String aux = (char *)map->first_attribute("width")->value();
    uint16 width = static_cast<uint16>(aux.ToInt());
    aux = (char *)map->first_attribute("height")->value();
    uint16 height = static_cast<uint16>(aux.ToInt());
    aux = (char *)map->first_attribute("tilewidth")->value();
    uint16 tileWidth = static_cast<uint16>(aux.ToInt());
    aux = (char *)map->first_attribute("tileheight")->value();
    uint16 tileHeight = static_cast<uint16>(aux.ToInt());
    //NODO TILESET
    xml_node<>* tileset = map->first_node("tileset");
    aux = (char *)tileset->first_attribute("firstgid")->value();
    int firstgid = aux.ToInt();
    aux = (char *)tileset->first_attribute("tilewidth")->value();
    int tilewidth = aux.ToInt();
    aux = (char *)tileset->first_attribute("tileheight")->value();
    int tileheight = aux.ToInt();
    //layer && next_sibling
    xml_node<>* layer = map->first_node("layer");
    layer = layer->next_sibling("layer");
    xml_node<>* data = layer->first_node("data");
    xml_node<> *tile = data->first_node("tile");
    while (tile != NULL)
    {
      aux = (char *)tile->first_attribute("gid")->value();
      topLayerIds.Add(aux.ToInt() - firstgid);
      tile = tile->next_sibling("tile");
    }
    int32 x, y;
    x = GetImage()->GetHandleX() + tileWidth;
    y = GetImage()->GetHeight() - GetImage()->GetHandleY() - tileHeight;
    GetImage()->SetHandle(x, y);
  }
}

void IsometricMap::GenerateLayerSprites(IsometricScene *scene)
{
  for (uint16 y = 0; y < GetRows(); y++) {
    for (uint16 x = 0; x < GetColumns(); x++) {
      if (GetLayerId(x, y) > -1)
      {
        //se genera sprite
        IsometricSprite *nuevo = scene->CreateSprite(GetImage());
        nuevo->SetFrameRange(GetLayerId(x, y), GetLayerId(x, y));
        if (GetLayerId(x, y) >= GetFirstColId())
          nuevo->SetCollision(Sprite::COLLISION_RECT);
        nuevo->SetPosition(x * GetTileWidth(), y * GetTileHeight(),0);
      }
    }
  }
}

uint16 IsometricMap::GetTileWidth() const 
{
  return Map::GetTileWidth() / 2;
}

void IsometricMap::Render() const 
{
  double screenX = 0.0;
  double screenY = 0.0;

  for (uint16 y = 0; y < GetRows(); y++) {
    for (uint16 x = 0; x < GetColumns(); x++) {
      if (GetLayerId(x, y) >= 0) {
        TransformIsoCoords(x*GetTileWidth(), y*GetTileHeight(), 0, &screenX, &screenY);
        RENDER.DrawImage(GetImage(), screenX, screenY, GetLayerId(x, y));
      }
    }
  }
}
