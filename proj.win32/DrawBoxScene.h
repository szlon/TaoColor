#ifndef __DRAWBOXSCENE_SCENE_H__
#define __DRAWBOXSCENE_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class DrawBoxScene :public CCScene
{
public:
	virtual void onEnter();
		

};


class CanvasLayer : public CCLayerColor
{
protected:
	CCArray * m_PointList;
	CCArray * m_EntireList;
public:
	virtual void onEnter();
    virtual void draw();
	virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

};
#endif