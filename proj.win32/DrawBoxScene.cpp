#include "DrawBoxScene.h"

void DrawBoxScene::onEnter()
{	    
	CCScene::onEnter();
    

 //   CCLabelTTF* label = CCLabelTTF::create("DrawBox", "Arial", 20);

	//CCSize size = CCDirector::sharedDirector()->getWinSize();

 //   label->setPosition( ccp(size.width / 2, size.height - 20) );

	//this->addChild(label);

    //addChild(label, 1);

	//CCLayer *layer = CCLayer::create();

	CCLayer *layer = new CanvasLayer();
	
	this->addChild(layer);

	//glLineWidth(2.0f);
	//ccDrawColor4B(0, 0, 255, 255);
	//ccDrawLine(ccp(10, 40), ccp(80, 80));

	//layer->addChild(label, 1);

	//layer->setPosition(10, -50);

	//addChild(layer);

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

	CCLabelTTF *label = CCLabelTTF::create("CanvasLayer", "Arial", 20);

	CCSize size = CCDirector::sharedDirector()->getWinSize();

    label->setPosition( ccp(size.width / 2, size.height - 20) );

	this->addChild(label);


	setTouchEnabled(true);

}

void CanvasLayer::draw()
{
	//CCLayer::draw();

	glLineWidth(40);

	int nCount = m_EntireList->count();
	for (int n = 0; n < nCount; n++)
	{
		CCArray *pointList = (CCArray *)m_EntireList->objectAtIndex(n);
		if (!pointList) continue;

		//ccDrawColor4B(rand() % 127 + 128, rand() % 127 + 128, rand() % 127 + 128, rand() % 127 + 128);

		ccDrawColor4B((n * 10) % 127 + 128, (n * 40) % 255, (n * 15) % 255, 230);

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

				ccDrawQuadBezier(ccp(pStart->x, pStart->y), ccp((pStart->x + pEnd->x)/2.0, (pStart->y + pEnd->y)/2.0), ccp(pEnd->x, pEnd->y), 50);

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

	//m_pEnd = &touch->getLocation();

    //CCPoint location = touch->getLocation();

    //CCPoint pos = CCPointZero;
    //if (m_background)
    //{
    //    pos = m_background->convertToWorldSpace(CCPointZero);
    //}

    //if (m_emitter != NULL)
    //{
    //    m_emitter->setPosition( ccpSub(location, pos) );    
    //}
}