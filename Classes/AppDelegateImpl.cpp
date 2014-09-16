//
//  AppDelegateImpl.cpp
//  PigPigLeague
//
//  Created by DLL on 14-9-15.
//  Copyright (c) 2014年 monster. All rights reserved.
//

#include "AppDelegateImpl.h"
#include "platform/android/jni/JniHelper.h"
#include "GameScene.h"

USING_NS_CC;

static jobject gObj;
AppDelegateImpl::AppDelegateImpl() {
}

AppDelegateImpl::~AppDelegateImpl() {

}
bool AppDelegateImpl::applicationDidFinishLaunching() {
	AppDelegate::applicationDidFinishLaunching();
	CCScene *scene = GameScene::scene(
			"/data/data/com.dll.stupidbird/cache/screenShot.jpg");
	CCDirector::sharedDirector()->runWithScene(scene);
	return true;
}
void AppDelegateImpl::setJobject(jobject jObj) {
	gObj = jObj;
}

void AppDelegateImpl::destroy() {
	JavaVM *jvm = JniHelper::getJavaVM();
	JNIEnv *env;
	jvm->AttachCurrentThread(&env, NULL);
	jclass cls = env->FindClass("com/dll/stupidbird/GameCaller");
	jmethodID mid = env->GetMethodID(cls, "stopGame", "()V");
	env->CallVoidMethod(gObj, mid, NULL);
	env->DeleteGlobalRef(gObj);
	AppDelegate::destroy();
}
