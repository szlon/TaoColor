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
	    
	CCRenderTexture *m_pTarget;
    CCSprite *m_pBrush;

public:
	virtual void onEnter();
    virtual void draw();
	virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	  

	void initBatchSprite();
	void runlogic(float dt);

	void initRenderTexture();

	void menuClearCallback(CCObject* pSender);
	void menuCloseCallback(CCObject* pSender);
	    
	virtual void ccTouchesMoved(CCSet* touches, CCEvent* event);

};
#endif