#ifndef __APPMACROS_H__
#define __APPMACROS_H__

#include "cocos2d.h"

typedef struct tagResource
{
	cocos2d::CCSize size;
	char directory[100];
}Resource;

////���õ���Դ�ߴ�
//static Resource smallResource  =  { cocos2d::CCSizeMake(480, 320),   "iphone" };
//static Resource mediumResource =  { cocos2d::CCSizeMake(1024, 768),  "ipad"   };
//static Resource largeResource  =  { cocos2d::CCSizeMake(2048, 1536), "ipadhd" };

////��Ʒ���
//static cocos2d::CCSize smallDesignResolutionSize = cocos2d::CCSizeMake(480.0f, 320.0f);
//static cocos2d::CCSize mediumDesignResolutionSize = cocos2d::CCSizeMake(1024.0f, 768.0f);
//static cocos2d::CCSize largeDesignResolutionSize = cocos2d::CCSizeMake(2048.0f, 1536.0f);

//���õ���Դ�ߴ�
static Resource smallResource  =  { cocos2d::CCSizeMake(480, 320),  "HVGA" };
static Resource mediumResource =  { cocos2d::CCSizeMake(800, 480),  "WVGA" };
static Resource largeResource  =  { cocos2d::CCSizeMake(1280, 720), "720P" };


//��Ʒ���
static cocos2d::CCSize smallDesignResolutionSize = cocos2d::CCSizeMake(480.0f, 320.0f);
static cocos2d::CCSize mediumDesignResolutionSize = cocos2d::CCSizeMake(800.0f, 480.0f);
static cocos2d::CCSize largeDesignResolutionSize = cocos2d::CCSizeMake(1280.0f, 720.0f);

//�������ӣ���Ҫ�����ֱ�ǩʹ��
//#define SCALE_FACTOR  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / smallResource.size.width)
#define SCALE_FACTOR  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / largeResource.size.width)

#endif