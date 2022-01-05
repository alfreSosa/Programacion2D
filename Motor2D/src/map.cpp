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
  this->m_filename = filename;
  this->m_firstColId = firstColId;
  m_valid = false;
  String contenido = String::Read(filename);
  if(contenido != ""){
    xml_document<> doc;
    //NODO MAPA
    doc.parse<0>((char *)contenido.ToCString());
    xml_node<>* map = doc.first_node("map");
    String aux = (char *)map->first_attribute("width")->value();
    m_width = static_cast<uint16>(aux.ToInt());
    aux = (char *)map->first_attribute("height")->value();
    m_height = static_cast<uint16>(aux.ToInt());
    aux = (char *)map->first_attribute("tilewidth")->value();
    m_tileWidth = static_cast<uint16>(aux.ToInt());
    aux = (char *)map->first_attribute("tileheight")->value();
    m_tileHeight = static_cast<uint16>(aux.ToInt());
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
    this->m_imageFile = imagenFile.StripDir();
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
      m_tileIds.Add(aux.ToInt() - firstgid);
      tile = tile->next_sibling("tile");
    }
    String ruta = filename.ExtractDir();
    String fichero;
    if (ruta != "")
      fichero = ruta + "/"+ m_imageFile;
    else
      fichero = m_imageFile;
    m_image = RESOURCE.LoadImage(fichero, static_cast<uint16>(imageWidth / tilewidth), static_cast<uint16>(imageHeight / tileheight));
    m_image->SetHandle(x, y);
    if (m_image->IsValid())
      m_valid = true; 
  }
}

void Map::Render() const {
  for ( uint16 y = 0; y < GetRows(); y++ ) {
    for ( uint16 x = 0; x < GetColumns(); x++ ) {
      if ( GetTileId(x, y) >= 0 ) {
        Renderer::Instance().DrawImage(m_image, x*GetTileWidth(), y*GetTileHeight(), GetTileId(x, y));
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
			if ( GetTileId(x, y) >= m_firstColId ) {
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

	if ( x < 0  ||  x >= m_width*m_tileWidth  ||  y >= m_height*m_tileHeight ) return groundY;
	if ( y < 0 ) y = 0;

	// Buscamos el primer tile en esa columna
	for ( int tiley = int(y/m_tileHeight); tiley < m_height; tiley++ ) {
		if ( m_tileIds[tiley*m_width + int(x/m_tileWidth)] >= 0 ) {
			groundY = tiley*m_tileHeight;
			break;
		}
	}
	return groundY;
}
