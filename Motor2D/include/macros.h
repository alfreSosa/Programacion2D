#ifndef _MACROS_H
#define _MACROS_H

#define RENDER Renderer::Instance()
#define SCREEN Screen::Instance()
#define RESOURCE ResourceManager::Instance()
//Macro para ejercicio4A
#define VEL(data) reinterpret_cast<Velocidades *>(data)
#define DOUBLE(x) static_cast<double>(x)

#endif