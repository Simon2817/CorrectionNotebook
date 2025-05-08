#include "service.h"

Error *MathList[MAX_SIZE]; int m_len = 0;
char math[3][10] = {"高数", "线代", "概率"};

Error *ComputerList[MAX_SIZE]; int c_len = 0;
char computer[4][10] = {"数据结构", "计组", "网络", "操作系统"};

Error *PoliticList[MAX_SIZE]; int p_len = 0;
char politic[5][10] = {"马原", "毛中特", "习", "史纲", "思修"};



void Init()
{
	read();

	int j = 0, k = 0, l = 0;
	bool readed = false;
	for (int i = 0; i < ListLen; i++)
	{
		readed = false;
		for (int x = 0; x < 3; x++)
			if ( strcmp(list[i]->classname, math[x]) == 0 )
			{
				MathList[j++] = list[i];
				readed = true;
				break;
			}
		if (readed)
			continue;
		for (x = 0; x < 4; x++)
			if ( strcmp(list[i]->classname, computer[x]) == 0 )
			{
				ComputerList[k++] = list[i];
				readed = true;
				break;
			}
		if (readed)
			continue;
		for (x = 0; x < 5; x++)
			if ( strcmp(list[i]->classname, politic[x]) == 0 )
			{
				PoliticList[l++] = list[i];
				readed = true;
				break;
			}
	}
	m_len = j;
	c_len = k;
	p_len = l;

	PrintList(list, ListLen);
	PrintList(MathList, j);
	PrintList(ComputerList, k);
	PrintList(PoliticList, l);
}