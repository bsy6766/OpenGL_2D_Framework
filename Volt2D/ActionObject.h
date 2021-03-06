//
//  ActionObject.h
//  Volt2D
//
//  Created by Seung Youp Baek on 5/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__ActionObject__
#define __Volt2D__ActionObject__

#include "Utility.hpp"

namespace Volt2D{
class Object;
    
/**
 *  @class AcitonObject
 *  @brief A base class of action classes.
 */
class ActionObject{
protected:
    /**
     *  protected constructor
     */
    ActionObject();
    
    /**
     *  protected copy constructor
     */
    ActionObject(const ActionObject& other);
    
    /**
     *  Action duration
     */
    double duration;
    
    /**
     *  Action's total elapsed time since it started
     */
    double totalElapsedTime;
    
    /**
     *  A target to update from this action
     */
    Object* target;
private:
public:
    virtual ~ActionObject();
    
    /**
     *  Only true if action starts running.
     *  False means it never started
     */
    bool running;
    
    /**
     *  Only true if action is valid.
     *  False means action is ended or dead
     */
    bool alive;
    
    /**
     * action won't get deleted if it is true.
     * It becomes true when action repeats forever
     */
    bool isProtected;
    
    /**
     *  Getter for action's duration
     *  @return duration of action object
     */
    double getDuration();
    
    /**
     *  Checks if action is running or not
     *  @return true if action is running. Else, false.
     */
    bool isRunning();
    
    /**
     *  Checks if action is alive or dead
     *  @return true if action is still valid. Else, false.
     */
    bool isAlive();
    
    /**
     *  Update time varaibles of this action object.
     *  @param elapsedTime An elapsed time for current iteration
     *  @return Remaining time that action didn't use if it ended. This will be stored and used on next action.
     */
    double setCurrentTime(double elapsedTime);
    
    /**
     *  Virtual function for starting action.
     *  Each action needs to update their own variables so it needs to be overriden
     */
    virtual void startAction();
    
    /**
     *  Update action. Pure virtual. 
     *  @param remainedTime An reference of remained time that stored in ActionSchedule.
     */
    virtual void updateAction(double& remainedTime) = 0;
    
    /**
     *  Kill and stop action. Action will be deleted if it doesn't have to repeat or protected
     */
    void kill();
    
    /**
     *  Revive this action.
     */
    virtual void revive();
    
    /**
     *  Get target of this object
     *  @return Object's target
     */
    Object* getTarget();
    
    /**
     *  Bind target to update
     *  @param target A RenderableObject pointer of target
     */
    void bindTarget(Object* target);
    
    /**
     *  Clone object
     */
    virtual ActionObject* clone() = 0;
};
}   //namespace end

#endif /* defined(__Volt2D__ActionObject__) */
