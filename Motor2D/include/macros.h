#ifndef _MACROS_H
#define _MACROS_H

//SIMPLIFICACION LLAMADAS SINGLETON
#define RENDER Renderer::Instance()
#define SCREEN Screen::Instance()
#define RESOURCE ResourceManager::Instance()

#define VEL(data) reinterpret_cast<Velocidades *>(data) //Macro para ejercicio4A

//CONVERSIONES DE TIPO
#define DOUBLE(x) static_cast<double>(x)
#define INT(x) static_cast<int>(x)
#define CHARTOUI32(x) static_cast<uint32>(x)

#endif