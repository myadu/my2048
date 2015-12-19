/*
************************************************************************
*
*	MySquare.h
*	Author: ���Ƿ�
*   describe: 2048С�����࣬���� ��ֵ��x/y���ꡢ��ǩ�ı�
*
************************************************************************
*/
#ifndef __MySquare_H__
#define __MySquare_H__

#include "cocos2d.h"

using namespace cocos2d;

class MySquare : public Sprite
{
public:
	MySquare();

	static MySquare* createMySquare(int num, int posX, int posY, int SquareSize);

	//��ȡ��ֵ
	int getNumber();

	//�趨��ֵ
	void setNumber(int num);

	//��ȡ��ɫ��
	LayerColor* getLayerColor();

private:
	bool initMySquare(int num, int posX, int posY, int SquareSize);

	int m_num;	//��ֵ
	Label* m_label;	//���ֲ�
	LayerColor* m_colorLayer; //��ɫ��
};

#endif