#ifndef _SERVICE_H_
#define _SERVICE_H_

#define WIN_WIDTH 1440
#define WIN_HEIGHT 800
#define MAX_SIZE 1000


/*********************************************************/
/*使用到的头文件*/

#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include <windows.h>



/*********************************************************/
/*参数*/
extern Error *MathList[MAX_SIZE];
extern int m_len;
extern char math[3][10];
extern Error *ComputerList[MAX_SIZE]; 
extern int c_len;
extern char computer[4][10];
extern Error *PoliticList[MAX_SIZE]; 
extern int p_len;
extern char politic[5][10];


/*********************************************************/
/*定义方法*/

void Init();

#endif _SERVICE_H_
