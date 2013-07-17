#ifndef __DRAW_SCENE_H__
#define __DRAW_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class DrawScene :public CCScene
{
public:
	virtual void onEnter();		
};


class DrawLayer : public CCLayer
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

};
#endif