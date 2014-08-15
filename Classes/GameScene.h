//
//  GameScene.h
//  StupidBird
//
//  Created by DLL on 14-3-15.
//
//

#ifndef __StupidBird__GameScene__
#define __StupidBird__GameScene__

#include "Cocos2d.h"
#include "BackgroundLayer.h"
#include "Bird.h"

using namespace cocos2d;

class GameScene : public CCLayer{
private:
    BackgroundLayer *mBackgroundLayer;
    Bird *mBird;
    bool mIsGameOver;
public:
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual ~GameScene();
    static CCScene* scene();
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    virtual void update(float dt);
    CREATE_FUNC(GameScene);
};

#endif /* defined(__StupidBird__GameScene__) */
