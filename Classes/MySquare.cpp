/*
************************************************************************
*
*	MySquare.cpp
*	Author: 杜星飞
*   describe: 2048小方格类，包含 数值、x/y坐标、标签文本、颜色层
*
************************************************************************
*/

#include "MySquare.h"

MySquare::MySquare() : m_num(0),m_label(nullptr), m_colorLayer(nullptr)
{

}

MySquare* MySquare::createMySquare(int num, int posX, int posY, int SquareSize)
{
	MySquare* m_square = nullptr;
	do 
	{
		m_square = new MySquare();
		CC_BREAK_IF(!m_square);

		if (m_square && m_square->initMySquare(num, posX, posY, SquareSize))
			m_square->autorelease();
		else
			CC_SAFE_DELETE(m_square);

	} while (0);
	return m_square;
}


bool MySquare::initMySquare(int num, int posX, int posY, int SquareSize)
{
	bool bRect = false;

	do
	{
		m_num = num;
		
		//创建标签
		m_label = Label::createWithTTF("", "fonts/DFPShaoNvW5-GB.ttf", 35);
		m_label->setPosition(Vec2(posX, posY));
		CC_BREAK_IF(!m_label);

		this->addChild(m_label,1);


		//创建颜色层
		m_colorLayer = LayerColor::create(Color4B(200, 190, 180, 255), SquareSize, SquareSize);
		m_colorLayer->setPosition(Vec2(posX, posY));
		CC_BREAK_IF(!m_colorLayer);

		this->addChild(m_colorLayer,0);

		bRect = true;
	} while (0);

	setNumber(num);

	return bRect;
}

//获取数值
int MySquare::getNumber()
{
	return m_num;
}

//设定数值
void MySquare::setNumber(int num)
{
	m_num = num;

	if (num>0)
	{
		m_label->setDimensions(m_colorLayer->getContentSize().width, m_colorLayer->getContentSize().height);
		m_label->setString(String::createWithFormat("%d", m_num)->getCString());
		
		if (num>0 && num<16)
		{
			m_label->setAnchorPoint(Vec2(-0.3, 0.2));

			switch (num)
			{
			case 2:
				m_label->setTextColor(Color4B(192, 192, 192, 255));
				m_colorLayer->setColor(Color3B(240, 230, 220));
				break;

			case 4:
				m_label->setTextColor(Color4B(130, 120, 110, 255));
				m_colorLayer->setColor(Color3B(240, 220, 200));
				break;

			case 8:
				m_label->setTextColor(Color4B(255, 255, 255, 255));
				m_colorLayer->setColor(Color3B(240, 180, 120));
				break;
			}
		}
		else if(num>=16 && num<128)
		{
			m_label->setAnchorPoint(Vec2(-0.1, 0.2));
			m_label->setScale(0.8);

			switch (num)
			{
			case 16:			
				m_label->setTextColor(Color4B(50, 234, 102, 255));
				m_colorLayer->setColor(Color3B(240, 140, 90));
				break;

			case 32:
				m_label->setTextColor(Color4B(178, 36, 156, 255));
				m_colorLayer->setColor(Color3B(240, 120, 90));
				break;

			case 64:
				m_label->setTextColor(Color4B(171, 27, 231, 255));
				m_colorLayer->setColor(Color3B(240, 90, 60));
				break;
			default:
				break;
			}
		}

		else if (num>=128 && num<1024)
		{
			m_label->setAnchorPoint(Vec2(-0.1, 0.1));
			m_label->setScale(0.6);

			switch (num)
			{
			case 128:
				m_label->setTextColor(Color4B(41, 231, 195, 255));
				m_colorLayer->setColor(Color3B(240, 90, 60));
				break;

			case 256:
				m_label->setTextColor(Color4B(129, 23, 192, 255));
				m_colorLayer->setColor(Color3B(240, 200, 70));
				break;

			case 512:
				m_label->setTextColor(Color4B(17,241,116,255));
				m_colorLayer->setColor(Color3B(0, 130, 0));
				break;
			}
		}

		else if (num>=1024 && num<=8192)
		{
			m_label->setAnchorPoint(Vec2(-0.1, -0.2));
			m_label->setScale(0.5);

			switch (num)
			{
			case 1024:
				m_label->setTextColor(Color4B(225,120,11,255));
				m_colorLayer->setColor(Color3B(200, 220, 240));
				break;

			case 2048:
				m_label->setTextColor(Color4B(40,60,80,255));
				m_colorLayer->setColor(Color3B(160,200,180));
				break;
			default:
				break;
			}
		}

	}
	else
	{
		m_label->setString("");
		m_colorLayer->setColor(Color3B(200, 190, 180));
	}
}

//获取颜色层
LayerColor* MySquare::getLayerColor()
{
	return this->m_colorLayer;
}