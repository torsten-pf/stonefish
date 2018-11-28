//
//  ColorCamera.h
//  Stonefish
//
//  Created by Patryk Cieslak on 4/5/18.
//  Copyright (c) 2018 Patryk Cieslak. All rights reserved.
//

#ifndef __Stonefish_ColorCamera__
#define __Stonefish_ColorCamera__

#include <functional>
#include "graphics/OpenGLRealCamera.h"
#include "sensors/vision/Camera.h"

namespace sf
{

class ColorCamera : public Camera
{
public:
    ColorCamera(std::string uniqueName, uint32_t resX, uint32_t resY, Scalar horizFOVDeg, Scalar frequency = Scalar(-1), uint32_t spp = 1, bool ao = true);
    virtual ~ColorCamera();
    
    void InternalUpdate(Scalar dt);
    void SetupCamera(const Vector3& eye, const Vector3& dir, const Vector3& up);
    void InstallNewDataHandler(std::function<void(ColorCamera*)> callback);
    void NewDataReady();
    uint8_t* getDataPointer(); //Should be only used in the callback
    
private:
    OpenGLRealCamera* glCamera;
    uint8_t* imageData;
    std::function<void(ColorCamera*)> newDataCallback;
};
    
}

#endif
