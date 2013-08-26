#include "TableViewLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;


//------------------------------------------------------------------
//
// TableViewLayer
//
//------------------------------------------------------------------
bool TableViewLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
	CCSprite *sprite = CCSprite::create("Images/Circle.png");	
	m_ViewItemSize = sprite->getContentSize().width;
	sprite->release();




	//CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	//CCSprite *sprite = CCSprite::create("Images/Circle.png");	
	//int spriteItemSize = sprite->getContentSize().width;
	//sprite->release();

	//int viewCount = winSize.width * 0.8 / spriteItemSize;
	CCLayerGradient* pLayer = CCLayerGradient::create(ccc4(245,245,245,255), ccc4(223,224,228,155));
	CCSize frameSize = CCSize(m_ViewItemSize * VIEW_COUNT, m_ViewItemSize);

	pLayer->setStartOpacity(240);
	pLayer->setEndOpacity(150);
	pLayer->setContentSize(frameSize);

	pLayer->setPosition(ccpAdd(VisibleRect::bottom(),
		ccp(-pLayer->getContentSize().width / 2, 0 //pLayer->getContentSize().height / 4
		)));




	//CCTableView* tableView = CCTableView::create(this, CCSizeMake(VIEW_ITEM_SIZE * VIEW_COUNT, VIEW_ITEM_SIZE));
	CCTableView* tableView = MyTableView::create(this, frameSize);
    tableView->setDirection(kCCScrollViewDirectionHorizontal);	  
    tableView->setDelegate(this);

	pLayer->addChild(tableView);
	this->addChild(pLayer);
    
	tableView->reloadData();
	  
	return true;
}


void TableViewLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    //CCLOG("cell touched at index: %i", );
	ccColor3B color = RGBToColor3B(RGBTable[cell->getIdx()]);
	onColorChanged(color);
}

CCSize TableViewLayer::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(m_ViewItemSize, m_ViewItemSize);
}

CCTableViewCell* TableViewLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	ccColor3B color = RGBToColor3B(RGBTable[idx]);
    CCTableViewCell *cell = table->dequeueCell();

	float scaleFactor = CCDirector::sharedDirector()->getContentScaleFactor();

	//float scf = (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / largeResource.size.width);
	if (!cell) 
	{
        cell = new CustomTableViewCell();
        cell->autorelease();
        CCSprite *sprite = CCSprite::create("Images/Circle.png");	
		//CCSize ss1 = sprite->getContentSize();
        sprite->setAnchorPoint(CCPointZero);
		//sprite->setScale(scaleFactor);
		sprite->setColor(color);
		sprite->setTag(120);

        cell->addChild(sprite);

    }
    else
    {
		CCSprite *sprite = (CCSprite *)cell->getChildByTag(120);
		sprite->setColor(color);
    }

    return cell;
}

unsigned int TableViewLayer::numberOfCellsInTableView(CCTableView *table)
{
	return RGBTABLE_COUNT;
}

void TableViewLayer::onColorChanged(ccColor3B color)
{
	if(!m_pStateChange) return;
	m_pStateChange->onColorChanged(color);

}

void TableViewLayer::SetStateChange(StateChange *pStateChange)
{
	m_pStateChange = pStateChange;
}