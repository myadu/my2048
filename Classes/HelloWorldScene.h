#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "MySquare.h"
#include "AdHelp.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

public:
	// a selector callback
	void menuReStartCallback(cocos2d::Ref* pSender);

	// 帮助
	void menuHelpCallback(cocos2d::Ref* pSender);

	//初始化数字图块数组
	void initNumberArr(int sex);

	//自动产生数字图块
	void newNumber();

	//触摸事件
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	//向左移动
	bool onLeft();

	//向右移动
	bool onRight();

	//向上移动
	bool onUp();

	//向下移动
	bool onDown();

	//游戏是否结束
	bool isOver();

	//游戏是否胜利
	bool isWin();

	//开始&结束菜单
	void startAndclose(Layer* layer,Vec2 start, Vec2 close);

private:
	float m_posX, m_posY;	//当前位置坐标x,y
	float m_targetX, m_targetY;		//目标位置
	int m_totalScore;	//总分
	MySquare* m_mySquare[4][4];		//数字图块 数组
	Label* m_scoreLabel2;
};

#endif // __HELLOWORLD_SCENE_H__
