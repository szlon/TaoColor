#ifndef __MYTABLEVIEW_H__
#define __MYTABLEVIEW_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include <stdio.h> 
//#include <sys/time.h> 
#include <time.h>


USING_NS_CC;
USING_NS_CC_EXT;

class MyTableView : public CCTableView
{
    public:
        bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
        void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
        void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

        static MyTableView* create(CCTableViewDataSource* dataSource, CCSize size);
        static MyTableView* create(CCTableViewDataSource* dataSource, CCSize size, CCNode *container);

    protected:
        CCPoint m_beginPoint;
        CCPoint m_lastPoint;
        struct timeval m_beginTime;
        struct timeval m_endTime;
};

class CustomTableViewCell : public cocos2d::extension::CCTableViewCell
{
public:
	virtual void draw();
};

#endif