//
//  ActionDelay.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/7/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "ActionDelay.h"

ActionDelay::ActionDelay():
ActionObject()
{
    cout << "Creating ACTION_DELAY" << endl;
}

ActionDelay::~ActionDelay(){
    cout << "Deleting ACTION_DELAY" << endl;
}

ActionDelay::ActionDelay(const ActionDelay& other):ActionObject(other){
    cout << "copying ACTION_DELAY" << endl;
}

void ActionDelay::initDelay(double duration){
    this->duration = duration;
}

void ActionDelay::instantUpdate(){
//    totalDelayed = duration;
    alive = false;
}

void ActionDelay::intervalUpdate(double& remainedTime){
    float duration = (float)this->duration;
    //currentTime will be total elapsed time (+ remained time)
    float totalDelayTime = (float)this->totalElapsedTime + remainedTime;
    
    //if total elapsed time is equal(remainedTime == 0) or greater than(remainedTime >0) than duration,
    if(totalDelayTime >= duration){
        alive = false;
        remainedTime = totalDelayTime - duration;
    }
    else{
        remainedTime = 0;
    }
}

void ActionDelay::updateAction(double& remainedTime){
    if(!alive)
        return;
    
    //delay doesn't need any update for initial state of action
    if(duration == 0){
        instantUpdate();
    }
    else{
        intervalUpdate(remainedTime);
    }
}

void ActionDelay::revive(){
    //revive. original and previous will be updated
    this->alive = false;
    this->running = false;
    
    ActionObject::revive();
}