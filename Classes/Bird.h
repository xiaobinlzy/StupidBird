//
//  Bird.h
//  StupidBird
//
//  Created by DLL on 14-3-16.
//
//

#ifndef __StupidBird__Bird__
#define __StupidBird__Bird__

#include "cocos2d.h"

using namespace cocos2d;



class Bird : public CCSprite {
private:
    CCActionInterval *mActionFly;
    CCActionInterval *mActionFalldown;
    CCActionInterval *mActionFlyUp;
    CCActionInterval *mCurrentAction;
    
public:
    virtual bool init();
    virtual ~Bird();
    virtual void fly();
    virtual void startFallDown();
    virtual void fallDown();
    virtual void cleanup();
    CREATE_FUNC(Bird);
};

#endif /* defined(__StupidBird__Bird__) */
