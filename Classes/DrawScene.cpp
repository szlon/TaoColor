#include "DrawScene.h"

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

	CCLabelTTF *label = CCLabelTTF::create("TaoRender", "Arial", 20);

	CCSize size = CCDirector::sharedDirector()->getWinSize();

    label->setPosition( ccp(size.width / 2, size.height - 20) );

	this->addChild(label);


	//---------------------------------------------		
	CCMenuItemImage *pClearItem = CCMenuItemImage::create(
                                        "ClearNormal.png",
                                        "ClearSelected.png",
                                        this,
										menu_selector(DrawLayer::menuClearCallback) );

    pClearItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width / 2, 22) );


    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
										menu_selector(DrawLayer::menuCloseCallback) );

    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );


    CCMenu* pMenu = CCMenu::create(pClearItem, pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);


	initRenderTexture();

}

void DrawLayer::initRenderTexture()
{		
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	m_pTarget = CCRenderTexture::create(winSize.width, winSize.height, kCCTexture2DPixelFormat_RGBA8888);	    
	m_pTarget->retain();
    m_pTarget->setPosition(ccp(winSize.width / 2, winSize.height / 2));

	this->addChild(m_pTarget);

	m_pBrush = CCSprite::create("Images/Brush03.png");
	m_pBrush->retain();	    
	m_pBrush->setColor(ccYELLOW);
    m_pBrush->setOpacity(50);
	m_pBrush->setScale(0.5f);

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
    m_pTarget->clear(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1());
}

void DrawLayer::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}