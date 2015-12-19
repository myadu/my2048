/*
************************************************************************
*
*	AdHelp.cpp
*	Author: ���Ƿ�
*   describe: ����
*
************************************************************************
*/

#include "AdHelp.h"

AdHelp::AdHelp()
{

}

AdHelp::~AdHelp()
{

}

void AdHelp::showAd(int adTag)
{

	//�жϵ�ǰ�Ƿ�ΪAndroidƽ̨ JniMethodInfo showAd;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/ShowAdHelper", "showMyAd", "(I)V");
	if (!isHave)
	{
		CCLog("jni:showAdStatic is null");
	}
	else
	{
		//���ô˺���
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, adTag);
	}
#endif
}
