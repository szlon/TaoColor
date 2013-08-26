#include "BrushViewLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;


//------------------------------------------------------------------
//
// BrushViewLayer
//
//------------------------------------------------------------------
bool BrushViewLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
	CCSprite *sprite = CCSprite::create("Images/Circle.png");	
	m_ViewItemSize = sprite->getContentSize().width;
	sprite->release();


	CCLayerGradient* pLayer = CCLayerGradient::create(ccc4(245,245,245,255), ccc4(223,224,228,155));
	CCSize frameSize = CCSize(m_ViewItemSize, m_ViewItemSize * VIEW_COUNT);

	pLayer->setStartOpacity(240);
	pLayer->setEndOpacity(150);
	pLayer->setContentSize(frameSize);

	pLayer->setPosition(ccpAdd(VisibleRect::right(),
		ccp(-pLayer->getContentSize().width, -pLayer->getContentSize().height / 2)));



	CCTableView* tableView = MyTableView::create(this, frameSize);
    tableView->setDirection(kCCScrollViewDirectionVertical);	  
    tableView->setDelegate(this);

	pLayer->addChild(tableView);
	this->addChild(pLayer);
    tableView->reloadData();
	  
	return true;
}


void BrushViewLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	//ccColor3B color = RGBToColor3B(RGBTable[cell->getIdx()]);
	//onColorChanged(color);
	onBrushChanged(cell->getIdx());
}

CCSize BrushViewLayer::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(m_ViewItemSize, m_ViewItemSize);
}

CCTableViewCell* BrushViewLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	//ccColor3B color = RGBToColor3B(RGBTable[idx]);
	ccColor3B color = ccBLACK;
	
	CCString *strBrush = CCString::createWithFormat("Brushes/Brush%d.png", idx);

    CCTableViewCell *cell = table->dequeueCell();

	float scaleFactor = CCDirector::sharedDirector()->getContentScaleFactor();

	//float scf = (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / largeResource.size.width);
	if (!cell) 
	{
        cell = new CustomTableViewCell();
        cell->autorelease();
		//CCSprite *sprite = CCSprite::create("Brushes/Brush1.png");	
        CCSprite *sprite = CCSprite::create(strBrush->getCString());	
        sprite->setAnchorPoint(CCPointZero);
		sprite->setColor(color);
		sprite->setTag(121);

        cell->addChild(sprite);

    }
    else
    {
		CCSprite *sprite = (CCSprite *)cell->getChildByTag(121);
		sprite->setColor(color);
    }

    return cell;
}

unsigned int BrushViewLayer::numberOfCellsInTableView(CCTableView *table)
{
	return BRUSHES_COUNT;
}


void BrushViewLayer::onBrushChanged(int index)
{
	if(!m_pStateChange) return;
	m_pStateChange->onBrushChanged(index);

}

void BrushViewLayer::SetStateChange(StateChange *pStateChange)
{
	m_pStateChange = pStateChange;
}