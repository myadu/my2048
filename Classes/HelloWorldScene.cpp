#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

	startAndclose(this,Vec2(origin.x, origin.y), Vec2(visibleSize.width, origin.y));

	//AI帮助项

	auto m_helpLabel = Label::createWithTTF(
		"Hint",
		"fonts/DFPShaoNvW5-GB.ttf",
		35);
	m_helpLabel->setTextColor(Color4B(255, 0, 0, 125));

	auto helpItem = MenuItemLabel::create(m_helpLabel, CC_CALLBACK_1(HelloWorld::menuHelpCallback, this));
	helpItem->setPosition(visibleSize.width/2,origin.y+helpItem->getContentSize().height*2);
//	helpItem->setAnchorPoint(Vec2(-0.2, -0.5));
//	helpItem->setTarget(this, menu_selector(HelloWorld::menuReStartCallback));

	// create menu, it's an autorelease object
	auto menu = Menu::create(helpItem, nullptr);
	menu->setPosition(Vec2::ZERO);

    /////////////////////////////
    // 3. add your codes below...

	m_totalScore = 0;

	//初始化背景
	auto bgLayerColor = LayerColor::create(Color4B(180, 170, 160, 255));
	bgLayerColor->setPosition(Vec2::ZERO);
	this->addChild(bgLayerColor, 0);
	
	//获取XML文本
	auto m_dictionary = Dictionary::createWithContentsOfFile("fonts/text.xml");

	//标题
	auto titleLabel = Label::createWithTTF(
		((__String*)(m_dictionary->objectForKey("next")))->getCString(),
		"fonts/DFPShaoNvW5-GB.ttf",
		40
		);
//	titleLabel->setDimensions(visibleSize.width, visibleSize.height/6);
	titleLabel->setAnchorPoint(Vec2(0, 0));
	titleLabel->setTextColor(Color4B(255, 0, 0, 160));
	titleLabel->setPosition(Vec2(visibleSize.width/6, visibleSize.height - titleLabel->getContentSize().height));
	this->addChild(titleLabel, 1);

	//分数标签
	auto scoreLabel1 = Label::createWithTTF(
		((__String*)(m_dictionary->objectForKey("score")))->getCString(),
		"fonts/DFPShaoNvW5-GB.ttf",
		35
		);
	scoreLabel1->setPosition(Vec2(origin.x + scoreLabel1->getContentSize().width, visibleSize.height - titleLabel->getContentSize().height-scoreLabel1->getContentSize().height));
	this->addChild(scoreLabel1, 1);

	m_scoreLabel2 = Label::createWithTTF(
		String::createWithFormat("%d",m_totalScore)->getCString(),
		"fonts/DFPShaoNvW5-GB.ttf",
		35
		);
	m_scoreLabel2->setTextColor(Color4B::RED);
	m_scoreLabel2->setPosition(Vec2(scoreLabel1->getContentSize().width * 3, visibleSize.height - titleLabel->getContentSize().height - scoreLabel1->getContentSize().height));
	this->addChild(m_scoreLabel2, 1);

	//初始化数字图块数组
	initNumberArr(visibleSize.height*2/3);
  
	//触摸事件

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	AdHelp::showAd(2);
	log("AdHelp::showAd(2);");

	return true;
}

//初始化数字图块数组
void HelloWorld::initNumberArr(int sex)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	int m_widthSingle = visibleSize.width / 25;
	int m_widthSize = m_widthSingle * 5;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4;j++)
		{
			MySquare* newMySquare = MySquare::createMySquare(0, m_widthSingle + ((m_widthSize + m_widthSingle)*j), sex - ((m_widthSize + m_widthSingle)*i), m_widthSize);
			this->addChild(newMySquare);
			m_mySquare[i][j] = newMySquare;
		}
	}

	newNumber();
	newNumber();
}

//自动产生数字图块
void HelloWorld::newNumber()
{
	CCLOG("newNumber");

	bool isSpace = false;

	//如果有空的，就生成新的数字图块
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (0==m_mySquare[i][j]->getNumber())
			{
				isSpace = true;
				break;
			}
		}
		if (isSpace)
		{
			break;
		}
	}

	while (isSpace)
	{
		int row = random(0,3);
		int col = random(0,3);

		if (0==m_mySquare[row][col]->getNumber())
		{
			m_mySquare[row][col]->setNumber((random(0, 20)>2 ? 2:4));
			m_mySquare[row][col]->getLayerColor()->runAction(Sequence::create(ScaleTo::create(0, 0, 0), ScaleTo::create(0.3, 1, 1),nullptr));
			break;
		}
	}
}

//触摸事件
bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
	m_posX = touch->getLocation().x;
	m_posY = touch->getLocation().y;

	return true;
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
	Vec2 m_vec = touch->getLocation();
	m_targetX = m_vec.x-m_posX;
	m_targetY = m_vec.y-m_posY;

	bool isNew = false;

	//判断 是左右移动 还是 上下移动
	if (abs(m_targetX) > abs(m_targetY))
	{
		if (m_targetX > 10)
			isNew=onUp();
		else if (m_targetX<-10)
			isNew = onDown();
	}
	else
	{
		if (m_targetY>10)
			isNew = onLeft();
		else if (m_targetY < -10)
			isNew = onRight();
	}

	//改变分数
	m_scoreLabel2->setString(CCString::createWithFormat("%d", m_totalScore)->getCString());

	log("Score1 %d", m_totalScore);

	if (isNew)
		newNumber();

	if (isOver() || isWin())
	{

		AdHelp::showAd(1);

		log("AdHelp::showAd(1);");

		//一个遮罩层
		auto shadeLayerColor = LayerColor::create(Color4B(180, 170, 160, 180));
		this->addChild(shadeLayerColor, 2);
		shadeLayerColor->runAction(Sequence::create(ScaleTo::create(0.3, 0, 0), ScaleTo::create(0.3, 1, 1),nullptr));
//		this->setTouchEnabled(false);

		//胜利 或 失败标志
		auto m_direction = Dictionary::createWithContentsOfFile("fonts/text.xml");

		auto m_resultStringWin = ((__String*)(m_direction->objectForKey("win")))->getCString();
		auto m_resultStringLose = ((__String*)(m_direction->objectForKey("lose")))->getCString();

		String m_resultString;
		if (isWin())
			m_resultString = m_resultStringWin;
		else
			m_resultString = m_resultStringLose;

		auto m_resultLabel = Label::create(
			m_resultString.getCString(),
			"fonts/DFPShaoNvW5-GB.ttf",
			50);
		m_resultLabel->setTextColor(Color4B(255, 0, 0, 255));
		m_resultLabel->setDimensions(shadeLayerColor->getContentSize().width, shadeLayerColor->getContentSize().height / 4);
		m_resultLabel->setPosition(Vec2(0, shadeLayerColor->getContentSize().height));
		m_resultLabel->setAnchorPoint(Vec2(0,1));
		shadeLayerColor->addChild(m_resultLabel);

		//最终成绩

		log("Score2 %d", m_totalScore);

		auto m_score = Label::createWithTTF(
			String::createWithFormat("Score: %d", m_totalScore)->getCString(),
			"fonts/DFPShaoNvW5-GB.ttf",
			25
			);
		m_score->setPosition(Vec2(shadeLayerColor->getContentSize().width / 2, shadeLayerColor->getContentSize().height-m_resultLabel->getContentSize().height));
		shadeLayerColor->addChild(m_score);

		//储存成绩
		auto userDefault = UserDefault::getInstance();

		auto m_bestScore = userDefault->getStringForKey("BestScore");

		log("BestScore1 %d", atoi(m_bestScore.c_str()));

		if (m_totalScore>atoi(m_bestScore.c_str()))
		{
			auto m_str = (__String*)String::createWithFormat("%d", m_totalScore);
			userDefault->setStringForKey("BestScore", m_str->getCString());
		}


		//最佳成绩
		auto m_scoreBest = Label::createWithTTF(
			"BestScore: " + userDefault->getStringForKey("BestScore"),
			"fonts/DFPShaoNvW5-GB.ttf",
			25
			);
		m_scoreBest->setPosition(Vec2(shadeLayerColor->getContentSize().width /2, shadeLayerColor->getContentSize().height - m_resultLabel->getContentSize().height*2));
		shadeLayerColor->addChild(m_scoreBest);

		log("BestScore2 %d", atoi(m_bestScore.c_str()));

		//重新开始||退出
		startAndclose(
			shadeLayerColor,
			Vec2(0,shadeLayerColor->getContentSize().height/4),
			Vec2(shadeLayerColor->getContentSize().width, shadeLayerColor->getContentSize().height / 4)
			);

		return;
	}
}

//向左移动
bool HelloWorld::onLeft()
{
	CCLOG("UP");

	bool isLeft = false;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			for (int xx = x + 1; xx < 4; xx++)
			{
				if (m_mySquare[xx][y]->getNumber()>0)
				{
					if (0==m_mySquare[x][y]->getNumber())
					{
						m_mySquare[x][y]->setNumber(m_mySquare[xx][y]->getNumber());
						m_mySquare[xx][y]->setNumber(0);
						--x;
						isLeft = true;
					}
					else if (m_mySquare[x][y]->getNumber() == m_mySquare[xx][y]->getNumber())
					{
						m_totalScore += m_mySquare[x][y]->getNumber() * 2;
						m_mySquare[x][y]->setNumber(m_mySquare[x][y]->getNumber() * 2);
						m_mySquare[xx][y]->setNumber(0);
						isLeft = true;
					}
					break;
				}
			}
		}
	}
	return isLeft;
}

//向右移动
bool HelloWorld::onRight()
{
	CCLOG("Down");

	bool isRight = false;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 3; x >=0; x--)
		{
			for (int xx = x - 1; xx >=0; xx--)
			{
				if (m_mySquare[xx][y]->getNumber()>0)
				{
					if (0 == m_mySquare[x][y]->getNumber())
					{
						m_mySquare[x][y]->setNumber(m_mySquare[xx][y]->getNumber());
						m_mySquare[xx][y]->setNumber(0);
						++x;
						isRight = true;
					}
					else if (m_mySquare[x][y]->getNumber() == m_mySquare[xx][y]->getNumber())
					{
						m_totalScore += m_mySquare[x][y]->getNumber() * 2;
						m_mySquare[x][y]->setNumber(m_mySquare[x][y]->getNumber() * 2);
						m_mySquare[xx][y]->setNumber(0);
						isRight = true;
					}
					break;
				}
			}
		}
	}
	return isRight;
}

//向上移动
bool HelloWorld::onUp()
{
	CCLOG("Right");

	bool isUp = false;

	for (int x = 0; x < 4; x++)
	{
		for (int y = 3; y >= 0; y--)
		{
			for (int yy = y - 1; yy >= 0; yy--)
			{
				if (m_mySquare[x][yy]->getNumber()>0)
				{
					if (0 == m_mySquare[x][y]->getNumber())
					{
						m_mySquare[x][y]->setNumber(m_mySquare[x][yy]->getNumber());
						m_mySquare[x][yy]->setNumber(0);
						++y;
						isUp = true;
					}
					else if (m_mySquare[x][y]->getNumber() == m_mySquare[x][yy]->getNumber())
					{
						m_totalScore += m_mySquare[x][y]->getNumber() * 2;
						m_mySquare[x][y]->setNumber(m_mySquare[x][y]->getNumber() * 2);
						m_mySquare[x][yy]->setNumber(0);
						isUp = true;
					}
					break;
				}
			}
		}
	}
	return isUp;
}

//向下移动
bool HelloWorld::onDown()
{
	CCLOG("Left");

	bool isDown= false;

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int yy = y + 1; yy < 4; yy++)
			{
				if (m_mySquare[x][yy]->getNumber()>0)
				{
					if (0 == m_mySquare[x][y]->getNumber())
					{
						m_mySquare[x][y]->setNumber(m_mySquare[x][yy]->getNumber());
						m_mySquare[x][yy]->setNumber(0);
						--y;
						isDown = true;
					}
					else if (m_mySquare[x][y]->getNumber() == m_mySquare[x][yy]->getNumber())
					{
						m_totalScore += m_mySquare[x][y]->getNumber() * 2;
						m_mySquare[x][y]->setNumber(m_mySquare[x][y]->getNumber() * 2);
						m_mySquare[x][yy]->setNumber(0);
						isDown = true;
					}
					break;
				}
			}
		}
	}
	return isDown;
}

//游戏是否结束
bool HelloWorld::isOver()
{
	bool bRect = false;

	for (int x = 0; x < 4; x++)
	{
		if (bRect)
			break;
		for (int y = 0; y < 4; y++)
		{
			if (0==m_mySquare[x][y]->getNumber())
				bRect = true;
			else if (x != 0 && m_mySquare[x][y]->getNumber() == m_mySquare[x - 1][y]->getNumber())
				bRect = true;
			else if (x != 3 && m_mySquare[x][y]->getNumber() == m_mySquare[x + 1][y]->getNumber())
				bRect = true;
			else if (y != 3 && m_mySquare[x][y]->getNumber() == m_mySquare[x][y + 1]->getNumber())
				bRect = true;
			else if (y != 0 && m_mySquare[x][y]->getNumber() == m_mySquare[x][y - 1]->getNumber())
				bRect = true;
			if (bRect)
				break;
		}
	}

	return !bRect;;
}

//游戏是否胜利
bool HelloWorld::isWin()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (16 == m_mySquare[i][j]->getNumber())
				return true;

	return false;
}

//开始&结束菜单
void HelloWorld::startAndclose(Layer* layer, Vec2 start, Vec2 close)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//获取XML文本
	auto m_dictionary = Dictionary::createWithContentsOfFile("fonts/text.xml");

	// 退出游戏 按钮

	auto m_closeLabel = Label::createWithTTF(
		((__String*)(m_dictionary->objectForKey("close")))->getCString(),
		"fonts/DFPShaoNvW5-GB.ttf",
		35);
	m_closeLabel->setTextColor(Color4B(255, 255, 0, 255));

	auto closeItem = MenuItemLabel::create(m_closeLabel);
	closeItem->setPosition(close);
	closeItem->setAnchorPoint(Vec2(1.2, -0.5));
	closeItem->setTarget(this, menu_selector(HelloWorld::menuCloseCallback));

	// 重新开始 按钮

	auto m_reStartLabel = Label::createWithTTF(
		((__String*)(m_dictionary->objectForKey("restart")))->getCString(),
		"fonts/DFPShaoNvW5-GB.ttf",
		35);

	m_reStartLabel->setTextColor(Color4B(255, 255, 0, 255));

	auto reStartItem = MenuItemLabel::create(m_reStartLabel);
	reStartItem->setPosition(start);
	reStartItem->setAnchorPoint(Vec2(-0.2, -0.5));
	reStartItem->setTarget(this, menu_selector(HelloWorld::menuReStartCallback));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, reStartItem, nullptr);
	menu->setPosition(Vec2::ZERO);
	layer->addChild(menu, 1);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

// a selector callback
void HelloWorld::menuReStartCallback(cocos2d::Ref* pSender)
{
	auto m_scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0, m_scene));
}


// 帮助
void HelloWorld::menuHelpCallback(cocos2d::Ref* pSender)
{

}