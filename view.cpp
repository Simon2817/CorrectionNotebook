#include "view.h"


int fragmentID = 0;

///////////////////////////////////////////////////////////////////////////////////////
// 首页面
Page FirstPage;	
Button btn_math, btn_cmp, btn_pol; // 课程按钮

///////////////////////////////////////////////////////////////////////////////////////
// 课程界面
Page ClassMathPage;

// 菜单导航
Page Navigation;
//Button SelAll, Sort, Asc, Desc, Create, Exam; 
Button Exam; // 公有按钮
Button class_math_btn[8];
char str[8][15] = {"全部", "高数", "线代", "概率", "错题数排序", "升序", "降序", "生成错题"};

// 绘制一个帧
void DrawFragment()
{
	cleardevice();

	switch (fragmentID)
	{
		case 0: // 界面1
			{
				DrawPage(&FirstPage);
			}
			break;
		case 1: // 界面2
			DrawPage(&FirstPage);
			break;
		case 2: // 界面3
			DrawPage(&FirstPage);
			break;
	}

	FlushBatchDraw();
	Sleep(10);

}

MOUSEMSG mouse; // 鼠标控制
Button *btnList[40]; // 鼠标按钮缓存
bool btnLive[40] = {false}; // 按钮是否活动
void MouseSearch()
{
	while (1)
	{
		if (MouseHit())
		{
			mouse = GetMouseMsg();		// 获取鼠标信息
			switch(mouse.uMsg)
			{
				case WM_MOUSEMOVE:
					{
						// 鼠标按钮缓存
						for (int i = 0; i < BtnIDCount; i++)
						{
							if (btnLive[i] != true)
								continue;
							if(pressedButton(btnList[i], &mouse)) // 鼠标在关闭按钮上
								btnList[i]->pressed = true;
							else
								btnList[i]->pressed = false;				
						}
					}
					break;

				case WM_LBUTTONDOWN:

					break;

				case WM_LBUTTONUP:
					if(pressedButton(&btn_math, &mouse)) // 关闭按钮被按下
					{
						// 鼠标按钮缓存
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

// 播放循环播放帧
void PlayFragment()
{
	BeginBatchDraw();
	while(1)
	{
		DrawFragment(); // 播放一帧
	}
	EndBatchDraw();	
}

void InitPageFirst(Page *page)
{
	InitPage(page, "ui_img/background.jpg");

	// 设置页类元素
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
	
	// 加入鼠标缓存中
	btnList[btn_math.id] = &btn_math; btnLive[btn_math.id] = true;
	btnList[btn_cmp.id] = &btn_cmp; btnLive[btn_cmp.id] = true;
	btnList[btn_pol.id] = &btn_pol; btnLive[btn_pol.id] = true;
}

void InitClassPage(Page *page)
{
	InitPage(page, "ui_img/background.jpg");

	///////////////
	// 设置页类元素

	// 菜单导航
	InitPage(&Navigation, "ui_img/mask.jpg");
	Navigation.width = (int)WIN_WIDTH*0.75;
	Navigation.height = 150;
	
}

void InitView()
{
	//////////////////////////////////////////////////////////////////////////////
	// 初始化屏幕属性
	initgraph(WIN_WIDTH, WIN_HEIGHT);//初始化窗口

	setbkcolor(RED);//设置背景颜色
	
	cleardevice();// 用背景色清空屏幕


	//////////////////////////////////////////////////////////////////////////////
	// 初始化页面

	// 初始化首页面
	InitPageFirst(&FirstPage);

	// 设置当前要显示的页面id
	fragmentID = FirstPage.id;

	// 初始化课程页面
	InitClassPage(&ClassMathPage);
	
	//////////////////////////////////////////////////////////////////////////////
	// 设置鼠标线程
	HANDLE mouseTh = CreateThread(NULL, NULL,  
		(LPTHREAD_START_ROUTINE)MouseSearch, 
		NULL, NULL, NULL);

}

void ViewMain()
{
	InitView(); // 初始话界面

	InitPageFirst(&FirstPage);
	PlayFragment(); // 播放界面
	
	closegraph();//关闭窗口
}