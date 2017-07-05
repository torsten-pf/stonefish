//
//  FallingTestManager.cpp
//  Stonefish
//
//  Created by Patryk Cieslak on 04/03/2014.
//  Copyright (c) 2014-2017 Patryk Cieslak. All rights reserved.
//

#include "FallingTestManager.h"

#include "FallingTestApp.h"
#include "Plane.h"
#include "Obstacle.h"
#include "Polyhedron.h"
#include "Box.h"
#include "Sphere.h"
#include "Torus.h"
#include "Cylinder.h"
#include "OpenGLContent.h"
#include "SystemUtil.hpp"
#include "FakeIMU.h"
#include "Trajectory.h"
#include "Manipulator.h"
#include "OpenGLSun.h"
#include "Light.h"
#include "Camera.h"

FallingTestManager::FallingTestManager(btScalar stepsPerSecond) : SimulationManager(SimulationType::TERRESTIAL, UnitSystems::MKS, stepsPerSecond, DANTZIG, STANDARD)
{
}

void FallingTestManager::BuildScenario()
{
	OpenGLPipeline::getInstance()->setRenderingEffects(true, false, false);
    OpenGLPipeline::getInstance()->setVisibleHelpers(true, false, false, false, true, true);
    setICSolverParams(false);
	
    ///////MATERIALS////////
    getMaterialManager()->CreateMaterial("Steel", 1000.0, 0.5);
    getMaterialManager()->SetMaterialsInteraction("Ground", "Ground", 0.5, 0.3);
    getMaterialManager()->SetMaterialsInteraction("Ground", "Steel", 0.5, 0.3);
    getMaterialManager()->SetMaterialsInteraction("Steel", "Steel", 0.5, 0.3);
    
    ///////LOOKS///////////
    int color = OpenGLContent::getInstance()->CreateSimpleLook(glm::vec3(1.f, 0.5f, 0.1f), 0.1f, 0.0f);
    
	////////OBJECTS
	Sphere* vehicle = new Sphere("Vehicle", 1., getMaterialManager()->getMaterial("Steel"), color);
	AddSolidEntity(vehicle, btTransform(btQuaternion::getIdentity(), btVector3(0,0,1)));
	
    Sphere* sphere = new Sphere("Sphere", 0.1f, getMaterialManager()->getMaterial("Steel"), color);
	Box* link1 = new Box("Link1", btVector3(0.5,0.1,0.1), getMaterialManager()->getMaterial("Steel"), color);
	Box* link2 = new Box("Link2", btVector3(0.5,0.1,0.1), getMaterialManager()->getMaterial("Steel"), color);
	Box* link3 = new Box("Link3", btVector3(0.5,0.1,0.1), getMaterialManager()->getMaterial("Steel"), color);
	
	Manipulator* manip = new Manipulator("Arm", 3, sphere, btTransform(btQuaternion::btQuaternion(btVector3(1,0,0), M_PI_2), btVector3(0,0,5)), vehicle->getRigidBody());
	manip->AddRotLinkDH(link1, btTransform(btQuaternion::getIdentity(), btVector3(-0.25f,0,0)), 0, 0.6f, 0);
	manip->AddRotLinkDH(link2, btTransform(btQuaternion::getIdentity(), btVector3(-0.25f,0,0)), 0, 0.6f, 0);
	manip->AddRotLinkDH(link3, btTransform(btQuaternion::getIdentity(), btVector3(-0.25f,0,0)), 0, 0.6f, 0);
	AddEntity(manip);
	
    /*for(int i=0; i<10; i++)
    {
        color = CreateOpaqueLook(glm::vec3(i/10.f + 0.2f, 1.0f - i/10.f * 0.8f, 0.1f), 0.4f, 0.1f, 1.2f);
        BoxEntity* box = new BoxEntity("Box" + std::to_string(i), btVector3(0.5f, 0.5f, 0.5f), getMaterialManager()->getMaterial("Steel"), color);
        box->setRenderable(true);
        AddSolidEntity(box, btTransform(btQuaternion(UnitSystem::Angle(true, i * 25.f), 0., 0.), btVector3(sinf(i * M_PI/10.f) * 5.f, -i * 1.f, 3.f + i * 0.3f)));
    }*/
    
    ////////SENSORS AND ACTUATORS
	FakeIMU* imu = new FakeIMU("IMU", vehicle, btTransform::getIdentity());
	AddSensor(imu);
	
    Light* omni = new Light("Omni", btVector3(-2,2,2), OpenGLLight::ColorFromTemperature(4500, 1000000));
    AddActuator(omni);
    //Light* spot = new Light("Spot", btVector3(5.f, 5.f, 5.f), btVector3(-1.f,-1.f,-1.f), 30.f, OpenGLLight::ColorFromTemperature(4500, 1000000));
    //AddActuator(spot);
    //Camera* cam = new Camera("Camera", btVector3(-10,0,1), btVector3(0,0,0), btVector3(0,0,1.), 0, 0, FallingTestApp::getApp()->getWindowWidth()/3, FallingTestApp::getApp()->getWindowHeight()/3, 60.f);
    //AddSensor(cam);
}