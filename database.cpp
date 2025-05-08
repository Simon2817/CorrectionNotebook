#include "database.h"

Error *list[DATA_LEN * 2]; // 获取到所有错题的表
int ListLen;

int GetQuestionCount()
{
	FILE *fp;//文件指针

	if((fp = fopen("QuestionCount.txt", "r")) == NULL)//文件格式必须文ANSI，才能正确输出汉字
	{
		printf("QuestionCount.txt文件不存在！\n");
		exit(0);
	}
	// 读出count
	char str_r[10];
	int i;
	for(i=0; (str_r[i] = fgetc(fp)) != EOF; i++);
	str_r[i] = '\0';
	fclose(fp);

	int count = 0;
	for (i = 0; str_r[i] != '\0'; i++)
	//	printf("%c\n", str_r[i]);
		if (str_r[i] >= '0' && str_r[i] < '9')
			count = count*10 + str_r[i] - 48;
		else
		{
			if (i != 0)
				count = 0;
		}

	return count;
}

void WriteQuestionCount(int count)
{
	count++;

	// 写入count
	FILE *fp;//文件指针
	if((fp = fopen("QuestionCount.txt", "w")) == NULL)//文件格式必须文ANSI，才能正确输出汉字
	{
		printf("QuestionCount.txt文件不存在！\n");
		exit(0);
	}
	char str_w[10];
	sprintf(str_w, "%d", count);
	for (int i = 0; str_w[i] != '\0'; i++)
		fputc(str_w[i], fp);

	fclose(fp);
}

void write(int id, char *classname, char *type, char *link)
{

	Error error;
	error.id = id;
	error.classname = classname;
	error.type = type;
	error.count = 0;
	error.link = link;
	
	char error_str[DATA_LEN];
	sprintf(error_str, "[%d %s %d %s %s]", id, error.classname, error.type, error.count, error.link);

	FILE *fp;//文件指针

	if((fp = fopen("aaa.txt", "a")) == NULL)//文件格式必须文ANSI，才能正确输出汉字
	{
		printf("文件不存在！\n");
		exit(0);
	}

	int i = 0;
	for (i = 0; error_str[i] != '\0'; i++)
	{
		fputc(error_str[i], fp);
	}
	fputc('\n', fp);
	fclose(fp);
	WriteQuestionCount(GetQuestionCount());
}

void read()
{
	FILE *fp;//要读的文件
	char error_str[DATA_LEN * 10];//存放读取到的字符
	int i;//循环变量

	if((fp = fopen("aaa.txt" ,"r")) == NULL)//打开文件
	{
		printf("文件不存在！\n");
		exit(0);
	}
	
	ListLen = 0;

	for(i=0; (error_str[i] = fgetc(fp)) != EOF; i++);//这种读取方式需要文件字符编码为ANSI，才不会乱码
	error_str[i] = '\0';

//	for (i = 0; error_str[i] != '\0'; i++)
//		printf("%c",error_str[i]);
//	getchar();
//	printf("[%d字节]\n", i);
	
	int index = 0; // 记录获取到的个数
	i = 0;
	while (error_str[i] != '\0')
	{
		char ch = error_str[i];
		Error *error = (Error*)malloc(sizeof(Error)); 
		if (error_str[i] == '[')
		{
			index++;
			list[index - 1] = error;
		}
		
		while (error_str[i] == ' ' || error_str[i] == '[')
		{
			ch = error_str[i];
			i++;
			int j, k;
		//	printf("{");
			for (j = 0; j < 6 && error_str[i] != ']'; j++, i++) // 对6个字段赋值
			{
				ch = error_str[i];
				if (j == 0) // 读出第一个字段id
				{		
					error->id = index;
					i--;
				//	printf("id: %d ", error->id);
				}
				else if (j == 1) // 读取第二个字段classname
				{
					error->classname = (char*)malloc(sizeof(char) * 10);
					for (k = 0; error_str[i] != ' '; k++, i++)
					{
						error->classname[k] = error_str[i];
					}
					error->classname[k] = '\0';
				//	printf("classname: %s ", error->classname);
				}
				else if (j == 2) // 读取第三个字段type
				{
					error->type = (char*)malloc(sizeof(char) * 20);
					for (k = 0; error_str[i] != ' '; k++, i++)
					{
						error->type[k] = error_str[i];
					}
					error->type[k] = '\0';
				//	printf("type: %s ", error->type);
				}
				if (j == 3) // 读出第四个字段count
				{		
					error->count = 0;
					while (error_str[i] != ' ')
					{
						error->count = error->count*10 + error_str[i] - 48;
						i++;
					}
				//	printf("count: %d ", error->count);
				}
				else if (j == 4) // 读取第五个字段type
				{
					error->link = (char*)malloc(sizeof(char) * 50);
					error->link[0] = 'i';error->link[1] = 'm';error->link[2] = 'g';error->link[3] = '\\';
					for (k = 4; error_str[i] != ' ' && error_str[i] != ']'; k++, i++)
					{
						error->link[k] = error_str[i];
					}
					error->link[k] = '.';error->link[k+1] = 'j';error->link[k+2] = 'p';error->link[k+3] = 'g';
					error->link[k+4] = '\0';
				//	printf("link: %s", error->link);
				//	printf("}\n");
				}

				else if (j == 5) // 读取第六个字段type
				{
					error->an_link = (char*)malloc(sizeof(char) * 50);
					error->an_link[0] = 'i';error->an_link[1] = 'm';error->an_link[2] = 'g';error->an_link[3] = '\\';
					for (k = 4; error_str[i] != ' ' && error_str[i] != ']'; k++, i++)
					{
						error->an_link[k] = error_str[i];
					}
					error->an_link[k] = '.';error->an_link[k+1] = 'j';error->an_link[k+2] = 'p';error->an_link[k+3] = 'g';
					error->an_link[k+4] = '\0';
					break;
				}
			}
		}

		if (error_str[i] == ']')
			i ++;
		else if(error_str[i] == '\n')
			i++;
	}
	ListLen = index;
    fclose(fp);//关闭文件
}

void PrintList(Error *L[], int len)
{
	for (int i = 0; i < len; i ++)
	{
		printf("id:%d ", L[i]->id);
		printf("classname:%s ", L[i]->classname);
		printf("type:%s ", L[i]->type);
		printf("count:%d ", L[i]->count);
		printf("link:%s ", L[i]->link);
		printf("an_link:%s\n", L[i]->an_link);
	}
	printf("==========================\n");
}