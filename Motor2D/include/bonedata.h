#ifndef UGINE_BONEDATA_H
#define UGINE_BONEDATA_H

#include "array.h"
#include "frame.h"
#include "string.h"
#include "types.h"

//Contiene los datos del XML
//Estos datos se cargan sobre el objeto bone que si pertenece al motor, estas clases son de apollo
class BoneData {
public:
    BoneData() : id(""), parentName(""), imageFilename(""), pivotx(0), pivoty(0), handlex(0), handley(0) {}
    BoneData(const String& id, const String& parentName, const String& imageFilename, double pivotx, double pivoty, double handlex, double handley);

    virtual const String& GetId() const { return id; }
    virtual const String& GetParentName() const { return parentName; }
    virtual const String& GetImageFilename() const { return imageFilename; }
    virtual double GetPivotX() const { return pivotx; }
    virtual double GetPivotY() const { return pivoty; }
    virtual double GetHandleX() const { return handlex; }
    virtual double GetHandleY() const { return handley; }

    virtual void AddFrame(const Frame& frame) { frames.Add(frame); } //Construye el array de frames
    virtual const Array<Frame>& GetFrames() const { return frames; }
private:
    String id;
    String parentName;
    String imageFilename;
    double pivotx, pivoty;
    double handlex, handley;
    Array<Frame> frames;
};

inline BoneData::BoneData(const String& id, const String& parentName, const String& imageFilename, double pivotx, double pivoty, double handlex, double handley)
    : id(id),
      parentName(parentName),
      imageFilename(imageFilename),
      pivotx(pivotx),
      pivoty(pivoty),
      handlex(handlex),
      handley(handley) {}

#endif
