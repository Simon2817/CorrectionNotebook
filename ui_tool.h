#ifndef _UI_TOOL_H_
#define _UI_TOOL_H_

/*********************************************************/
/*ʹ�õ���ͷ�ļ�*/

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
//�������
void outText(int textColor, int size, char *style, int x, int y, char* str);



////////////////////////////////////////////////////////////////////////////////////////////////////////
//BUTTON

//����
typedef struct
{
	int id;
	int x;
	int y;
	int width;
	int height;
	char name[20];
	IMAGE normalImage; // ��� ��ѹ��   ��ť��
	IMAGE pressImage;  // ��� ѹ��     ��ť��
	IMAGE maskImage;   // ����ͼ
	bool pressed;      // ��� �Ƿ�ѹ�� ��ť��
}Button;
extern bool pressL;

extern int BtnIDCount;

void initButton(Button *button, int x, int y,
				char* normalFile, char* pressedFile, char *maskFile,
				int width, int height);

bool pressedButton(Button *button, MOUSEMSG *m);

void drawButton(Button *button);




////////////////////////////////////////////////////////////////////////////////////////////////////////
//Page��ҳ��

//����
typedef struct
{
	int id;
	int x, y;
	int width, height;
	IMAGE bg; // ����ͼƬ
	Map map; // Ԫ���б�
}Page;

extern int PageIDCount;

void InitPage(Page *page, char *bgStr);

void ElemOfPageAdd(Page *page, char *key, void *value);

void DrawPage(Page *page);

#endif _UI_TOOL_H_