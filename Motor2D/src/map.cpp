#include "../include/map.h"
#include "../include/rectcollision.h"
#include "../include/collision.h"
#include "../include/image.h"
#include "../include/renderer.h"
#include "../include/resourcemanager.h"
#include "../include/string.h"
#include "../lib/rapidxml.hpp"
#include <limits.h>

using namespace rapidxml;

Map::Map(const String &filename, uint16 firstColId) {
	// TAREA: Implementar constructor
  this->filename = filename;
  this->firstColId = firstColId;
  valid = false;
  String contenido = String::Read(filename);
  if(contenido != ""){
    xml_document<> doc;
    //NODO MAPA
    doc.parse<0>((char *)contenido.ToCString());
    xml_node<>* map = doc.first_node("map");
    String aux = (char *)map->first_attribute("width")->value();
    width = static_cast<uint16>(aux.ToInt());
    aux = (char *)map->first_attribute("height")->value();
    height = static_cast<uint16>(aux.ToInt());
    aux = (char *)map->first_attribute("tilewidth")->value();
    tileWidth = static_cast<uint16>(aux.ToInt());
    aux = (char *)map->first_attribute("tileheight")->value();
    tileHeight = static_cast<uint16>(aux.ToInt());
    //NODO TILESET
    xml_node<>* tileset = map->first_node("tileset");
    aux = (char *)tileset->first_attribute("firstgid")->value();
    int firstgid = aux.ToInt();
    aux = (char *)tileset->first_attribute("tilewidth")->value();
    int tilewidth = aux.ToInt();
    aux = (char *)tileset->first_attribute("tileheight")->value();
    int tileheight = aux.ToInt();
    //tileoffset
    xml_node<>* tileoffset = NULL;
    int x = 0, y = 0 ;
    tileoffset = tileset->first_node("tileoffset");
    if(tileoffset){
      aux = (char *)tileoffset->first_attribute("x")->value();
      x = aux.ToInt();
      aux = (char *)tileoffset->first_attribute("y")->value();
      y = aux.ToInt();
    }
    //image
    xml_node<>* imagen = tileset->first_node("image");
    String imagenFile = (char *)imagen->first_attribute("source")->value();
    this->imageFile = imagenFile.StripDir();
    //this->imageFile = ruta + imagenFile;
    int imageWidth, imageHeight;
    aux = (char *)imagen->first_attribute("width")->value();
    imageWidth = aux.ToInt();
    aux = (char *)imagen->first_attribute("height")->value();
    imageHeight = aux.ToInt();
    //layer
    xml_node<>* layer = map->first_node("layer");
    xml_node<>* data = layer->first_node("data");
    //Compresion no soportada
    if (data->first_attribute("compression")) return;
    if (data->first_attribute("encoding")) return;

    xml_node<> *tile = data->first_node("tile");
    while (tile != NULL)
    {
      aux = (char *)tile->first_attribute("gid")->value();
      tileIds.Add(aux.ToInt() - firstgid);
      tile = tile->next_sibling("tile");
    }
    String ruta = filename.ExtractDir();
    String fichero;
    if (ruta != "")
      fichero = ruta + "/"+ imageFile;
    else
      fichero = imageFile;
    image = RESOURCE.LoadImage(fichero, imageWidth / tileWidth, imageHeight / tileHeight);
    image->SetHandle(x, y);
    if (image->IsValid())
      valid = true; 
  }
}

void Map::Render() const {
  for ( uint16 y = 0; y < GetRows(); y++ ) {
    for ( uint16 x = 0; x < GetColumns(); x++ ) {
      if ( GetTileId(x, y) >= 0 ) {
        Renderer::Instance().DrawImage(image, x*GetTileWidth(), y*GetTileHeight(), GetTileId(x, y));
      }
    }
  }
}

bool Map::CheckCollision(const Collision* collision) const {
	// Creamos caja de colisiones
	double boxX = 0, boxY = 0, boxWidth = GetTileWidth(), boxHeight = GetTileHeight();
	RectCollision boxCol(&boxX, &boxY, &boxWidth, &boxHeight);
	
	// Comprobamos colision con cada tile
	for ( uint16 y = 0; y < GetRows(); y++ ) {
		for ( uint16 x = 0; x < GetColumns(); x++ ) {
			if ( GetTileId(x, y) >= firstColId ) {
				boxX = x * GetTileWidth();
				boxY = y * GetTileHeight();

				if ( collision->DoesCollide(&boxCol) )
					return true;
			}
		}
	}

	return false;
}

double Map::GetGroundY(double x, double y) const {
	double groundY = UINT_MAX;

	if ( x < 0  ||  x >= width*tileWidth  ||  y >= height*tileHeight ) return groundY;
	if ( y < 0 ) y = 0;

	// Buscamos el primer tile en esa columna
	for ( int tiley = int(y/tileHeight); tiley < height; tiley++ ) {
		if ( tileIds[tiley*width + int(x/tileWidth)] >= 0 ) {
			groundY = tiley*tileHeight;
			break;
		}
	}
	return groundY;
}
