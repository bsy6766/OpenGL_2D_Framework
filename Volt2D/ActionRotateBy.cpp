//
//  ActionRotateBy.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 12/8/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "ActionRotateBy.h"

using namespace Volt2D;

ActionRotateBy::ActionRotateBy():
ActionObject(),
rotatingAngle(0),
previousAngle(0),
movedAngle(0),
axis(glm::vec3())
{
//    cout << "[SYSTEM::INFO] Creating ActionRotateBy" << endl;
}

ActionRotateBy::~ActionRotateBy(){
//    cout << "[SYSTEM::INFO] Releasing ActionRotateBy" << endl;
}

ActionRotateBy* ActionRotateBy::createRotateBy(double duration, float angle, glm::vec3 axis){
    ActionRotateBy* newActionMoveBy = new ActionRotateBy();
    newActionMoveBy->initRotateBy(angle, duration, axis);
    return newActionMoveBy;
}

void ActionRotateBy::initRotateBy(float angle, double duration, glm::vec3 axis){
    this->duration = duration;
    this->rotatingAngle = angle;
    this->movedAngle = 0;
    this->previousAngle = 0;
    this->axis = axis;
}

void ActionRotateBy::updateAction(double& remainedTime){
    if(!alive)
        return;
    
    if(duration == 0){
        instantUpdate();
    }
    else{
        intervalUpdate(remainedTime);
    }
}

void ActionRotateBy::instantUpdate(){
    movedAngle = rotatingAngle;
    this->target->addAngle(rotatingAngle);
    alive = false;
}

void ActionRotateBy::intervalUpdate(double& remainedTime){
    float duration = (float)this->duration;
    float currentTime = (float)(this->totalElapsedTime + remainedTime);
    
    if(currentTime >= duration){
        movedAngle = rotatingAngle - previousAngle;
        alive = false;
        remainedTime = currentTime - duration;
    }
    else{
        remainedTime = 0;
        if(rotatingAngle == 0){
            movedAngle = rotatingAngle;
            previousAngle = rotatingAngle;
        }
        else{
            float diff = (rotatingAngle * (currentTime / duration)) - previousAngle;
            movedAngle = diff;
            previousAngle += diff;
        }
    }
    this->target->addAngle(movedAngle, axis);
}

void ActionRotateBy::revive(){
    //revive. original and previous will be updated
    this->previousAngle = 0;
    this->movedAngle = 0;
    //make sure you kill it
    this->alive = false;
    this->running = false;
    
    ActionObject::revive();
}

ActionObject* ActionRotateBy::clone(){
    ActionRotateBy* cloneRotateBy = new ActionRotateBy();
    cloneRotateBy->initRotateBy(this->rotatingAngle, this->duration, this->axis);
    return cloneRotateBy;
}