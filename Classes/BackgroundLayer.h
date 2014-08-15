//
//  BackgroundLayer.h
//  StupidBird
//
//  Created by DLL on 14-3-16.
//
//

#ifndef __StupidBird__GameLayer__
#define __StupidBird__GameLayer__

#include "cocos2d.h"

using namespace cocos2d;
class BackgroundLayer : public CCLayer {
private:
    CCArray *mTopHoldbacks;
    CCArray *mBottomHoldbacks;
    CCArray *mHoldbacks;
    int mHoldbackHorizontalDistance;
    int mHoldbackVerticalDistance;
    int mNumberOfBackholds;
    int mHoldbackRandomBetween;
    int mMoveSpeed;
    float mGroundHeight;
public:
    virtual ~BackgroundLayer();
    virtual bool init();
    CREATE_FUNC(BackgroundLayer);
    virtual float getGroundHeight();
    virtual void startMoveToBack();
    virtual void stopMove();
    virtual CCArray* getHoldbacks();
private:
    virtual void refreshBackgroundLayer();
    virtual void randomHoldbacks();
    virtual int xOffset(int index);
    virtual int randomHeight();
    virtual int getBaseBottomHoldbackHeight();
};

#endif /* defined(__StupidBird__GameLayer__) */
