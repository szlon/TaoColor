﻿#ifndef __BASE_TYPES_H__
#define __BASE_TYPES_H__

#include "cocos2d.h"
#include "AppMacros.h"
#include "VisibleRect.h"


#define  BRUSHES_COUNT  3

//#define  RGBTABLE_COUNT  106
//
//const int RGBTable[RGBTABLE_COUNT] = 
//{
//	0xFF0000,	//Red
//	0xFF6100,	//Orange
//	0xFFFF00,	//Yellow
//	0x00FF00,	//Green
//	0x00FFFF,	//Cyan
//	0x0000FF,	//Blue
//	0xA020F0,	//Purple
//
//	0x000000, 0x292421, 0xC0C0C0, 0x808A87, 0x708069, 0x808069, 0xFFFFFF, 0xFAEBD7, 0xF0FFFF, 0xF5F5F5, 
//	0xFFFFCD, 0xFFF8DC, 0xFCE6C9, 0xFFFAF0, 0xDCDCDC, 0xF8F8FF, 0xF0FFF0, 0xFAFFF0, 0xFAF0E6, 0xFFDEAD, 
//	0xFDF5E6, 0xFFF5EE, 0xFFFAFA, 0xFF0000, 0x9C661F, 0xE3170D, 0xFF7F50, 0xB22222, 0xB0171F, 0xB03060, 
//	0xFFC0CB, 0x872657, 0xFA8072, 0xFF6347, 0xFF4500, 0xFF00FF, 0xFFFF00, 0xE3CF57, 0xFF9912, 0xEB8E55, 
//	0xFFE384, 0xFFD700, 0xDAA569, 0xE3A869, 0xFF6100, 0xFF6103, 0xED9121, 0xFF8000, 0xF5DEB3, 0x802A2A, 
//	0xA39480, 0x8A360F, 0x873324, 0xD2691E, 0xFF7D40, 0xF0E68C, 0xBC8F8F, 0xC76114, 0x734A12, 0x5E2612, 
//	0xA0522D, 0x8B4513, 0xF4A460, 0xD2B48C, 0x0000FF, 0x3D59AB, 0x1E90FF, 0x0B1746, 0x03A89E, 0x191970, 
//	0x33A1C9, 0x00C78C, 0xB0E0E6, 0x4169E1, 0x6A5ACD, 0x87CEEB, 0x00FFFF, 0x385E0F, 0x082E54, 0x7FFFD4, 
//	0x40E0D0, 0x00FF00, 0x7FFF00, 0x3D9140, 0x00C957, 0x228B22, 0x7CFC00, 0x32CD32, 0xBDFCC9, 0x6B8E23, 
//	0x308014, 0x2E8B57, 0x00FF7F, 0xA020F0, 0x8A2BE2, 0xA066D3, 0x9933FA, 0xDA70D6, 0xDDA0DD,
//
//
//};

#define  RGBTABLE_COUNT  32

const int RGBTable[RGBTABLE_COUNT] = 
{
	//基本色
	0xFF0000, 0xFF6100, 0xFFFF00, 0x00FF00,	
	0x00FFFF, 0x0000FF, 0xA020F0, 
	0xFFFFFF, 0x000000,

	//24色环
	0xC51578, 0xDB146F, 0xDA1C5A, 0xDA2045, 
	0xD72229,0xE47615, 0xF0A200, 0xFAD900, 
	0xC8DE00, 0x83C024, 0x37AA35, 0x00973A, 
	0x008F57, 0x00917C, 0x0091A2, 0x0091C8, 
	0x0080C7, 0x0065AB, 0x004890, 0x202778, 
	0x47166F, 0x6F1A75, 0x971A76, 
};

static cocos2d::ccColor3B RGBToColor3B(int rgb)
{		
	unsigned char r = (rgb & 0xFF0000) >> 16;		
	unsigned char g = (rgb & 0xFF00) >> 8;		
	unsigned char b = (rgb & 0xFF);		
	return cocos2d::ccc3(r, g, b);
}


class StateChange
{
public:
	virtual void onColorChanged(cocos2d::ccColor3B color) = 0;
	virtual void onBrushChanged(int index) = 0;
};


#endif