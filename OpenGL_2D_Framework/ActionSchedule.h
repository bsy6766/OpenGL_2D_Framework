//
//  ActionSchedule.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/17/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionSchedule__
#define __OpenGL_2D_Framework__ActionSchedule__

#include "CommonInclude.h"
#include "ActionObject.h"
#include "ActionDelay.h"
#include <list>

class ActionSchedule{
protected:
private:
    int repeat;
    int repeatCounter;
    bool instantSchedule;
    bool finished;
    
    double remainedTime;
    
    std::list<ActionObject*> actionList;
    void clearList();
public:
    ActionSchedule();
    ~ActionSchedule();
    void createSchedule(ActionObject* action, int repeat);
    void createSchedule(ActionObject** actions, int size, int repeat);
    void createSchedule(std::initializer_list<ActionObject*>& actions, int repeat);
    void terminateAllAction();
    void updateSchedule();
    bool isEmpty();
    bool isFinished();
    bool needRepeat();
    void reviveSchedule();
};

#endif /* defined(__OpenGL_2D_Framework__ActionSchedule__) */
