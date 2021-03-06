﻿#ifndef __RENDERDRAW_SCENE_H__
#define __RENDERDRAW_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class RenderDrawScene :public CCScene
{
public:
	virtual void onEnter();		
};


class RenderLayer : public CCLayer
{
protected:	    
	CCRenderTexture *m_pTarget;
    CCSprite *m_pBrush;

public:

	virtual void onEnter();

	void menuClearCallback(CCObject* pSender);
	void menuCloseCallback(CCObject* pSender);
			
	void initRenderTexture();
	
	virtual void registerWithTouchDispatcher();

	// addStandardDelegate()
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    //virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

    // addTargetedDelegate()
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    //virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
};
#endif