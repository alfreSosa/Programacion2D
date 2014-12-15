#include "../include/isometricmap.h"
#include "../lib/rapidxml.hpp"
#include "../include/image.h"

using namespace rapidxml;

IsometricMap::IsometricMap(const String& filename, uint16 firstColId = 0) : Map(filename,firstColId)
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
    //como accedo al segundo!!!
    xml_node<>* tileset = map->first_node("tileset");
    aux = (char *)tileset->first_attribute("firstgid")->value();
    int firstgid = aux.ToInt();
    aux = (char *)tileset->first_attribute("tilewidth")->value();
    int tilewidth = aux.ToInt();
    aux = (char *)tileset->first_attribute("tileheight")->value();
    int tileheight = aux.ToInt();
    //layer
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
    double x, y;
    x = GetImage()->GetHandleX() + tilewidth;
    y = GetImage()->GetHeight() - GetImage()->GetHandleY() - tileheight;
    GetImage()->SetHandle(x, y);
  }
}
