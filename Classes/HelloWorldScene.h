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

	// ����
	void menuHelpCallback(cocos2d::Ref* pSender);

	//��ʼ������ͼ������
	void initNumberArr(int sex);

	//�Զ���������ͼ��
	void newNumber();

	//�����¼�
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	//�����ƶ�
	bool onLeft();

	//�����ƶ�
	bool onRight();

	//�����ƶ�
	bool onUp();

	//�����ƶ�
	bool onDown();

	//��Ϸ�Ƿ����
	bool isOver();

	//��Ϸ�Ƿ�ʤ��
	bool isWin();

	//��ʼ&�����˵�
	void startAndclose(Layer* layer,Vec2 start, Vec2 close);

private:
	float m_posX, m_posY;	//��ǰλ������x,y
	float m_targetX, m_targetY;		//Ŀ��λ��
	int m_totalScore;	//�ܷ�
	MySquare* m_mySquare[4][4];		//����ͼ�� ����
	Label* m_scoreLabel2;
};

#endif // __HELLOWORLD_SCENE_H__
