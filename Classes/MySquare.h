/*
************************************************************************
*
*	MySquare.h
*	Author: 杜星飞
*   describe: 2048小方格类，包含 数值、x/y坐标、标签文本
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

	//获取数值
	int getNumber();

	//设定数值
	void setNumber(int num);

	//获取颜色层
	LayerColor* getLayerColor();

private:
	bool initMySquare(int num, int posX, int posY, int SquareSize);

	int m_num;	//数值
	Label* m_label;	//数字层
	LayerColor* m_colorLayer; //颜色层
};

#endif