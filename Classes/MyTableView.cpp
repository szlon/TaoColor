#include "MyTableView.h"
#include <stdlib.h>

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
// MyTableView
//
//------------------------------------------------------------------
MyTableView* MyTableView::create(CCTableViewDataSource* dataSource, CCSize size)
{
    return MyTableView::create(dataSource, size, NULL);
}

MyTableView* MyTableView::create(CCTableViewDataSource* dataSource, CCSize size, CCNode *container)
{
    MyTableView *table = new MyTableView();
    table->initWithViewSize(size, container);
    table->autorelease();
    table->setDataSource(dataSource);
    table->_updateContentSize();

    return table;
}

bool MyTableView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    m_beginPoint = pTouch->getLocation();
    ::gettimeofday(&m_beginTime, NULL);
    //CCLog("touch begin");
    return CCTableView::ccTouchBegan(pTouch, pEvent);

}

void MyTableView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    m_lastPoint = pTouch->getLocation();
    CCTableView::ccTouchMoved(pTouch, pEvent);
}

void MyTableView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	m_lastPoint = pTouch->getLocation();

	//CCLog("touch end");
    ::gettimeofday(&m_endTime, NULL);

    if (!this->isVisible()) { return; }

    /// 判断是否有移动
    bool isTouchMove = true;
    float moveRange = 30; // 移动范围小于10个像素
    
	//CCLog("bt:%d,%d", m_beginTime.tv_sec, m_beginTime.tv_usec);
    //CCLog("et:%d,%d", m_endTime.tv_sec, m_endTime.tv_usec);
    
	long timediff = m_endTime.tv_sec - m_beginTime.tv_sec;

    timediff = timediff* 1000 + (m_endTime.tv_usec - m_beginTime.tv_usec)/1000;
    
	//CCLog("timediff:%ld", timediff);
    
	// 触屏时间少于150ms
    if (timediff < 250) 
	{
        float dx = m_beginPoint.x - m_lastPoint.x;
        float dy = m_beginPoint.y - m_lastPoint.y;
        //CCLog("bp:%f,%f", m_beginPoint.x, m_beginPoint.y);
        //CCLog("ep:%f,%f, %f, %f", m_lastPoint.x, m_lastPoint.y, dx, dy);
        
		if ((-moveRange < dx &&  dx < moveRange) && (-moveRange < dy && dy < moveRange)) 
		{
            isTouchMove = false;
        }

    }

    if (m_pTouches->count() == 1 && !isTouchMove) 
	{
        //CCLog("CCTableView::ccTouchEnded not move");
        unsigned int        index;
        CCTableViewCell   *cell;
        CCPoint           point;
        
        point = this->getContainer()->convertTouchToNodeSpace(pTouch);
        
		if (m_eVordering == kCCTableViewFillTopDown) 
		{
            CCSize cellSize = m_pDataSource->cellSizeForTable(this);
            point.y -= cellSize.height;
        }

        index = this->_indexFromOffset(point);
        cell  = this->_cellWithIndex(index);
        
        if (cell) 
		{
            m_pTableViewDelegate->tableCellTouched(this, cell);
        }

    }

    CCScrollView::ccTouchEnded(pTouch, pEvent);

}