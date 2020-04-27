#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<time.h>
#pragma warning(disable:4996)

void Main_show();											//UI主界面窗口
void Main_start();												//程序执行函数
void Information_increment();						//联系人信息增加模块
void Information_delete();								//联系人信息删除模块
void Information_modify();								//联系人信息修改模块
void Information_query();								//联系人信息查询模块
void Information_count();								//联系人信息统计模块
void Show_store_information();						//查看联系人信息存储分布模块
void Information_store_clean();						//碎片整理模块
void Select_exit();											//每个模块结束后的UI界面窗口
void Show_information();								//显示联系人信息
void Bin_read_head();										//从起始位置读取文件
void Bin_read_end();										//从结束位置读取文件
void Bin_write_head(int Lens);							//从起始位置写入文件，nlens表示写入的长度
void Bin_write_end(int Lens);							//从结束位置写入文件，nlens表示写入的长度
void Clear_g_szInf();											//对数组初始化函数；
char g_szInf[10000] = { 0 };								//用来保存联系人所有信息的数组

/*
约定，对每个存储的数据一个下标用来记录存储状态和类型
 -1代表有效数据存储的姓名,
 -3代表无效数据存储的姓名
 -2代表有效数据存储的号码
 -4代表无效数据存储的号码
*/

int main()
{
	Main_start();								//开始执行程序程序
	return 0;
}

void Main_start()							//程序开始执行
{
	int nNum = 0;
	system("cls");
	Main_show();
	scanf_s("%d", &nNum);			//接受用户输入的数数字选择功能
	if (nNum == 1)
	{
		Information_increment();
	}
	else if (nNum == 2)
	{
		Information_delete();
	}
	else if (nNum == 3)
	{
		Information_modify();
	}
	else if (nNum == 4)
	{
		Information_query();
	}
	else if (nNum == 5)
	{
		Information_count();
	}
	else if (nNum == 6)
	{
		Show_store_information();
	}
	else if (nNum == 7)
	{
		Information_store_clean();
	}
	else if (nNum == 8)
	{
		Show_information();
		Select_exit();
	}
	else if (nNum == 9)
	{
		exit(0);
	}
	else
	{
		printf("输出错误，请重新输入\n");							//输入错误返回UI主界面窗口
		Sleep(1000);
		Main_start();											
	}
}

void Main_show()															//UI主界面窗口
{
	printf("--------------------------------------------------\n");
	printf("\t    欢迎进入联系人信息管理系统\n");
	printf("--------------------------------------------------\n");
	printf("请输入您要执行的操作(按数字执行)：\n");
	printf("\t1.增加新的联系人\n");
	printf("\t2.删除联系人\n");
	printf("\t3.修改联系人\n");
	printf("\t4.查询联系人\n");
	printf("\t5.统计联系人\n");
	printf("\t6.查看当前存储信息\n");
	printf("\t7.整理碎片并查看当前整理好的碎片状态\n");
	printf("\t8.查看当前存储的所有联系人信息\n");
	printf("\t9.退出程序\n");
	printf("--------------------------------------------------\n");
}

void Information_increment()													//联系人信息增加模块(先将增加的数据报存至数组，每增加一次写入一次)
{
	int i = 0;																	
	int nLen = 0;																		//用来记录增加信息的长度
	char szAdd_name[300] = { 0 };											//用来接收用户输入的姓名
	long long int Add_number = 0 ;											//用来接收用户输入的电话号码
	system("cls");
	printf("--------------------------------------------------\n");
	printf("\t联系人信息增加模式:\n");
	printf("--------------------------------------------------\n");
	printf("请输入你想要添加的联系人信息：\n");
	printf("请输入存储的联系人名称:\n");
	scanf_s("%s", szAdd_name, sizeof(szAdd_name));
	for (i = 0; i < 300; i++)																//插入姓名信息
	{
		if (g_szInf[i] == '\0' && g_szInf[i + 1] == '\0' && i == 0)		//当数组为空时
		{
			g_szInf[i] = -1;																		//每个数据首地址插入表示姓名的下标-3
			strcpy(&g_szInf[i + 1], szAdd_name);									//将输入的信息拷贝至下标后的位置			
			nLen = strlen(szAdd_name) + 1;											//计算长度输入姓名信息的长度
			break;
		}
	}
	printf("输入要存储的手机号码：(必须为小于22位的数字)\n");
	scanf_s("%lld", &Add_number, sizeof(Add_number));				//检测非法输入
	while (1)
	{
		if (Add_number >= 9223372036854775807)								//大于long long int 类型长度报错，重新输入
		{
			printf("输入无效数字！！请重新输入不大于22位的数字:\n");
			Add_number = 0;
			scanf_s("%lld", &Add_number, sizeof(Add_number));
		}
		if (Add_number < 9223372036854775807)
		{
			break;
		}
	}
	printf("插入信息成功！");
	for (i = 0; i < 300; i++)															//插入手机号信息
	{
		if (g_szInf[i] == '\0' && g_szInf[i + 1] == '\0')
		{
			char szAdd_number[20] = { 0 };
			sprintf(szAdd_number, "%lld", Add_number);
			g_szInf[i + 1] = -2;														//每个数据首地址插入表示姓名的下标-3
			strcpy(&g_szInf[i + 2], szAdd_number); 			    		//将输入的信息拷贝至下标后的位置	
			nLen += strlen(szAdd_number) + 3;
			break;
		}
	}
	Bin_write_end(nLen);																//每次添加都从二进制文件尾部写入文件，
	printf("添加后的联系人信息为:\n");											//防止断电等突发状况损毁数据			
	printf("--------------------------------------------------\n");
	Show_information();
	Clear_g_szInf();																		//对数组初始化
	Select_exit();																		//选择退出
}	

void Information_delete()														//联系人信息删除模块
{
	system("cls");
	int i = 0;
	int nLen = 0;																			//用来记录修改后的数据长度
	int nIsTrue = 0;																		//用来标记是查询到修改的数据
	int nNum = 0;																			//记录用户输入信息
	int nCount = 0;																		//用来统计联系人标号
	//char szDel[100] = { 0 };															//这里的数组用来接收用户输入的字符
	printf("--------------------------------------------------\n");
	printf("\t    欢迎进入联系人删除模式:\n");
	printf("--------------------------------------------------\n");
	printf("请选择删除模式:\n");
	printf("1.输入编号删除对应的联系人\n");
	printf("2.格式化清楚所有联系人信息\n");
	printf("3.返回主界面\n");
	scanf_s("%d", &nNum);
	
	if (nNum == 1)
	{
		Show_information();												 //先查看下当前存储所有数据
		Bin_read_end();
		printf("请输入您要删除的联系人编号：\n");
		scanf_s("%d", &nNum);
		for (i = 0; i < 10000; i++)										//遍历数组，如果用户删除的字符串标号与存在的下标一致，则算作删除
		{
			if ((g_szInf[i] == -1 && i == 0) || (g_szInf[i] == -1 && g_szInf[i - 1] == '\0'))					
			{																							//遍历数组，打印出首位和所有'\0'后标头为-3的数据，即保存姓名的数据
				nCount++;								
				if (nNum == nCount)														//输入数据与字符串编号比较
				{
					g_szInf[i] = -3;																	//删除姓名数据及把有效数据的下标置为-4
				}
			}
			else if (g_szInf[i] == -2 && g_szInf[i - 1] == '\0')					//遍历数组，打印出首位和所有'\0'后标头为-2的数据，即保存手机号的数据
			{
				if (nNum == nCount)
				{
					g_szInf[i] = -4;																	//删除号码数据及把有效数据的标头置为-4
					nIsTrue = 1;
					printf("恭喜，删除成功！\n");
				}
			}
			if (g_szInf[i] == '\0' && g_szInf[i + 1] == '\0' && g_szInf[i + 2] == '\0' && g_szInf[i + 3] == '\0')						
			{																									//找到连续为0的地址，即循环退出的出口
				nLen = i+1;
				break;
			}
		}
		if (nIsTrue == 0)									//输入不存在的编号时
		{
			printf("没有这一项联系人信息");
		}

		Bin_write_head(nLen);							//将执行删除操作后的数据传回二进制数组		
		Clear_g_szInf();
		printf("删除后的联系人: \n");
		Show_information();
		Select_exit();
	}

	if (nNum == 2)											//格式化数据
	{
		Bin_read_head();										//从起始位置读取文件及清空所有数据
		printf("当前所有联系人已经全部格式化!!\n");
		Select_exit();
	}

	if (nNum == 3) {											//返回主菜单
		Main_start();
	}
	printf("输入错误！\n");
	Select_exit();
}

void Information_modify()								//联系人信息修改模块
{
	int i = 0,j=0;
	int nLen = 0;																			//用来记录修改后的数据长度
	int nIsTrue = 0;																		//用来标记是查询到修改的数据
	int nNum = 0;																			//记录用户输入信息
	int nCount = 0;																		//用来统计联系人标号
	char szName[300] = { 0 };
	char szNum[300] = { 0 };
	char szInf[300] = { 0 };
	int nszAddLen = 0;																	//记录用户输入的数据块的长度
	int nszLen = 0;																			//用来记录原的数据块长度		
	system("cls");
	printf("--------------------------------------------------\n");
	printf("\t    欢迎进入字符串修改模式:\n");
	printf("--------------------------------------------------\n");
	printf("当前存储的联系信息如下所示:\n");
	Show_information();
	Bin_read_end();																	//从文件中将二进制信息读入数组
	printf("请输入您要修改的联系人所在编号：");
	scanf_s("%d", &nNum);
	for (i = 0; i < 1000; i++)														//首先计算一下原数据块长度
	{
		if ((g_szInf[i] == -1 && i == 0) || (g_szInf[i] == -1 && g_szInf[i - 1] == '\0'))			
		{																							//读到一条有效姓名数据时开始进入循环
			nCount++;
			if (nCount == nNum)													
			{
				while(1)
				{
					nszLen++;										
					i++;
					if (g_szInf[i] == '\0' && (g_szInf[i + 1] == -1 || g_szInf[i + 1] == -3|| g_szInf[i + 1]=='\0'))
					{																			//找到连续为0的地址，即循环退出的出口
						break;	
					}
				}
			}
		}
	}
	nCount=0;																		//初始化计数器
	printf("您要修改姓名还是号码？(输入1，2来选择)\n");
	printf("1.修改姓名");
	printf("2.修改电话号码");
	scanf_s("%d", &i);
	if (i == 1)
	{
		printf("请输入要修改的姓名:\n");
		scanf_s("%s", szName, sizeof(szName));
		for (i = 0; i < 10000; i++)
		{
			if (g_szInf[i] == -1)
			{
				nCount++;
				if (nCount == nNum)
				{
					g_szInf[i] = -6;				                             //如果匹配到要修改的字符串把原下标置为-6,视为可修改标记
					strcpy(szInf, szName);  
					nszAddLen = strlen(szName)+1 ;
				}
			}
			if (g_szInf[i] == -2)
			{
				if (nCount == nNum)
				{
					g_szInf[i] = -4;											 //下标置为无效号码-4
					szNum[j] = -2;
					for (j=0; j<=20; j++,i++)
					{
						szNum[j+1] = g_szInf[i + 1];
						if (g_szInf[i] == '\0')
						{
							break;
						}
					}
					strcpy(szInf + nszAddLen, szNum);			//将修改好的全部信息放在szInf数组内。
					nszAddLen += strlen(szNum)+1;
				}
			}
		}
		if (nszLen<nszAddLen)									//当原数据长度小于用户输入的长度，存不下，重新开辟空间存储
		{
			for (j= 0; j < 1000;j++)
			{
				if (g_szInf[j] == -6)											//未利用标记，清理掉待修改标记
				{
					g_szInf[j] = -3;												//标记视为无效数据
				}
				if (g_szInf[j] == '\0' && g_szInf[j + 1] == '\0' && g_szInf[j + 2] == '\0' && g_szInf[j + 3] == '\0')
				{																		//循环结束出口
					nLen = j;
					g_szInf[j + 1] = -1;																	//存储的首位数据插入下标-1
					memcpy(&g_szInf[j + 2], szInf, nszAddLen);					    	//将修改后的整条数据拷贝至存储信息的数组
					//strcpy(&g_szInf[j + 2], szInf);
					nLen += nszAddLen + 2;
					break;
				}
			}	
		}

		if (nszLen >= nszAddLen)								//当原数据长度大于用户输入的长度，可以存下，在原空间存储
		{
			for (j = 0; j < 1000; j++)
			{
				if (g_szInf[j] == -6 && j == 0)					//找到待修改标记-6，在此处进行修改数据
				{
					g_szInf[j] = -1;																		//把首数据置为-1
					memcpy(&g_szInf[j + 1], szInf, nszAddLen);						//将修改后的整条数据拷贝至存储信息的数组
				}
				if (g_szInf[j] == '\0' && g_szInf[j + 1] == -6)									
				{
					nLen = j;
					g_szInf[j + 1] = -1;
					memcpy(&g_szInf[j + 2], szInf, nszAddLen);						
				}
				if (g_szInf[j] == '\0' && g_szInf[j + 1] == '\0' && g_szInf[j + 2] == '\0' && g_szInf[j + 3] == '\0')
				{																								//找到连续为0的地址，即循环退出的出口
					nLen = j+1;
					break;
				}
			}
		}
	}
	if (i == 2)
	{
		printf("请输入要修改的号码：\n");
		szNum[0] = -2;													//存储的数组中号码首数据置插入下标-2
		scanf_s("%s", szNum+1, sizeof(szNum));
		for (i = 0; i < 10000; i++)
		{
			if (g_szInf[i] == -1)												//遍历所有有效姓名
			{
				nCount++;
				if (nCount == nNum)										//检索到输入编号对应的有效姓名时
				{
					g_szInf[i] = -5;												//如果匹配到要修改的字符串把原标头置为-5,视为删除或可修改
					szInf[j] = -1;													//将下标-1赋予新数组，表示有效姓名数据
					nszAddLen++;
					for (j = 0; j <= 20; j++)
					{
						nszAddLen++;
						szInf[j + 1] = g_szInf[i + 1];						//将这里有存储的姓名拷贝至新的数组szInf
						i++;
						if (g_szInf[i] == '\0' && g_szInf[i + 1] == -2)
						{
							break;
						}
					}
					//	strcpy(szInf, szName);
					//	nszAddLen = strlen(szName) + 1;
				}
			}
			if (g_szInf[i] == -2)										//检索到有效号码
			{
				if (nCount == nNum)
				{
					g_szInf[i] = -4;										//检索到，待修改的号码数据，先置为无效号码-4
					strcpy(szInf + nszAddLen, szNum);		//将修改好的信息放在szInf数组内。
					nszAddLen += strlen(szNum);
					break;
				}
			}
		}

		if (nszLen < nszAddLen)									//当原数据长度小于用户输入的长度，存不下，重新开辟空间存储
		{
			for (j = 0; j < 1000; j++)
			{	
				if (g_szInf[j] == -5)									//清理掉标记
				{
					g_szInf[j] = -3;										//标记视为无效数据
				}
				if (g_szInf[j] == '\0' && g_szInf[j + 1] == '\0' && g_szInf[j + 2] == '\0' && g_szInf[j + 3] == '\0')
				{
					nLen = j;
	//				g_szInf[j + 1] = -1;												//把原下标置为有效姓名数据-1
					memcpy(&g_szInf[j + 1], szInf, nszAddLen);		//将输入数据拷贝至存储信息的数组
					//strcpy(&g_szInf[j + 2], szInf);
					nLen += nszAddLen + 2;
					break;
				}
			}
		}
		if (nszLen >= nszAddLen)								//当原数据长度大于用户输入的长度，可以存下，在原空间存储
		{
			for (j = 0; j < 1000; j++)
			{
				if (g_szInf[j] == -5 && j == 0)					//遍历找到-5标号
				{
					g_szInf[j] = -1;																		
					memcpy(&g_szInf[j], szInf, nszAddLen+1);
				}
				if (g_szInf[j] == '\0' && g_szInf[j + 1] == -5)
				{
					nLen = j;
					g_szInf[j + 1] = -1;
					memcpy(&g_szInf[j + 1], szInf, nszAddLen+1);
				}
				if (g_szInf[j] == '\0' && g_szInf[j + 1] == '\0' && g_szInf[j + 2] == '\0' && g_szInf[j + 3] == '\0')
				{																//找到连续为0的地址，即循环退出的出口
					nLen = j + 1;
					break;
				}
			}
		}
	}
	Bin_write_head(nLen);											//将执行删除操作后的数据传回二进制数组		
	Clear_g_szInf();														//执行数组初始化操作
	printf("修改后的电话簿信息为：\n");
	Show_information();
	Select_exit();
}


void Information_query()													//联系人信息查询模块
{
	int nNum=0;
	int nTemp = 0;
	int nCount= 0;
	int i = 0,j=0;
	char szName[100] = { 0 };
	char szNum[100] = { 0 };
	system("cls");
	printf("--------------------------------------------------\n");
	printf("\t    欢迎进入信息查询模式:\n");
	printf("--------------------------------------------------\n");
	printf("当前所有信息为:\n");
	Show_information();
	Bin_read_end();																	//从文件中将二进制信息读入数组
	printf("请选择查询模式:\n");
	printf("1.根据输姓名查询手机号\n");
	printf("2.跟据输入手机号查询姓名\n");
	printf("3.模糊输入姓名查手机号\n");
	printf("4.模糊输入手机号查姓名\n");
	scanf_s("%d", &nNum);
	if (nNum == 1)
	{
		printf("请输入您要查询的姓名:\n\n");
		nTemp = 0;
		scanf_s("%s", &szName,sizeof(szName));
		for (i = 0; i < 10000; i++)
		{
			if (g_szInf[i] == -1)														
			{
				nCount++;
				if ((strcmp(&g_szInf[i + 1], szName)) == 0)								//匹配字符串是否一样
				{
					nTemp = 1;
					printf("查询到的联系人信息: ");
					printf("%d. 姓名:%s  ",nCount, &g_szInf[i + 1]);						//打印姓名
					for (; i < 1000; i++)
					{
						if (g_szInf[i] == -2)
						{
							printf("手机号:%s\r\n", &g_szInf[i + 1]);							//打印手机号
							break;
						}
					}
				}
			}
		}
	}
	if (nNum == 2)
	{
		printf("请输入您要查询的号码:\n\n");
		nTemp = 0;
		scanf_s("%s", &szNum, sizeof(szNum));
		for (i = 0; i < 10000; i++)													//在大叔组里寻找匹配的字符串
		{
			if (g_szInf[i] == -2)														
			{
				nCount++;
				if ((strcmp(&g_szInf[i + 1], szNum)) == 0)					//匹配输入字符串是否与相同
				{
					nTemp = 1;
					printf("查找到该联系人信息:");
					printf("%d. ", nCount);
					printf("号码 ");
					printf("%s  ",&g_szInf[i + 1]);									
					for (j=i; j > 0; j--)														//遍历到姓名时，需打印整条数据
					{
						if (g_szInf[j] == -1)
						{
							printf(" 对应联系人是 : %s\r\n", &g_szInf[j + 1]);									
							break;
						}
					}
				}
			}
		}
	}
	if (nNum == 3)
	{
		nTemp=0;
		printf("请输入您要查询的姓名信息:\n\n");
		scanf_s("%s", &szName, sizeof(szName));									 //接收用户要查找的模糊字段
		for (i = 0; i < 10000; i++)
		{
			if (g_szInf[i] == -1)																	//比较有效字符串的内容是否有检索的内容
			{
				nCount++;
				if (strstr(&g_szInf[i + 1], szName) != NULL)						//调用strstr函数检索查找字符在每一个有效数据是否出现
				{
					nTemp = 1;
					printf("模糊匹配到的姓名:%d:%s  ", nCount, &g_szInf[i + 1]);
					for (; i < 1000; i++)
					{
						if (g_szInf[i] == -2)
						{
							printf("手机号:%s\r\n", &g_szInf[i + 1]);							 
							break;
						}
					}
				}
			}
		}
	}
	if (nNum == 4)
	{
		nTemp = 0;
		printf("请输入您要查询的手机信息:\n\n");
		scanf("%s", &szNum);																  //接收用户要查找的模糊字段
		for (i = 0; i < 10000; i++)
		{
			if (g_szInf[i] == -2)																//比较有效字符串的内容是否有检索的内容
			{
				nCount++;
				if (strstr(&g_szInf[i + 1], szNum) != NULL)						//调用strstr函数检索查找字符在每一个有效数据是否出现
				{
					printf("模糊匹配到的手机号:%d.%s ", nCount, &g_szInf[i + 1]);
					for (j=i; i > 0; j--)
					{
						if (g_szInf[j] == -1)
						{
							nTemp = 1;
							printf("姓名:%s\r\n", &g_szInf[j + 1]);									//打印手机号
							break;
						}
					}
				}
			}
		}
	}
	if (nTemp == 0)
	{
		printf("\n对不起，没有查询到您输入的信息\n");
	}
	Clear_g_szInf();																			//执行数组初始化操作
	Select_exit();
}

void Information_count()															//联系人信息统计模块
{
	int i = 0;
	int j = 0;
	float nCount = 0;																		//用来计算联系人出现总次数
	float nIndex = 0;																		//用来计算联系人重复出现次数
	system("cls");
	printf("--------------------------------------------------\n");
	printf("\t    当前为联系人信息统计模式:\n");
	printf("--------------------------------------------------\n");
	printf("当前存储所有联系人信息为:\n");
	Show_information();
	Bin_read_end();																			//从文件中将二进制信息读入数组
	for (i = 0; i < sizeof(g_szInf); i++)												//首先计算联系人出现总次数
		if ((g_szInf[i] == -1 && i == 0) || (g_szInf[i] == -1 && g_szInf[i - 1] == '\0'))				
		{
			nCount++;																			//记录存储了有多少个联系人
		}
	printf("当前所有联系人总个数是:%.0f\n",nCount);
	printf("--------------------------------------------------\n");
	printf("当前每个联系人出现次数及比例为:\n");
	printf("--------------------------------------------------\n");
	for (i = 0; i < 1000; i++)
	{
		nIndex = 1;
		if ((g_szInf[i] == -1 && i == 0) || (g_szInf[i] == -1 && g_szInf[i - 1] == '\0'))					//遍历数组，打印出首位和所有'\0'后标头为-3的数据，即保存姓名的数据
		{
			for (j = i+strlen(&g_szInf[i+1]); j < 1000; j++)							//遍历寻找是否存在多次出现的联系人
			{
				if ((strcmp(&g_szInf[i + 1], &g_szInf[j])) == 0)						//匹配之后出现的姓名是否与第一次出现的一样
				{
					g_szInf[j-1] = -3;																	//若匹配到出现超过两次的姓名就修改第一次出现后的数据下标，使其只打印一次
					nIndex++;
				}
			}
			printf("姓名: %s ", &g_szInf[i + 1]);
			printf("出现次数：%.0f ", nIndex);
			float ratio = ((nIndex / nCount) * 100);										//数据转换成float型输出百分比
			printf("出现比例 :%7.2f%%\n", ratio);
		}
	}
	printf("--------------------------------------------------\n");

	Clear_g_szInf();												//执行数组初始化操作
	Select_exit();
}
void Show_store_information()						//查看联系人信息存储分布模块
{
	int i = 0;
	int j = 0;
	system("cls");
	printf("--------------------------------------------------\n");
	printf("\t    当前为资源存储信息查看模式:\n");
	printf("--------------------------------------------------\n");
	printf("当前存储的联系人信息为:\n");
	Show_information();
	Bin_read_end();																			//从文件中将二进制信息读入数组
	printf("当前字符串占据内存空间为(U表示已使用占据的区域一字节 F表示无效数据):\n");
	for (i = 0; i < 1000; i++)
	{
		if (g_szInf[i] == -1 )																	//判断第一个标记是否为有效数据
		{
			printf("U");
		}
		if (g_szInf[i] == -1 || g_szInf[i] == -2)										//找到占用的数据
		{
			for (j = i+1 ; j <= strlen(&g_szInf[i + 1])+i; j++)
			{
				printf("U");																		//占用的数据用U显示
				i++;
			}
		}
		if (g_szInf[j] == '\0' && (g_szInf[j + 1] == -2 || g_szInf[j + 1] == -1))
		{
			printf("U");																			//将字符串阶段符置为占用数据
		}
		else
		{
			printf("F");
		}
		/*
		if (g_szInf[i] == -3 || g_szInf[i] == -4)
		{
			for (j = i + 1; j <= (strlen(&g_szInf[i + 1]) + i); j++)
			{
				printf("F");
			}
		}
		*/
	}
	printf("\r\n");
	Clear_g_szInf();														//执行数组初始化操作
	Select_exit();
}
void Information_store_clean()								//碎片整理模块
{
	FILE* fp = NULL;
	char* p = NULL;
	char szBuffer[5000] = { 0 };
	Bin_read_end();																   	//从文件中将二进制信息读入数组
	int i = 0,j = 0;
	int nLen = 0;
	p = szBuffer;
	system("cls");
	printf("--------------------------------------------------\n");
	printf("\t    字符串碎片已整理完毕！！:\n");
	printf("--------------------------------------------------\n");
    for (i = 0; i < 10000; i++)								                    //找到有效数据放到另一个数组里面，再把原数组清0，在把有效数组放回去
    {
        if (g_szInf[i] == -1 || g_szInf[i] == -2 )						    	//找到有效数据
        {
            for (j = 0; j < 10000; j++)
            {
                if (szBuffer[j] == '\0' && szBuffer[j + 1] == '\0' && j == 0)
                {
                    strcpy(&szBuffer[j], &g_szInf[i]);							               //把有效数据放到新数组的第一个位置
					nLen += strlen(&szBuffer[j]) + 1;
                    break;
                }
                else if (szBuffer[j] == '\0' && szBuffer[j + 1] == '\0')
                {
                    strcpy(&szBuffer[j+1], &g_szInf[i]);								       //把原有效数据在新数组内依次排好
					nLen += strlen(&szBuffer[j+1]) + 1;						         //赋值有效数据
                    break;
                }
            }
        }
    } 
	if ((fp = fopen("MyData.bin", "w")) == NULL)					//打开二进制文件，w方式
	{
		printf("打开文件失败！\n");
		exit(EXIT_SUCCESS);
	}
	fwrite(p, nLen, 1, fp);													 //写入这个二进制文件
	fclose(fp);
	for (i = 0; i < 5000; i++)
	{
		szBuffer[i]=0;
	}
	Clear_g_szInf();
	printf("碎片整理后的资源分布状态:\n\n");
	Show_store_information();
}



void Select_exit()											//每个模块结束后的选择退出UI界面窗口
{
	int nNum = 0;
	printf("\n1.返回主界面\n");
	printf("2.退出程序\n");
	scanf_s("%d", &nNum);
	if (nNum == 1) {												//输入1返回主菜单
		Main_start();								
	}
	else if (nNum == 2) {										//输入2退出
		exit(0);	
	}
	else
	{
		printf("输入错误，请重新输入:\n");				//输入其他数字报错重新输入
		Select_exit();
	}
}

void Show_information()										//用来显示联系人信息的函数
{
	int nCount = 0;												//用来标记信息编号
	int i = 0;
	Bin_read_end();												//读取二进制文件写入数组
	printf("--------------------------------------------------\n");
	for (i = 0; i < sizeof(g_szInf); i++)
		if ( (g_szInf[i] == -1&&i==0) || (g_szInf[i] == -1 && g_szInf[i-1] =='\0'))					//遍历数组，打印出首位和所有'\0'后标头为-3的数据，即保存姓名的数据
		{
			nCount++;																		//每次打印总个数序号+1
			printf("联系人%d:%s ", nCount, &g_szInf[i + 1]);					
		}
		else if (g_szInf[i] == -2&& g_szInf[i-1] == '\0')					//遍历数组，打印出首位和所有'\0'后标头为-2的数据，即保存手机号的数据
		{
			printf("号码:%s\r\n",&g_szInf[i + 1]);						    	//打印所有有效数据，并且给给每个数据一个标号			
		}					
	printf("--------------------------------------------------\n");
	Clear_g_szInf();							
}

void Bin_write_head(int nLen)												//对二进制文件进行从起始位置写入
{
	FILE* fp = NULL;																//文件指针fp
	char* p = NULL;																//定义一个指针用来存储数组信息
	p = g_szInf;																		//指向数组首地址
	if ((fp = fopen("MyData.bin", "w")) == NULL)					//打开这个二进制文件，w方式
	{
		printf("打开文件失败！\n");
		exit(EXIT_SUCCESS);
	}
	fwrite(p, nLen , 1, fp);													  //把有效数据插入数组
	fclose(fp);
}

void Bin_write_end(int nLen)										    	//对二进制文件进行末尾位置写入(用于增加新数据)
{
	FILE* fp = NULL;
	char* p = NULL;
	p = g_szInf;
	if ((fp = fopen("MyData.bin", "a+")) == NULL)		    	//打开这个二进制文件，a+方式
	{
		printf("打开文件失败！\n");
		exit(EXIT_SUCCESS);
	}
	fwrite(p, nLen, 1, fp);													   	//把有效数据插入数组
	fclose(fp);
}

void Bin_read_head()										//对二进制文件进行从起始位置读取
{
	FILE* fp = NULL;  														
	char* p = NULL;																 
	p = g_szInf;
	if ((fp = fopen("MyData.bin", "w")) == NULL)						//打开二进制文件，w方式
	{
		printf("打开文件失败！\n");
		exit(EXIT_SUCCESS);
	}
	fread(p, sizeof(g_szInf), 1, fp);												 //读取这个二进制文件
	fclose(fp);
}

void Bin_read_end()																	//对二进制文件进行从末尾位置读取								
{
	FILE* fp = NULL;  															
	char* p = NULL;																 
	p = g_szInf;
	if ((fp = fopen("MyData.bin", "a+")) == NULL)					//打开二进制文件，a+方式
	{
		printf("打开文件失败！\n");
		exit(EXIT_SUCCESS);
	}
	fread(p, sizeof(g_szInf), 1, fp);											  //读取这个二进制文件
	fclose(fp);
}

void Clear_g_szInf()																//初始化数组函数
{
	for (int i = 0; i < 10000; i++)							
	{
		g_szInf[i] = 0;																//清空数组，对数组所有数据置为0；
	}
}

