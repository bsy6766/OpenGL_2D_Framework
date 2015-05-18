//
//  ActionObject.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionObject__
#define __OpenGL_2D_Framework__ActionObject__

#include "CommonInclude.h"
#include "Timer.h"
#include <glm/glm.hpp>

//Action IDs
enum ActionID{
    ACTION_DELAY = 0,
    ACTION_MOVE_TO,
    ACTION_MOVE_BY,
    ACTION_ROTATE_TO,
    ACTION_ROTATE_BY,
    ACTION_SCALE_TO,
    ACTION_SCALE_BY,
    ACTION_JUMP_TO,
    ACTION_JUMP_BY,
    ACTION_FADE_TO
};

class ActionObject{
private:
protected:
    //action's unique enum ID
    ActionID actionID;
    
    static unsigned int ACTION_ID;
    
    //item vars
    double duration;
    double totalElapsedTime;
    double previousTime;
    double unusedTime;
    double remainedTimeByDeath;
    double speed;
    
public:
    unsigned int objID;
    
    ActionObject();
    virtual ~ActionObject();
    
    bool running;
    bool alive;
    
    /**
     * action won't get deleted if it is true.
     * It becomes true when action repeats forever
     */
    bool isProtected;
    
    //getters
    ActionID getActionID();
    double getDuration();
    
    bool isRunning();
    bool isAlive();
    
    //time functions
    double getPreviousTime();
    double getTotalElapsedTime();
    double getElapsedTime();
    double setCurrentTime(double elapsedTime);
    double getRemainedTime();
    
    //setters
    void setSpeed(double speed);
    
    void startAction();
    void stopAction();
    
    /**
     * pure virtual function.
     * Derived class
     */
//    virtual void update(double elapsedTime, double unusedTime) = 0;
    virtual void instantUpdate() = 0;
    virtual void intervalUpdate(double remainedTime) = 0;
    
    //kill and reset
    void kill();
    void revive();
};

#endif /* defined(__OpenGL_2D_Framework__ActionObject__) */
