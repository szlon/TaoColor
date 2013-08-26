#include "MenuLayer.h"
#include "TableViewLayer.h"
#include "BrushViewLayer.h"

USING_NS_CC;


//------------------------------------------------------------------
//
// MenuLayer
//
//------------------------------------------------------------------
void MenuLayer::onEnter()
{
	CCLayer::onEnter();

	TableViewLayer *pColorViewLayer = TableViewLayer::create();
	pColorViewLayer->SetStateChange(this);

	//pColorViewLayer->setContentSize(frameSize);
	//pLayer->addChild(pColorViewLayer);	

	BrushViewLayer *pBrushViewLayer = BrushViewLayer::create();
	pBrushViewLayer->SetStateChange(this);

	this->addChild(pBrushViewLayer);
	this->addChild(pColorViewLayer, 1, 102);

		

}

void MenuLayer::menuColorCallback(CCObject* pSender)
{
}

void MenuLayer::onBrushChanged(int index)
{
	if(!m_pStateChange) return;
	m_pStateChange->onBrushChanged(index);
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