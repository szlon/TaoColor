#ifndef __DRAW_SCENE_H__
#define __DRAW_SCENE_H__

#include "cocos2d.h"
#include "BaseTypes.h"

class DrawScene :public cocos2d::CCScene
{
public:
	virtual void onEnter();		
};


class DrawLayer : public cocos2d::CCLayer, public StateChange
{
protected:	    
	cocos2d::CCRenderTexture *m_pTarget;
	cocos2d::CCSprite *m_pBrush;
	bool m_bClearState;

public:
	virtual void onEnter();

	virtual void keyBackClicked();
	virtual void keyMenuClicked();

	void menuClearCallback(CCObject* pSender);
	void menuCloseCallback(CCObject* pSender);
			
	void initRenderTexture();
	
	virtual void registerWithTouchDispatcher();

	// addStandardDelegate()
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    //virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

	//接口
	virtual void onColorChanged(cocos2d::ccColor3B color);

};



#endif