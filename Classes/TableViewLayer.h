#ifndef __TABLEVIEW_LAYER_H__
#define __TABLEVIEW_LAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "BaseTypes.h"

#include "MyTableView.h"

#define  VIEW_ITEM_SIZE		96
#define  VIEW_COUNT			10

class CustomTableViewCell : public cocos2d::extension::CCTableViewCell
{
public:
	virtual void draw();
};

class TableViewLayer : public cocos2d::CCLayer, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
//class TableViewLayer : public cocos2d::CCLayer, MyTableView, public cocos2d::extension::CCTableViewDelegate
{
private:
	StateChange *m_pStateChange;

public:
    virtual bool init();  

    CREATE_FUNC(TableViewLayer);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}

    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	//接口
	virtual void onColorChanged(cocos2d::ccColor3B color);
	void SetStateChange(StateChange *pStateChange);

};

#endif