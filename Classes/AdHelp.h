/*
************************************************************************
*
*	AdHelp.h
*	Author: ���Ƿ�
*   describe: ����
*
************************************************************************
*/

#ifndef __AdHelp__H__
#define __AdHelp__H__

#include <cocos2d.h>
using namespace cocos2d;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"
#include <jni.h>

#endif

class AdHelp
{
public:
	AdHelp();
	virtual ~AdHelp();
	//ͨ��JNI����JAVA��̬������ʵ��չʾAD
	static void showAd(int adTag);

};

#endif