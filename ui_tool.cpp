#include "ui_tool.h"

/*********************************************************/
/*Map*/
void InitMap(Map *map)
{
	map->len = 0;
}

void MapAdd(Map *map, char *key, void *value)
{
	MNode node = (MNode)malloc(sizeof(MapNode));
	node->key = key; node->value = value;
	map->node[map->len] = node;
	map->len++;
	
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
//�������
void outText(int textColor, int size, char *style, int x, int y, char* str)
{
	setbkmode(TRANSPARENT);			//ȥ�����ֱ���
	settextcolor(textColor);		// ����������ɫ
	settextstyle(size, 0, style);	// ���õ�ǰ���壬���磺Ϊ�� 35 ���صġ����塱	
	outtextxy(x, y, str);					
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//BUTTON

int BtnIDCount = 0;

void initButton(Button *button, int x, int y,
				char* normalFile, char* pressedFile, char *maskFile,
				int width, int height)
{
	loadimage(&button->normalImage, normalFile, width, height);
	loadimage(&button->pressImage, pressedFile, width, height);
	loadimage(&button->maskImage, maskFile, width, height);
	
	button->id = BtnIDCount++;
	button->x = x;
	button->y = y;
	button->width = width;
	button->height = height;
	button->pressed = false;
}

bool pressedButton(Button *button, MOUSEMSG *m)
{
	if(
		m->x > button->x &&
		m->x < (button->x + button->width) &&
		m->y > button->y &&
		m->y < (button->y + button->height)
		)
	{
		return true;
	}
	return false;
}

void drawButton(Button *button)
{	
	if(button->pressed == true)
	{
		putimage(button->x, button->y, &button->maskImage, NOTSRCERASE);
		putimage(button->x, button->y, &button->pressImage, SRCINVERT);
	}
	else if(button->pressed == false)
	{
		putimage(button->x, button->y, &button->maskImage, NOTSRCERASE);
		putimage(button->x, button->y, &button->normalImage, SRCINVERT);
	}
}


/*
int main()
{
	initgraph(WINDWOSWIDTH, WINDOWHEIGHT); 

	setScreen(4, 30);

	// д�뱳��ͼ
	IMAGE imgBg; // ����ͼƬ
	loadimage(&imgBg, "res/bg.jpg");
	putimage(0, 0, &imgBg);	
	
	Button buttonClose;
	initButton(&buttonClose, 300, 300, 
		"res/normalButton.jpg", "res/pressedButton.jpg", "res/maskButton.jpg",	
		200, 50);
	drawButton(&buttonClose);
	outText(BLACK, 25, "����", buttonClose.x + 15, buttonClose.y + 15, "׼  ��");
	while(1)
	{
		MOUSEMSG m = GetMouseMsg(); // ��ȡ�����Ϣ
		FlushMouseMsgBuffer(); // ��������Ϣ�Ļ���
		
		switch(m.uMsg)
		{
			case WM_MOUSEMOVE:
				{
					if(pressedButton(&buttonClose, &m)) // ����ڹرհ�ť��
					{
						buttonClose.pressed = true;
						drawButton(&buttonClose);
						
					}
					else
					{
						if(buttonClose.pressed)
						{
							buttonClose.pressed = false;
							drawButton(&buttonClose);					
						}
						// ... if
					}
				}
				break;

			case WM_LBUTTONDOWN:
				{

				}
				break;

			case WM_LBUTTONUP:
				{
					if(pressedButton(&buttonClose, &m)) // �رհ�ť������
					{
						closegraph();
						exit(0);
					}
				}
				break;
		}
	}
	getchar();

	return 0;
}
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////
//Page��ҳ��

int PageIDCount = 0;

void InitPage(Page *page, char *bgStr)
{
	page->id = PageIDCount++;
	loadimage(&page->bg, bgStr, 0, 0);
	InitMap(&page->map);
}

void ElemOfPageAdd(Page *page, int id, char *key, void *value)
{
	MapAdd(&page->map, key, value);
}

//IMAGE img;
void DrawPage(Page *page)
{
	putimage(page->x, page->y, &page->bg); // ����ͼƬ
	for (int i = 0; i < page->map.len; i++)
	{
		if (strcmp(page->map.node[i]->key, "button") == 0) // �����ť
		{
			Button *btn = (Button*)page->map.node[i]->value;
			drawButton(btn);
		}
		else if(strcmp(page->map.node[i]->key, "page") == 0) // ���ҳ��
		{
			Page *page = (Page*)page->map.node[i]->value;
			DrawPage(page);
		}
	}
}