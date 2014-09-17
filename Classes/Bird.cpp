//
//  Bird.cpp
//  StupidBird
//
//  Created by DLL on 14-3-16.
//
//

#include "Bird.h"


Bird::~Bird()
{
}

bool Bird::init()
{
    if (!CCSprite::init()) {
        return false;
    }
    mCurrentAction = NULL;
    CCAnimationCache::sharedAnimationCache()->addAnimationsWithFile("flappy_frame.plist");
    CCAnimation *flyAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("fly");
    CCAnimate *flyAnimate = CCAnimate::create(flyAnimation);
    mActionFly = CCRepeatForever::create(flyAnimate);
    mActionFly->retain();
    this->runAction(mActionFly);
    this->setAnchorPoint(ccp(0.5f, 0.5f));
    
    CCMoveBy *dropDown = CCMoveBy::create(0.6, ccp(0, -250));
    CCActionInterval *easeIn1 = CCEaseIn::create(dropDown, 2.0f);
    CCActionInterval *rotate = CCRotateTo::create(0.6, 70);
    CCActionInterval *easeIn2 = CCEaseIn::create(rotate, 2.0f);
    CCActionInterval *fallDown = CCMoveBy::create(0.6, ccp(0, -500));
    CCActionInterval *repeatFallDown = CCRepeat::create(fallDown, -1);
    mActionFalldown = CCSequence::create(CCSpawn::create(easeIn1, easeIn2, NULL), repeatFallDown, NULL);
    mActionFalldown->retain();
    

    mActionFlyUp = CCSequence::create(CCEaseOut::create(CCMoveBy::create(0.3, ccp(0, 100)), 2.0f), CCCallFunc::create(this, callfunc_selector(Bird::startFallDown)), NULL);
    mActionFlyUp->retain();
    return true;
}



void Bird::startFallDown()
{
    if (mCurrentAction) {
        this->stopAction(mCurrentAction);
    }
    mCurrentAction = mActionFalldown;
    this->runAction(mActionFalldown);
}

void Bird::cleanup()
{
    mActionFly->release();
    mActionFalldown->release();
    mActionFlyUp->release();
    CCSprite::cleanup();
}

void Bird::fallDown()
{
    this->stopAction(mActionFly);
    if (mCurrentAction == mActionFalldown) {
        return;
    }
    this->startFallDown();
}

void Bird::fly()
{
    if (mCurrentAction) {
        this->stopAction(mCurrentAction);
    }
    this->setRotation(-20.0f);
    mCurrentAction = mActionFlyUp;
    this->runAction(mActionFlyUp);
}
