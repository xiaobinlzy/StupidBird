//
//  GameScene.cpp
//  StupidBird
//
//  Created by DLL on 14-3-15.
//
//

#include "GameScene.h"


bool GameScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("flappy_packer.plist");
    mIsGameOver = false;
    mBackgroundLayer = BackgroundLayer::create();
    this->addChild(mBackgroundLayer, -1);
    
    CCSprite *sprBg1 = CCSprite::create("bg.png");
    sprBg1->setAnchorPoint(ccp(0, 0));
    sprBg1->setPosition(ccp(0, 0));
    this->addChild(sprBg1, -2);
    mBird = Bird::create();
    mBird->setPosition(ccp(150, 600));
    this->addChild(mBird, 0);
    
    return true;
}

GameScene::~GameScene()
{
    
}

CCScene* GameScene::scene()
{
    CCScene *scene = CCScene::create();
    GameScene *layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

void GameScene::update(float dt)
{
    CCRect birdBounds = mBird->boundingBox();
    if (birdBounds.origin.y <= mBackgroundLayer->getGroundHeight()) {
        mIsGameOver = true;
    }
    birdBounds.origin.y += 30;
    birdBounds.size.height -= 35;
    birdBounds.size.width -= 20;
    birdBounds.origin.x += 10;
    CCArray *holdbacks = mBackgroundLayer->getHoldbacks();
    for (int i = 0; i < holdbacks->count(); i++) {
        CCNode *holdback = (CCNode*)(holdbacks->objectAtIndex(i));
        CCRect holdbackRect = holdback->boundingBox();
        holdbackRect.origin.x += mBackgroundLayer->getPositionX() + 15.0f;
        holdbackRect.size.width -= 30;
        if (birdBounds.intersectsRect(holdbackRect)) {
            mIsGameOver = true;
            break;
        }
    }
    if (mIsGameOver) {
        mBird->stopAllActions();
        mBackgroundLayer->stopAllActions();
        this->unscheduleUpdate();
    }
}

void GameScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    mBackgroundLayer->startMoveToBack();
    mBird->startFallDown();
    this->scheduleUpdate();
}

bool GameScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (mIsGameOver) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1, GameScene::scene()));
        return true;
    }
    mBird->fly();
    return true;
}
