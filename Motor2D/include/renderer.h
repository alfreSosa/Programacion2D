#ifndef UGINE_RENDERER_H
#define UGINE_RENDERER_H

#include "string.h"
#include "types.h"
#include <math.h>

class Font;
class Image;

class Renderer {
public:
    enum BlendMode {
		SOLID,
		ALPHA,
		MULTIPLICATIVE,
		ADDITIVE
	};

    static const Renderer& Instance() { if ( !renderer ) renderer = new Renderer(); return *renderer; }

    virtual void SetBlendMode(BlendMode blendMode) const;
    virtual void SetColor(double r, double g, double b, double a) const;
    virtual void SetOrigin(double x, double y) const;
    virtual void Clear(double r = 0.0, double g = 0.0, double b = 0.0f) const;
    virtual void DrawPoint(double x, double y) const;
    virtual void DrawLine(double x1, double y1, double x2, double y2) const;
    virtual void DrawRect(double x, double y, double width, double height) const;
    virtual void DrawEllipse(double x, double y, double xradius, double yradius) const;
    virtual void DrawImage(const Image* image, double x, double y, uint32 frame = 0, double width = 0.0f, double height = 0.0f, double ang = 0) const;
    virtual uint32 GenImage(uint8* buffer, uint16 width, uint16 height) const;
    virtual void BindImage(uint32 glhandle) const;
    virtual void DeleteImage(uint32 glhandle) const;
    virtual void PushMatrix() const;
    virtual void PopMatrix() const;
    virtual void TranslatedMatrix(double x, double y, double z) const;
    virtual void RotateMatrix(double angle, double x, double y, double z) const;
    virtual void TexImage2D(uint32 gltex, uint16 width, uint16 height,const uint8 *buffer) const;
    virtual void DrawTiledImage(const Image* image, double x, double y, double width, double height, double offsetx = 0, double offsety = 0) const;
    virtual void DrawText(const Font* font, const String& text, double x, double y) const;
protected:
    Renderer() {}
private:
    static Renderer* renderer;
};

#endif
