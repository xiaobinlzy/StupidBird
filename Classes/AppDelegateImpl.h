//
//  AppDelegateImpl.h
//  PigPigLeague
//
//  Created by DLL on 14-9-15.
//  Copyright (c) 2014年 monster. All rights reserved.
//

#ifndef __PigPigLeague__AppDelegateImpl__
#define __PigPigLeague__AppDelegateImpl__

#include <iostream>
#include "AppDelegate.h"
#include <jni.h>

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
USING_NS_CC;

extern "C" {
class AppDelegateImpl : public AppDelegate
{
public:
    AppDelegateImpl();
    ~AppDelegateImpl();
    virtual bool applicationDidFinishLaunching();
    virtual void destroy();
    static void setJobject(jobject jObj);
};

}


#endif /* defined(__PigPigLeague__AppDelegateImpl__) */
