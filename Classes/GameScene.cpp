//
//  GameScene.cpp
//  StupidBird
//
//  Created by DLL on 14-3-15.
//
//

#include "GameScene.h"
#include "AppDelegate.h"

bool GameScene::init(const char* bgPath) {
	if (!CCLayer::init()) {
		return false;
	}
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("flappy_packer.plist");
	mIsGameOver = false;
	mBackgroundLayer = BackgroundLayer::create();
	this->addChild(mBackgroundLayer, -1);
	CCSprite *sprBg1 = CCSprite::create(bgPath);
	sprBg1->setAnchorPoint(ccp(0, 0));
	sprBg1->setPosition(ccp(0, 0));
	CCSize bgSize = sprBg1->getContentSize();
	sprBg1->setScaleX(640.0f / bgSize.width);
	sprBg1->setScaleY(960.0f / bgSize.height);
	this->addChild(sprBg1, -2);
	mBird = Bird::create();
	mBird->setPosition(ccp(150, 600));
	this->addChild(mBird, 0);

	return true;
}

GameScene * GameScene::create(const char *bgPath) {
	GameScene * scene = new GameScene();
	if (scene && scene->init(bgPath)) {
		scene->autorelease();
		return scene;
	} else {
		delete scene;
		scene = NULL;
		return scene;
	}
}


GameScene::~GameScene() {

}

CCScene* GameScene::scene(const char *bgPath) {
	CCScene *scene = CCScene::create();
	GameScene *layer = GameScene::create(bgPath);
	scene->addChild(layer);
	return scene;
}

void GameScene::update(float dt) {
	CCRect birdBounds = mBird->boundingBox();
	if (!mIsDead && !mIsGameOver) {
		if (birdBounds.origin.y <= mBackgroundLayer->getGroundHeight()) {
			mIsDead = true;
		} else {
			birdBounds.origin.y += 30;
			birdBounds.size.height -= 35;
			birdBounds.size.width -= 20;
			birdBounds.origin.x += 10;
			CCArray *holdbacks = mBackgroundLayer->getHoldbacks();
			for (int i = 0; i < holdbacks->count(); i++) {
				CCNode *holdback = (CCNode*) (holdbacks->objectAtIndex(i));
				CCRect holdbackRect = holdback->boundingBox();
				holdbackRect.origin.x += mBackgroundLayer->getPositionX()
						+ 15.0f;
				holdbackRect.size.width -= 30;
				if (birdBounds.intersectsRect(holdbackRect)) {
					mIsDead = true;
					break;
				}
			}
		}
		if (mIsDead) {
			mBird->fallDown();

			mBackgroundLayer->stopAllActions();
		}
	} else if (mIsDead) {
		if (birdBounds.origin.y <= mBackgroundLayer->getGroundHeight()) {
			mBird->stopAllActions();
			mIsGameOver = true;
		}
	}
}

void GameScene::onEnterTransitionDidFinish() {
	CCLayer::onEnterTransitionDidFinish();
	this->setTouchEnabled(true);
	this->setTouchMode(kCCTouchesOneByOne);
	mBackgroundLayer->startMoveToBack();
	mBird->startFallDown();
	this->scheduleUpdate();
	((AppDelegate *)CCApplication::sharedApplication())->onGameStart();
}

bool GameScene::onTouchBegan(cocos2d::CCTouch *pTouch,
		cocos2d::CCEvent *pEvent) {
	if (!mIsDead) {
		mBird->fly();
	}
	return true;
}

void GameScene::onTouchEnded(CCTouch *pTouch,CCEvent *pEvent) {
	if (mIsGameOver) {
		CCDirector::sharedDirector()->popScene();
		((AppDelegate *) CCApplication::sharedApplication())->destroy();
	}

}
