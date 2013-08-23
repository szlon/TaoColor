#include "TableViewLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;


//------------------------------------------------------------------
//
// CustomTableViewCell
//
//------------------------------------------------------------------
void CustomTableViewCell::draw()
{
	CCTableViewCell::draw();	
}

//------------------------------------------------------------------
//
// ScrollViewLayer
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

	//CCTableView* tableView = CCTableView::create(this, CCSizeMake(VIEW_ITEM_SIZE * VIEW_COUNT, VIEW_ITEM_SIZE));
	CCTableView* tableView = MyTableView::create(this, CCSizeMake(m_ViewItemSize * VIEW_COUNT, m_ViewItemSize));
    tableView->setDirection(kCCScrollViewDirectionHorizontal);	  
    tableView->setDelegate(this);

	this->addChild(tableView);
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