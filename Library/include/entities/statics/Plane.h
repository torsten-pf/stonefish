//
//  Plane.h
//  Stonefish
//
//  Created by Patryk Cieslak on 1/30/13.
//  Copyright (c) 2013 Patryk Cieslak. All rights reserved.
//

#ifndef __Stonefish_Plane__
#define __Stonefish_Plane__

#include "entities/StaticEntity.h"

namespace sf
{

class Plane : public StaticEntity
{
public:
    Plane(std::string uniqueName, Scalar size, Material m, int lookId = -1);
    
    void getAABB(Vector3& min, Vector3& max);
    StaticEntityType getStaticType();
};

}

#endif
