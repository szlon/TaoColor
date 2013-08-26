#ifndef __MENU_LAYER_H__
#define __MENU_LAYER_H__

#include "cocos2d.h"
#include "BaseTypes.h"


class MenuLayer : public cocos2d::CCLayer, public StateChange
{
private:
	StateChange *m_pStateChange;
public:
	virtual void onEnter();
	void menuColorCallback(cocos2d::CCObject* pSender);

	//接口
	virtual void onBrushChanged(int index);
	virtual void onColorChanged(cocos2d::ccColor3B color);
	void SetStateChange(StateChange *pStateChange);

};


#endif