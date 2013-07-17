#include "DrawBoxScene.h"

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

void DrawBoxScene::onEnter()
{	    
	CCScene::onEnter();
    
	CCLayer *layer = new CanvasLayer();
	
	this->addChild(layer);


}

//------------------------------------------------------------------
//
// CanvasLayer
//
//------------------------------------------------------------------
void CanvasLayer::onEnter()
{
    CCLayer::onEnter();
	    
	//m_PointList = new CCArray();
	//m_PointList->retain();

	m_EntireList = new CCArray();
	m_EntireList->retain();

	CCLabelTTF *label = CCLabelTTF::create("TaoColor", "Arial", 20);

	CCSize size = CCDirector::sharedDirector()->getWinSize();

    label->setPosition( ccp(size.width / 2, size.height - 20) );

	this->addChild(label);

	setTouchEnabled(true);


	//---------------------------------------------		
	CCMenuItemImage *pClearItem = CCMenuItemImage::create(
                                        "ClearNormal.png",
                                        "ClearSelected.png",
                                        this,
										menu_selector(CanvasLayer::menuClearCallback) );

    pClearItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width / 2, 22) );


    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
										menu_selector(CanvasLayer::menuCloseCallback) );

    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );


    CCMenu* pMenu = CCMenu::create(pClearItem, pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

	//----------------------------------------------------------------------------

	CCSpriteBatchNode * batchNode = CCSpriteBatchNode::create("Images/SpriteTextures.png", 50);	//128x192
	addChild(batchNode, 0, kTagSpriteBatchNode);

	//----------------------------------------------------------------------------


	initBatchSprite();

	initRenderTexture();
}

void CanvasLayer::initRenderTexture()
{		
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	m_pTarget = CCRenderTexture::create(winSize.width, winSize.height, kCCTexture2DPixelFormat_RGBA8888);	    
	m_pTarget->retain();
    m_pTarget->setPosition(ccp(winSize.width / 2, winSize.height / 2));

	this->addChild(m_pTarget);

	m_pBrush = CCSprite::create("Images/Brush1.png");
	m_pBrush->retain();	    
	m_pBrush->setColor(ccRED);
    m_pBrush->setOpacity(20);


    this->setTouchEnabled(true);


}

void CanvasLayer::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
    CCTouch *touch = (CCTouch *)touches->anyObject();
    CCPoint start = touch->getLocation();
    CCPoint end = touch->getPreviousLocation();

    // begin drawing to the render texture
    m_pTarget->begin();

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
            m_pBrush->setPosition(ccp(start.x + (difx * delta), start.y + (dify * delta)));
            m_pBrush->setRotation(rand() % 360);
            float r = (float)(rand() % 50 / 50.f) + 0.25f;
            m_pBrush->setScale(r);
            /*m_pBrush->setColor(ccc3(CCRANDOM_0_1() * 127 + 128, 255, 255));*/
            // Use CCRANDOM_0_1() will cause error when loading libtests.so on android, I don't know why.
            m_pBrush->setColor(ccc3(rand() % 127 + 128, 255, 255));
            // Call visit to draw the brush, don't call draw..
            m_pBrush->visit();
        }
    }

    // finish drawing and return context back to the screen
    m_pTarget->end();
}


void CanvasLayer::initBatchSprite()
{
	int rowCount = 4;
	int colCount = 4;
	int x = 0;
	int y = 0;

	CCSpriteBatchNode * batchNode = (CCSpriteBatchNode *)getChildByTag(kTagSpriteBatchNode);

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSize textureSize = batchNode->getTexture()->getContentSize();

	int width = textureSize.width / colCount;
	int height = textureSize.height / rowCount;

	int totalCount = colCount * rowCount;
	for (int i = 0; i < totalCount; i++ )
	{
		x = (i % colCount) * width;
		y = (i / rowCount) * height;
			
		CCSprite *sprite = CCSprite::createWithTexture(batchNode->getTexture(), CCRectMake(x, y, width, height));	
		
		sprite->setPosition(ccp(size.width - x - width, size.height - y - height));
			
		//sprite->setVisible(false);

		batchNode->addChild(sprite, 100, 100 + i);
	}

	//schedule(schedule_selector(CanvasLayer::runlogic), 1);

}


void CanvasLayer::runlogic(float dt)
{
	CCSpriteBatchNode * batchNode = (CCSpriteBatchNode *)getChildByTag(kTagSpriteBatchNode);

	int index = rand() % 15;
	CCSprite *sprite = (CCSprite *)batchNode->getChildByTag(100 + index);
	sprite->setVisible(true);

	int imgWidth = 32;
	int imgHeight = 48;
	
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();  

	int minY = imgHeight/2;  
    int maxY = winSize.height - imgHeight/2;
	int minX = imgWidth/2;
	int maxX = winSize.width - imgWidth/2;
 
	int rangeY = maxY - minY;       
	int rangeX = maxX - minX;

	int actualY = ( rand() % rangeY ) + minY; 
	int actualX = ( rand() % rangeX ) + minX;

	sprite->setPosition(ccp(actualX, actualY));


}

void CanvasLayer::draw()
{
	//CCLayer::draw();

	//glLineWidth(40);

	int nCount = m_EntireList->count();
	for (int n = 0; n < nCount; n++)
	{
		CCArray *pointList = (CCArray *)m_EntireList->objectAtIndex(n);
		if (!pointList) continue;

		//ccDrawColor4B(rand() % 127 + 128, rand() % 127 + 128, rand() % 127 + 128, rand() % 127 + 128);

		ccDrawColor4B((n * 5) % 55 + 200, (n * 20) % 50 + 205, (n * 15) % 200 + 55, 230);

		int count = pointList->count();

		for(int i = 0; i < count; i++)
		{
			CCPoint * pEnd = (CCPoint *)pointList->objectAtIndex(i);
			if(i == 0)
			{
				ccDrawPoint(ccp(pEnd->x, pEnd->y));
			}
			else
			{
				CCPoint * pStart = (CCPoint *)pointList->objectAtIndex(i - 1);
				//CCPoint * ppEnd =  (CCPoint *)this->m_PointList->objectAtIndex(i + 1);

				float dx = abs(pStart->x - pEnd->x);
				float dy = abs(pStart->y - pEnd->y);

				//if(dx >= 4 || dy >= 4)
				//{
					ccDrawQuadBezier(ccp(pStart->x, pStart->y), ccp((pStart->x + pEnd->x)/2.0, (pStart->y + pEnd->y)/2.0), ccp(pEnd->x, pEnd->y), 50);
				//}
				//else
				//{

				//} 
					//ccDrawLine(ccp(pStart->x, pStart->y), ccp(pEnd->x, pEnd->y));
					
				//ccDrawColor4B(0, 255, 0, 100);				
				//ccDrawQuadBezier(ccp(pStart->x, pStart->y), ccp(pEnd->x, pEnd->y),ccp(ppEnd->x, ppEnd->y), 50);

				//ccDrawColor4B(155, 255, 255, 200);
				//ccDrawLine(ccp(pStart->x, pStart->y),ccp(pEnd->x, pEnd->y));


			}		

		}
	

	}
	

	//if(this->m_PointList)
	//{
	//	int count = m_PointList->count();

	//	for(int i = 0; i < count; i++)
	//	{
	//		CCPoint * pEnd = (CCPoint *)this->m_PointList->objectAtIndex(i);
	//		if(i == 0)
	//		{
	//			ccDrawPoint(ccp(pEnd->x, pEnd->y));
	//		}
	//		else
	//		{
	//			CCPoint * pStart = (CCPoint *)this->m_PointList->objectAtIndex(i - 1);
	//			//CCPoint * ppEnd =  (CCPoint *)this->m_PointList->objectAtIndex(i + 1);
	//				
	//
	//			//ccDrawColor4B(255, 0, 0, 200);
	//			//ccDrawQuadBezier(ccp(pStart->x, pStart->y), ccp((pStart->x + pEnd->x)/2.0, (pStart->y + pEnd->y)/2.0), ccp(pEnd->x, pEnd->y), 50);

	//			//ccDrawColor4B(0, 255, 0, 100);				
	//			//ccDrawQuadBezier(ccp(pStart->x, pStart->y), ccp(pEnd->x, pEnd->y),ccp(ppEnd->x, ppEnd->y), 50);

	//			ccDrawColor4B(155, 255, 255, 200);
	//			ccDrawLine(ccp(pStart->x, pStart->y),ccp(pEnd->x, pEnd->y));


	//		}		

	//	}
	//}

}


void CanvasLayer::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}


bool CanvasLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{		
	m_PointList = new CCArray();
	m_PointList->retain();

	m_EntireList->addObject(m_PointList);

	CCPoint *point = new CCPoint(touch->getLocation().x, touch->getLocation().y);

	m_PointList->addObject(point);

	point->release();


    return true;
}

void CanvasLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	//CCPoint *point = new CCPoint(touch->getLocation().x, touch->getLocation().y);

	//m_PointList->addObject(point);

	//point->release();
    return ccTouchEnded(touch, event);
}

void CanvasLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{		
	CCPoint *point = new CCPoint(touch->getLocation().x, touch->getLocation().y);

	m_PointList->addObject(point);

	point->release();

}


void CanvasLayer::menuClearCallback(CCObject* pSender)
{
	this->m_EntireList->removeAllObjects();
}

void CanvasLayer::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}