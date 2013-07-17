#ifndef __RENDERDRAW_SCENE_H__
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

	virtual void ccTouchesMoved(CCSet* touches, CCEvent* event);

};
#endif