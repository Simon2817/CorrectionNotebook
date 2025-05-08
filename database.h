#ifndef _DATABASE_H_
#define _DATABASE_H_





/*********************************************************/
/*ʹ�õ���ͷ�ļ�*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*********************************************************/
/*����*/

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

extern Error *list[DATA_LEN * 2]; // ��ȡ�����д���ı�
extern int ListLen;
/*********************************************************/
/*���巽��*/

int GetQuestionCount();

void WriteQuestionCount(int count);

void write(int id, char *classname, char *type, char *link);

void read();

void PrintList(Error *L[], int len);


#endif _DATABASE_H_
