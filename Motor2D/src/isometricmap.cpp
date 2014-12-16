#include "../include/isometricmap.h"
#include "../lib/rapidxml.hpp"
#include "../include/image.h"
#include "../include/math.h"
#include "../include/renderer.h"
#include "../include/isometricscene.h"

using namespace rapidxml;

IsometricMap::IsometricMap(const String& filename, uint16 firstColId) : Map(filename,firstColId)
{
  //clase padre, lee el layer 1
  //esta clase lee el segundo layer
  String contenido = String::Read(filename);
  if (contenido != ""){
    xml_document<> doc;
    //NODO MAPA
    doc.parse<0>((char *)contenido.ToCString());
    xml_node<>* map = doc.first_node("map");
    String aux;
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
    //Compresion no soportada
    if (data->first_attribute("compression")){ 
      Map::SetValid(false);
      return;
    }
    if (data->first_attribute("encoding")){
      Map::SetValid(false);
      return;
    }

    xml_node<> *tile = data->first_node("tile");
    while (tile != NULL)
    {
      aux = (char *)tile->first_attribute("gid")->value();
      topLayerIds.Add(aux.ToInt() - firstgid);
      tile = tile->next_sibling("tile");
    }
    if (GetImage() == NULL || !GetImage()->IsValid())
    {
      Map::SetValid(false);
      return;
    }
    uint32 x, y;
    x = GetImage()->GetHandleX() + tilewidth;
    y = GetImage()->GetHeight() - GetImage()->GetHandleY() - tileheight;
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
        if (GetLayerId(x, y) > GetFirstColId())
          nuevo->SetCollision(Sprite::COLLISION_RECT);
        //nuevo->SetPosition(x * Map::GetTileWidth(), y * GetTileHeight()); me falta Z otra vez
        //poner sus coordenadas de la escena, fila y columna del tile, por el ancho y alto del tile respectivamente
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
  double screenX, screenY;
  for (uint16 y = 0; y < GetRows(); y++) {
    for (uint16 x = 0; x < GetColumns(); x++) {
      if (GetLayerId(x, y) >= 0) {
        //TransformIsoCoords(x, y, z, &screenX, &screenY);de donde saco la z?
        RENDER.DrawImage(GetImage(), screenX*GetTileWidth(), screenY*GetTileHeight(), GetLayerId(x, y));
      }
    }
  }
}
