#include "DrawScene.h"
#include "TableViewLayer.h"
#include "MenuLayer.h"

USING_NS_CC;


//------------------------------------------------------------------
//
// DrawScene
//
//------------------------------------------------------------------
void DrawScene::onEnter()
{	    
	CCScene::onEnter();
    
	CCLayer *layer = new DrawLayer();
	this->addChild(layer);

}

//------------------------------------------------------------------
//
// DrawLayer
//
//------------------------------------------------------------------
void DrawLayer::onEnter()
{
    CCLayer::onEnter();

	this->setTouchEnabled(true);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCLabelTTF *label = CCLabelTTF::create("TaoColor", "Arial", 20);
	
	label->setPosition( ccp(winSize.width / 2, winSize.height - 20) );
	label->setColor(ccBLACK);

	this->addChild(label, 1, 201);


	//---------------------------------------------		
	CCMenuItemImage *pClearItem = CCMenuItemImage::create(
                                        "ClearNormal.png",
                                        "ClearSelected.png",
                                        this,
										menu_selector(DrawLayer::menuClearCallback) );



    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
										menu_selector(DrawLayer::menuCloseCallback) );

	pClearItem->setPosition( ccp(winSize.width - 170, winSize.height - 60) );
    pCloseItem->setPosition( ccp(winSize.width - 70, winSize.height - 60) );


    CCMenu* pMenu = CCMenu::create(pClearItem, pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);


	MenuLayer * pMenuLayer = new MenuLayer();
	pMenuLayer->SetStateChange(this);
	pMenuLayer->autorelease();


	this->addChild(pMenuLayer, 2, 101);

	//pMenuLayer->setVisible(false);

	initRenderTexture();

}

void DrawLayer::initRenderTexture()
{		
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	m_pTarget = CCRenderTexture::create(winSize.width, winSize.height, kCCTexture2DPixelFormat_RGBA8888);	    
	m_pTarget->retain();
    m_pTarget->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    
	m_bClearState = false;

	//m_pTarget->clear(0,0,0,0);
	m_pTarget->clear(255,255,255,255);

	this->addChild(m_pTarget, 0);

	m_pBrush = CCSprite::create("Images/Brush03.png");
	m_pBrush->retain();	    
	m_pBrush->setColor(ccBLACK);
    m_pBrush->setOpacity(100);
	//m_pBrush->setScale(0.5f);

}


void DrawLayer::registerWithTouchDispatcher()
{	    
	CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addStandardDelegate(this, kCCMenuHandlerPriority);

}

void DrawLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *pTouch = (CCTouch *)pTouches->anyObject();	    
	CCPoint start = pTouch->getLocation();
    CCPoint end = pTouch->getPreviousLocation();


    m_pTarget->begin();

	m_pBrush->setPosition(ccp(start.x, start.y));
	m_pBrush->visit();
    m_pTarget->end();

}

void DrawLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
}

void DrawLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *pTouch  = (CCTouch *)pTouches->anyObject();
    CCPoint start = pTouch->getLocation();
    CCPoint end = pTouch->getPreviousLocation();

    m_pTarget->begin();

    float distance = ccpDistance(start, end);
    if (distance > 1)
    {
        int d = (int)distance;
        for (int i = 0; i < d; i++)
        {
            float difx = end.x - start.x;
            float dify = end.y - start.y;
            float delta = (float)i / distance;

			//delta = CCRANDOM_0_1() * delta;
            
			m_pBrush->setPosition(ccp(start.x + (difx * delta), start.y + (dify * delta)));

            m_pBrush->visit();
        }
    }

    m_pTarget->end();
}


void DrawLayer::menuClearCallback(CCObject* pSender)
{	    
	//清屏（改变背景色）
	m_bClearState = !m_bClearState;
	if(m_bClearState)
	{
		m_pTarget->clear(0,0,0, 10);
	}
	else
	{
		m_pTarget->clear(255,255,255,255);
	}

    //m_pTarget->clear(0,0,0, 10);
	//m_pTarget->clear(255,255,255,255);
	//m_pTarget->clear(37,43,48,255);


	//CCLayer * pMenuLayer = (CCLayer *)this->getChildByTag(101);
	//pMenuLayer->setVisible(true);


    //m_pTarget->clear(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1());

}

void DrawLayer::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void DrawLayer::onColorChanged(ccColor3B color)
{
	//当前颜色选择
	CCString *colorStr = CCString::createWithFormat("%X", color);
	//CCLOG("%s", colorStr->getCString());

	CCLabelTTF *label = (CCLabelTTF *)this->getChildByTag(201);
	//label->setString(colorStr->getCString());
	label->setColor(color);

	m_pBrush->setColor(color);

}


