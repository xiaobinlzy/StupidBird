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

class GameScene : public CCLayerColor{
private:
    BackgroundLayer *mBackgroundLayer;
    Bird *mBird;
    bool mIsGameOver;
    bool mIsDead;
public:
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual ~GameScene();
    static CCScene* scene(const char *bgPath);
    virtual bool init(const char * bgPath);
    virtual void onEnterTransitionDidFinish();
    virtual void update(float dt);
    static GameScene * create(const char* bgPath);
};

#endif /* defined(__StupidBird__GameScene__) */
