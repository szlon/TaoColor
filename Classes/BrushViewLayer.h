#ifndef __BRUSHVIEW_LAYER_H__
#define __BRUSHVIEW_LAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "BaseTypes.h"

#include "MyTableView.h"

#define  VIEW_COUNT			4

class BrushViewLayer : public cocos2d::CCLayer, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
private:
	StateChange *m_pStateChange;
	int m_ViewItemSize;
public:
    virtual bool init();  

    CREATE_FUNC(BrushViewLayer);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}

    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	//接口
	virtual void onBrushChanged(int index);
	void SetStateChange(StateChange *pStateChange);

};

#endif