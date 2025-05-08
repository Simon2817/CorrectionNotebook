#ifndef _DATABASE_H_
#define _DATABASE_H_





/*********************************************************/
/*使用到的头文件*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*********************************************************/
/*参数*/

#define DATA_LEN 512

typedef struct
{
	int id;
	char * classname;
	char * type;
	int count;
	char * link;
	char * an_link;
} Error;

extern Error *list[DATA_LEN * 2]; // 获取到所有错题的表
extern int ListLen;
/*********************************************************/
/*定义方法*/

int GetQuestionCount();

void WriteQuestionCount(int count);

void write(int id, char *classname, char *type, char *link);

void read();

void PrintList(Error *L[], int len);


#endif _DATABASE_H_
