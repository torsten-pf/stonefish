//
//  OpenGLDebugDrawer.h
//  Stonefish
//
//  Created by Patryk Cieslak on 28/06/2014.
//  Copyright (c) 2014 Patryk Cieslak. All rights reserved.
//

#ifndef __Stonefish_OpenGLDebugDrawer__
#define __Stonefish_OpenGLDebugDrawer__

#include <LinearMath/btIDebugDraw.h>
#include "graphics/OpenGLPipeline.h"

namespace sf
{

class OpenGLDebugDrawer : public btIDebugDraw
{
public:
    OpenGLDebugDrawer(int debugMode, bool zUp);
    
    void drawLine(const Vector3& from,const Vector3& to,const Vector3& color);
    void drawLine(const Vector3& from,const Vector3& to, const Vector3& fromColor, const Vector3& toColor);
    void drawContactPoint(const Vector3& PointOnB, const Vector3& normalOnB, Scalar distance, int lifeTime, const Vector3& color);
	void draw3dText(const Vector3& location, const char* textString);
    void reportErrorWarning(const char* warningString);
	
	void setDebugMode(int debugMode);
	int	getDebugMode() const;
    
private:
    int mode;
	bool zAxisUp;
};

}

#endif
