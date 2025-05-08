#include "view.h"


int fragmentID = 0;

///////////////////////////////////////////////////////////////////////////////////////
// ��ҳ��
Page FirstPage;	
Button btn_math, btn_cmp, btn_pol; // �γ̰�ť

///////////////////////////////////////////////////////////////////////////////////////
// �γ̽���
Page ClassMathPage;

// �˵�����
Page Navigation;
//Button SelAll, Sort, Asc, Desc, Create, Exam; 
Button Exam; // ���а�ť
Button class_math_btn[8];
char str[8][15] = {"ȫ��", "����", "�ߴ�", "����", "����������", "����", "����", "���ɴ���"};

// ����һ��֡
void DrawFragment()
{
	cleardevice();

	switch (fragmentID)
	{
		case 0: // ����1
			{
				DrawPage(&FirstPage);
			}
			break;
		case 1: // ����2
			DrawPage(&FirstPage);
			break;
		case 2: // ����3
			DrawPage(&FirstPage);
			break;
	}

	FlushBatchDraw();
	Sleep(10);

}

MOUSEMSG mouse; // ������
Button *btnList[40]; // ��갴ť����
bool btnLive[40] = {false}; // ��ť�Ƿ�
void MouseSearch()
{
	while (1)
	{
		if (MouseHit())
		{
			mouse = GetMouseMsg();		// ��ȡ�����Ϣ
			switch(mouse.uMsg)
			{
				case WM_MOUSEMOVE:
					{
						// ��갴ť����
						for (int i = 0; i < BtnIDCount; i++)
						{
							if (btnLive[i] != true)
								continue;
							if(pressedButton(btnList[i], &mouse)) // ����ڹرհ�ť��
								btnList[i]->pressed = true;
							else
								btnList[i]->pressed = false;				
						}
					}
					break;

				case WM_LBUTTONDOWN:

					break;

				case WM_LBUTTONUP:
					if(pressedButton(&btn_math, &mouse)) // �رհ�ť������
					{
						// ��갴ť����
						for (int i = 0; i < BtnIDCount; i++)
						{
							btnLive[i] = false;
						}						
						closegraph();
						exit(0);
					}
					break;
			}
			FlushMouseMsgBuffer();
		}
		Sleep(2);
	}
}

// ����ѭ������֡
void PlayFragment()
{
	BeginBatchDraw();
	while(1)
	{
		DrawFragment(); // ����һ֡
	}
	EndBatchDraw();	
}

void InitPageFirst(Page *page)
{
	InitPage(page, "ui_img/background.jpg");

	// ����ҳ��Ԫ��
	int btn_width = 278, btn_height = 392;
	int btn_left_margin = (WIN_WIDTH - 3*btn_width) / 4;
	int btn_top_margin = (WIN_HEIGHT - btn_height) / 2;

	initButton(&btn_math, btn_left_margin, btn_top_margin, 
		"ui_img/math.jpg", "ui_img/math_pressed.jpg", "ui_img/mask.jpg",
		btn_width, btn_height);
	
	initButton(&btn_cmp, btn_left_margin*2 + btn_width, btn_top_margin, 
		"ui_img/computer.jpg", "ui_img/computer_pressed.jpg", "ui_img/mask.jpg",
		btn_width, btn_height);

	initButton(&btn_pol, btn_left_margin*3 + btn_width*2, btn_top_margin, 
		"ui_img/politic.jpg", "ui_img/politic_pressed.jpg", "ui_img/mask.jpg",
		btn_width, btn_height);

	MapAdd(&page->map, "button", &btn_math);
	MapAdd(&page->map, "button", &btn_cmp);
	MapAdd(&page->map, "button", &btn_pol);
	
	// ������껺����
	btnList[btn_math.id] = &btn_math; btnLive[btn_math.id] = true;
	btnList[btn_cmp.id] = &btn_cmp; btnLive[btn_cmp.id] = true;
	btnList[btn_pol.id] = &btn_pol; btnLive[btn_pol.id] = true;
}

void InitClassPage(Page *page)
{
	InitPage(page, "ui_img/background.jpg");

	///////////////
	// ����ҳ��Ԫ��

	// �˵�����
	InitPage(&Navigation, "ui_img/mask.jpg");
	Navigation.width = (int)WIN_WIDTH*0.75;
	Navigation.height = 150;
	
}

void InitView()
{
	//////////////////////////////////////////////////////////////////////////////
	// ��ʼ����Ļ����
	initgraph(WIN_WIDTH, WIN_HEIGHT);//��ʼ������

	setbkcolor(RED);//���ñ�����ɫ
	
	cleardevice();// �ñ���ɫ�����Ļ


	//////////////////////////////////////////////////////////////////////////////
	// ��ʼ��ҳ��

	// ��ʼ����ҳ��
	InitPageFirst(&FirstPage);

	// ���õ�ǰҪ��ʾ��ҳ��id
	fragmentID = FirstPage.id;

	// ��ʼ���γ�ҳ��
	InitClassPage(&ClassMathPage);
	
	//////////////////////////////////////////////////////////////////////////////
	// ��������߳�
	HANDLE mouseTh = CreateThread(NULL, NULL,  
		(LPTHREAD_START_ROUTINE)MouseSearch, 
		NULL, NULL, NULL);

}

void ViewMain()
{
	InitView(); // ��ʼ������

	InitPageFirst(&FirstPage);
	PlayFragment(); // ���Ž���
	
	closegraph();//�رմ���
}