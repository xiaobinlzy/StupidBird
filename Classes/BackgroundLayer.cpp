//
//  BackgroundLayer.cpp
//  StupidBird
//
//  Created by DLL on 14-3-16.
//
//

#include "BackgroundLayer.h"
#include "Defines.h"


BackgroundLayer::~BackgroundLayer()
{
    mTopHoldbacks->release();
    mBottomHoldbacks->release();
    mHoldbacks ->release();
}

float BackgroundLayer::getGroundHeight()
{
    return mGroundHeight;
}

bool BackgroundLayer::init()
{
    if (!CCLayer::init()) {
        return  false;
    }
    
    mHoldbackHorizontalDistance = 360;
    mHoldbackVerticalDistance = 200;
    mHoldbackRandomBetween = 300;
    mGroundHeight = 281;
    mMoveSpeed = 200;
    mNumberOfBackholds = 4;
    
    mHoldbacks = CCArray::createWithCapacity(mNumberOfBackholds * 2);
    mHoldbacks->retain();
    CCSpriteBatchNode *batchNode = CCSpriteBatchNode::create("flappy_packer.png");
    this->addChild(batchNode);
    

    

    CCSprite *sprGd1 = CCSprite::create("ground.png");
    sprGd1->setAnchorPoint(ccp(0, 0));
    sprGd1->setPosition(ccp(0, 0));
    CCSprite *sprGd2 = CCSprite::create("ground.png");
    sprGd2->setAnchorPoint(ccp(0, 0));
    sprGd2->setPosition(ccp(840, 0));
    this->addChild(sprGd1, 1);
    this->addChild(sprGd2, 1);
    
    mTopHoldbacks = CCArray::create();
    mTopHoldbacks->retain();
    mBottomHoldbacks = CCArray::create();
    mBottomHoldbacks->retain();
    
    srand(random());

    for (int i = 0; i < mNumberOfBackholds; i++) {
        int randomHeight = this->randomHeight();
        int xOffset = this->xOffset(i);
        CCSprite *bottomHoldback = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("holdback1.png"));
        bottomHoldback->setAnchorPoint(ccp(0.5f, 1));
        mBottomHoldbacks->addObject(bottomHoldback);
        batchNode->addChild(bottomHoldback);
        
        CCSprite *topHoldback = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("holdback2.png"));
        topHoldback->setAnchorPoint(ccp(0.5f, 0));
        mTopHoldbacks->addObject(topHoldback);
        batchNode->addChild(topHoldback);
        if (i < mNumberOfBackholds / 2) {
            bottomHoldback->setPosition(ccp(xOffset, 0));
            topHoldback->setPosition(ccp(xOffset, WIN_HEIGHT));
        } else {
            topHoldback->setPosition(ccp(xOffset, this->getBaseBottomHoldbackHeight() + randomHeight + mHoldbackVerticalDistance));
            bottomHoldback->setPosition(ccp(xOffset,  this->getBaseBottomHoldbackHeight() + randomHeight));
        }
        mHoldbacks->addObject(bottomHoldback);
        mHoldbacks->addObject(topHoldback);
    }
    return true;
    
}

CCArray* BackgroundLayer::getHoldbacks()
{
    return mHoldbacks;
}

int BackgroundLayer::randomHeight()
{
    return rand() % mHoldbackRandomBetween;
}

void BackgroundLayer::startMoveToBack()
{
    int changeOffset = mHoldbackHorizontalDistance * mNumberOfBackholds / 2;
    CCMoveBy *actionMove = CCMoveBy::create(changeOffset / (float)mMoveSpeed, ccp(-changeOffset, 0));
    CCCallFunc *callFunction = CCCallFunc::create(this, callfunc_selector(BackgroundLayer::refreshBackgroundLayer));
    CCSequence *moveBackAction = CCSequence::create(actionMove, callFunction, NULL);
    this->runAction(CCRepeatForever::create(moveBackAction));
}


void BackgroundLayer::refreshBackgroundLayer()
{
    this->setPosition(ccp(0, 0));
    this->randomHoldbacks();
}

void BackgroundLayer::randomHoldbacks()
{
    for (int i = 0; i < mNumberOfBackholds; i++) {
        int xOffset = this->xOffset(i);
        CCSprite *topHoldback = (CCSprite*)mTopHoldbacks->objectAtIndex(i);
        CCSprite *bottomHoldback = (CCSprite*)mBottomHoldbacks->objectAtIndex(i);
        if (i < mNumberOfBackholds / 2) {
            topHoldback->setPosition(ccp(xOffset, ((CCSprite*)mTopHoldbacks->objectAtIndex(i + mNumberOfBackholds / 2))->getPosition().y));
            bottomHoldback->setPosition(ccp(xOffset, ((CCSprite*)mBottomHoldbacks->objectAtIndex(i + mNumberOfBackholds / 2))->getPosition().y));
        } else {
            int randomHeight = this->randomHeight();
            topHoldback->setPosition(ccp(xOffset, this->getBaseBottomHoldbackHeight() + randomHeight + mHoldbackVerticalDistance));
            bottomHoldback->setPosition(ccp(xOffset,  this->getBaseBottomHoldbackHeight() + randomHeight));
        }
    }
}

int BackgroundLayer::getBaseBottomHoldbackHeight()
{
    return(WIN_HEIGHT - mHoldbackRandomBetween + mGroundHeight - mHoldbackVerticalDistance) / 2;
}

int BackgroundLayer::xOffset(int index)
{
    return (index) * mHoldbackHorizontalDistance;
}

void BackgroundLayer::stopMove()
{
    this->stopAllActions();
}