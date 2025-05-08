#ifndef _UI_TOOL_H_
#define _UI_TOOL_H_

/*********************************************************/
/*使用到的头文件*/

#include <stdio.h>
#include"graphics.h"

/*********************************************************/
/*Map*/
typedef struct
{
	char *key;
	void *value;
} MapNode, *MNode;

typedef struct
{
	MNode node[40];
	int len;
} Map;

void InitMap(Map *map);

void MapAdd(Map *map, char *key, void *value);


////////////////////////////////////////////////////////////////////////////////////////////////////////
//文字输出
void outText(int textColor, int size, char *style, int x, int y, char* str);



////////////////////////////////////////////////////////////////////////////////////////////////////////
//BUTTON

//参数
typedef struct
{
	int id;
	int x;
	int y;
	int width;
	int height;
	char name[20];
	IMAGE normalImage; // 鼠标 不压在   按钮上
	IMAGE pressImage;  // 鼠标 压在     按钮上
	IMAGE maskImage;   // 掩码图
	bool pressed;      // 鼠标 是否压在 按钮上
}Button;
extern bool pressL;

extern int BtnIDCount;

void initButton(Button *button, int x, int y,
				char* normalFile, char* pressedFile, char *maskFile,
				int width, int height);

bool pressedButton(Button *button, MOUSEMSG *m);

void drawButton(Button *button);




////////////////////////////////////////////////////////////////////////////////////////////////////////
//Page，页面

//参数
typedef struct
{
	int id;
	int x, y;
	int width, height;
	IMAGE bg; // 背景图片
	Map map; // 元素列表
}Page;

extern int PageIDCount;

void InitPage(Page *page, char *bgStr);

void ElemOfPageAdd(Page *page, char *key, void *value);

void DrawPage(Page *page);

#endif _UI_TOOL_H_