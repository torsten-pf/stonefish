//
//  ScrewConstraint.h
//  Stonefish
//
//  Created by Patryk Cieslak on 12/04/2018.
//  Copyright (c) 2018 Patryk Cieslak. All rights reserved.
//

#ifndef __Stonefish_ScrewConstraint__
#define __Stonefish_ScrewConstraint__

#include <limits>
#include <cmath>
#include <BulletDynamics/ConstraintSolver/btSliderConstraint.h>
#include "StonefishCommon.h"

namespace sf
{

class ScrewConstraint : public btSliderConstraint
{
public: 
      ScrewConstraint(btRigidBody &_rbA, btRigidBody &_rbB, const Transform &_frameInA, const Transform &_frameInB, bool _useLinearReferenceFrameA)
          : btSliderConstraint(_rbA, _rbB, _frameInA, _frameInB, _useLinearReferenceFrameA), threadPitch(1.0) {}

      ScrewConstraint(btRigidBody &_rbB, const Transform &_frameInB, bool _useLinearReferenceFrameA)
          : btSliderConstraint(_rbB, _frameInB, _useLinearReferenceFrameA), threadPitch(1.0) {}

      virtual void getInfo1(btConstraintInfo1 *_info)
      {
        this->_getInfo1NonVirtual(_info);
      }

      virtual void getInfo2(btConstraintInfo2 *_info)
      {
        this->_getInfo2NonVirtual(_info,
                                  m_rbA.getCenterOfMassTransform(),
                                  m_rbB.getCenterOfMassTransform(),
                                  m_rbA.getLinearVelocity(),
                                  m_rbB.getLinearVelocity(),
                                  m_rbA.getInvMass(), m_rbB.getInvMass());
      }

      void _getInfo1NonVirtual(btConstraintInfo1* info);
      
      void _getInfo2NonVirtual(btConstraintInfo2* info, const Transform& transA, const Transform& transB, const Vector3& linVelA, const Vector3& linVelB, Scalar rbAinvMass, Scalar rbBinvMass);

      Scalar getLinearPosition();
      Scalar getAngularPosition();

      // needed non-const version for SetForce
      btRigidBody& getRigidBodyA();
      btRigidBody& getRigidBodyB();

      virtual void setThreadPitch(double _threadPitch)
      {
        this->threadPitch = -_threadPitch;
      }

      virtual double getThreadPitch() const
      {
        return -this->threadPitch;
      }

private: 
    double threadPitch;
};

}
    
#endif
