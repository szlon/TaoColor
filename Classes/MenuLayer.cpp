#include "MenuLayer.h"
#include "TableViewLayer.h"

USING_NS_CC;


//------------------------------------------------------------------
//
// MenuLayer
//
//------------------------------------------------------------------
void MenuLayer::onEnter()
{
	CCLayer::onEnter();


	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	//CCLayerColor *pLayerColor = CCLayerColor::create(ccc4(30, 100, 200,  120), 100, 60);
	CCSprite *sprite = CCSprite::create("Images/Circle.png");	
	int spriteItemSize = sprite->getContentSize().width;
	sprite->release();

	int viewCount = winSize.width * 0.8 / spriteItemSize;
    CCLayerGradient* pLayer = CCLayerGradient::create(ccc4(245,245,245,255), ccc4(223,224,228,155));
	CCSize frameSize = CCSize(spriteItemSize * VIEW_COUNT, spriteItemSize);
	//frameSize = CCDirector::sharedDirector()->getVisibleSize();

	//float scf = SCALE_FACTOR;
	//CCDirector::sharedDirector()->getWinSize();

	//pLayer->setScale(scf);
	pLayer->setStartOpacity(240);
	pLayer->setEndOpacity(150);
	pLayer->setContentSize(frameSize);

	//pLayer->ignoreAnchorPointForPosition(false);
	//pLayer->setPosition(CCPointMake(winSize.width/2, frameSize.height / 2));
	pLayer->setPosition(ccpAdd(VisibleRect::bottom(),
		ccp(-pLayer->getContentSize().width / 2, 0, //pLayer->getContentSize().height / 4
		)));



	TableViewLayer *pViewLayer = TableViewLayer::create();
	pViewLayer->SetStateChange(this);
	pViewLayer->setContentSize(frameSize);

		
	//pViewLayer->setPosition(CCPointMake(frameSize.width/2, frameSize.height/2 + 5));

	//pViewLayer->setPosition(VisibleRect::center());

	pLayer->addChild(pViewLayer);


	
	this->addChild(pLayer, 1, 102);

		

}

void MenuLayer::menuColorCallback(CCObject* pSender)
{
}

void MenuLayer::onColorChanged(ccColor3B color)
{
	if(!m_pStateChange) return;
	m_pStateChange->onColorChanged(color);

}
void MenuLayer::SetStateChange(StateChange *pStateChange)
{
	m_pStateChange = pStateChange;
}