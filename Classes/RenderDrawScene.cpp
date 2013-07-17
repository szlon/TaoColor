#include "RenderDrawScene.h"

#define SPRITE_INDEX    100

enum 
{
    kTagTileMap = 1,
    kTagSpriteBatchNode = 1,
    kTagNode = 2,
    kTagAnimation1 = 1,
    kTagSpriteDown,
    kTagSpriteLeft,
    kTagSpriteRight,
    kTagSpriteUP,

};

void RenderDrawScene::onEnter()
{	    
	CCScene::onEnter();
    
	CCLayer *layer = new RenderLayer();
	
	this->addChild(layer);


}

//------------------------------------------------------------------
//
// CanvasLayer
//
//------------------------------------------------------------------
void RenderLayer::onEnter()
{
    CCLayer::onEnter();

	CCLabelTTF *label = CCLabelTTF::create("TaoRender", "Arial", 20);

	CCSize size = CCDirector::sharedDirector()->getWinSize();

    label->setPosition( ccp(size.width / 2, size.height - 20) );

	this->addChild(label);

	setTouchEnabled(true);


	//---------------------------------------------		
	CCMenuItemImage *pClearItem = CCMenuItemImage::create(
                                        "ClearNormal.png",
                                        "ClearSelected.png",
                                        this,
										menu_selector(RenderLayer::menuClearCallback) );

    pClearItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width / 2, 22) );


    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
										menu_selector(RenderLayer::menuCloseCallback) );

    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );


    CCMenu* pMenu = CCMenu::create(pClearItem, pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

	//----------------------------------------------------------------------------

	CCSpriteBatchNode * batchNode = CCSpriteBatchNode::create("Images/SpriteTextures.png", 50);	//128x192
	addChild(batchNode, 0, kTagSpriteBatchNode);

	//----------------------------------------------------------------------------


	initRenderTexture();

}

void RenderLayer::initRenderTexture()
{		
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	m_pTarget = CCRenderTexture::create(winSize.width, winSize.height, kCCTexture2DPixelFormat_RGBA8888);	    
	m_pTarget->retain();
    m_pTarget->setPosition(ccp(winSize.width / 2, winSize.height / 2));

	this->addChild(m_pTarget);

	m_pBrush = CCSprite::create("Images/Brush03.png");
	m_pBrush->retain();	    
	//m_pBrush->setColor(ccRED);
    m_pBrush->setOpacity(50);

	m_pBrush->setScale(0.5f);

    this->setTouchEnabled(true);


}

void RenderLayer::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
    CCTouch *touch = (CCTouch *)touches->anyObject();
    CCPoint start = touch->getLocation();
    CCPoint end = touch->getPreviousLocation();

    // begin drawing to the render texture
    m_pTarget->begin();

	//m_pBrush->setPosition(ccp(start.x, start.y));
	//m_pBrush->visit();
    // for extra points, we'll draw this smoothly from the last position and vary the sprite's
    // scale/rotation/offset
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
            //m_pBrush->setRotation(rand() % 360);
            //float r = (float)(rand() % 50 / 50.f) + 0.25f;
            //m_pBrush->setScale(r);
            ///*m_pBrush->setColor(ccc3(CCRANDOM_0_1() * 127 + 128, 255, 255));*/
            //// Use CCRANDOM_0_1() will cause error when loading libtests.so on android, I don't know why.
            ////m_pBrush->setColor(ccc3(rand() % 127 + 128, 255, 255));
            //// Call visit to draw the brush, don't call draw..
            m_pBrush->visit();
        }
    }

    // finish drawing and return context back to the screen
    m_pTarget->end();
}


void RenderLayer::menuClearCallback(CCObject* pSender)
{
    m_pTarget->clear(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1());
}

void RenderLayer::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}