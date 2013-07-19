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

    CCLayerGradient* pLayer = CCLayerGradient::create(ccc4(240,255,255,255), ccc4(64,224,208,255));
	CCSize frameSize = CCSize(VIEW_ITEM_SIZE * VIEW_COUNT, VIEW_ITEM_SIZE + 10);

	pLayer->setStartOpacity(240);
	pLayer->setEndOpacity(150);
	pLayer->setContentSize(frameSize);

	pLayer->ignoreAnchorPointForPosition(false);
	pLayer->setPosition(CCPointMake(winSize.width/2, frameSize.height / 2));



	TableViewLayer *pViewLayer = TableViewLayer::create();
	pViewLayer->SetStateChange(this);
	pViewLayer->setContentSize(frameSize);
	pViewLayer->ignoreAnchorPointForPosition(false);	

	
	pViewLayer->setPosition(CCPointMake(frameSize.width/2, frameSize.height/2 + 5));

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