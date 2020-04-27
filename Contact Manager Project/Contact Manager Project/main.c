#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<time.h>
#pragma warning(disable:4996)

void Main_show();											//UI�����洰��
void Main_start();												//����ִ�к���
void Information_increment();						//��ϵ����Ϣ����ģ��
void Information_delete();								//��ϵ����Ϣɾ��ģ��
void Information_modify();								//��ϵ����Ϣ�޸�ģ��
void Information_query();								//��ϵ����Ϣ��ѯģ��
void Information_count();								//��ϵ����Ϣͳ��ģ��
void Show_store_information();						//�鿴��ϵ����Ϣ�洢�ֲ�ģ��
void Information_store_clean();						//��Ƭ����ģ��
void Select_exit();											//ÿ��ģ��������UI���洰��
void Show_information();								//��ʾ��ϵ����Ϣ
void Bin_read_head();										//����ʼλ�ö�ȡ�ļ�
void Bin_read_end();										//�ӽ���λ�ö�ȡ�ļ�
void Bin_write_head(int Lens);							//����ʼλ��д���ļ���nlens��ʾд��ĳ���
void Bin_write_end(int Lens);							//�ӽ���λ��д���ļ���nlens��ʾд��ĳ���
void Clear_g_szInf();											//�������ʼ��������
char g_szInf[10000] = { 0 };								//����������ϵ��������Ϣ������

/*
Լ������ÿ���洢������һ���±�������¼�洢״̬������
 -1������Ч���ݴ洢������,
 -3������Ч���ݴ洢������
 -2������Ч���ݴ洢�ĺ���
 -4������Ч���ݴ洢�ĺ���
*/

int main()
{
	Main_start();								//��ʼִ�г������
	return 0;
}

void Main_start()							//����ʼִ��
{
	int nNum = 0;
	system("cls");
	Main_show();
	scanf_s("%d", &nNum);			//�����û������������ѡ����
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
		printf("�����������������\n");							//������󷵻�UI�����洰��
		Sleep(1000);
		Main_start();											
	}
}

void Main_show()															//UI�����洰��
{
	printf("--------------------------------------------------\n");
	printf("\t    ��ӭ������ϵ����Ϣ����ϵͳ\n");
	printf("--------------------------------------------------\n");
	printf("��������Ҫִ�еĲ���(������ִ��)��\n");
	printf("\t1.�����µ���ϵ��\n");
	printf("\t2.ɾ����ϵ��\n");
	printf("\t3.�޸���ϵ��\n");
	printf("\t4.��ѯ��ϵ��\n");
	printf("\t5.ͳ����ϵ��\n");
	printf("\t6.�鿴��ǰ�洢��Ϣ\n");
	printf("\t7.������Ƭ���鿴��ǰ����õ���Ƭ״̬\n");
	printf("\t8.�鿴��ǰ�洢��������ϵ����Ϣ\n");
	printf("\t9.�˳�����\n");
	printf("--------------------------------------------------\n");
}

void Information_increment()													//��ϵ����Ϣ����ģ��(�Ƚ����ӵ����ݱ��������飬ÿ����һ��д��һ��)
{
	int i = 0;																	
	int nLen = 0;																		//������¼������Ϣ�ĳ���
	char szAdd_name[300] = { 0 };											//���������û����������
	long long int Add_number = 0 ;											//���������û�����ĵ绰����
	system("cls");
	printf("--------------------------------------------------\n");
	printf("\t��ϵ����Ϣ����ģʽ:\n");
	printf("--------------------------------------------------\n");
	printf("����������Ҫ��ӵ���ϵ����Ϣ��\n");
	printf("������洢����ϵ������:\n");
	scanf_s("%s", szAdd_name, sizeof(szAdd_name));
	for (i = 0; i < 300; i++)																//����������Ϣ
	{
		if (g_szInf[i] == '\0' && g_szInf[i + 1] == '\0' && i == 0)		//������Ϊ��ʱ
		{
			g_szInf[i] = -1;																		//ÿ�������׵�ַ�����ʾ�������±�-3
			strcpy(&g_szInf[i + 1], szAdd_name);									//���������Ϣ�������±���λ��			
			nLen = strlen(szAdd_name) + 1;											//���㳤������������Ϣ�ĳ���
			break;
		}
	}
	printf("����Ҫ�洢���ֻ����룺(����ΪС��22λ������)\n");
	scanf_s("%lld", &Add_number, sizeof(Add_number));				//���Ƿ�����
	while (1)
	{
		if (Add_number >= 9223372036854775807)								//����long long int ���ͳ��ȱ�����������
		{
			printf("������Ч���֣������������벻����22λ������:\n");
			Add_number = 0;
			scanf_s("%lld", &Add_number, sizeof(Add_number));
		}
		if (Add_number < 9223372036854775807)
		{
			break;
		}
	}
	printf("������Ϣ�ɹ���");
	for (i = 0; i < 300; i++)															//�����ֻ�����Ϣ
	{
		if (g_szInf[i] == '\0' && g_szInf[i + 1] == '\0')
		{
			char szAdd_number[20] = { 0 };
			sprintf(szAdd_number, "%lld", Add_number);
			g_szInf[i + 1] = -2;														//ÿ�������׵�ַ�����ʾ�������±�-3
			strcpy(&g_szInf[i + 2], szAdd_number); 			    		//���������Ϣ�������±���λ��	
			nLen += strlen(szAdd_number) + 3;
			break;
		}
	}
	Bin_write_end(nLen);																//ÿ����Ӷ��Ӷ������ļ�β��д���ļ���
	printf("��Ӻ����ϵ����ϢΪ:\n");											//��ֹ�ϵ��ͻ��״���������			
	printf("--------------------------------------------------\n");
	Show_information();
	Clear_g_szInf();																		//�������ʼ��
	Select_exit();																		//ѡ���˳�
}	

void Information_delete()														//��ϵ����Ϣɾ��ģ��
{
	system("cls");
	int i = 0;
	int nLen = 0;																			//������¼�޸ĺ�����ݳ���
	int nIsTrue = 0;																		//��������ǲ�ѯ���޸ĵ�����
	int nNum = 0;																			//��¼�û�������Ϣ
	int nCount = 0;																		//����ͳ����ϵ�˱��
	//char szDel[100] = { 0 };															//������������������û�������ַ�
	printf("--------------------------------------------------\n");
	printf("\t    ��ӭ������ϵ��ɾ��ģʽ:\n");
	printf("--------------------------------------------------\n");
	printf("��ѡ��ɾ��ģʽ:\n");
	printf("1.������ɾ����Ӧ����ϵ��\n");
	printf("2.��ʽ�����������ϵ����Ϣ\n");
	printf("3.����������\n");
	scanf_s("%d", &nNum);
	
	if (nNum == 1)
	{
		Show_information();												 //�Ȳ鿴�µ�ǰ�洢��������
		Bin_read_end();
		printf("��������Ҫɾ������ϵ�˱�ţ�\n");
		scanf_s("%d", &nNum);
		for (i = 0; i < 10000; i++)										//�������飬����û�ɾ�����ַ����������ڵ��±�һ�£�������ɾ��
		{
			if ((g_szInf[i] == -1 && i == 0) || (g_szInf[i] == -1 && g_szInf[i - 1] == '\0'))					
			{																							//�������飬��ӡ����λ������'\0'���ͷΪ-3�����ݣ�����������������
				nCount++;								
				if (nNum == nCount)														//�����������ַ�����űȽ�
				{
					g_szInf[i] = -3;																	//ɾ���������ݼ�����Ч���ݵ��±���Ϊ-4
				}
			}
			else if (g_szInf[i] == -2 && g_szInf[i - 1] == '\0')					//�������飬��ӡ����λ������'\0'���ͷΪ-2�����ݣ��������ֻ��ŵ�����
			{
				if (nNum == nCount)
				{
					g_szInf[i] = -4;																	//ɾ���������ݼ�����Ч���ݵı�ͷ��Ϊ-4
					nIsTrue = 1;
					printf("��ϲ��ɾ���ɹ���\n");
				}
			}
			if (g_szInf[i] == '\0' && g_szInf[i + 1] == '\0' && g_szInf[i + 2] == '\0' && g_szInf[i + 3] == '\0')						
			{																									//�ҵ�����Ϊ0�ĵ�ַ����ѭ���˳��ĳ���
				nLen = i+1;
				break;
			}
		}
		if (nIsTrue == 0)									//���벻���ڵı��ʱ
		{
			printf("û����һ����ϵ����Ϣ");
		}

		Bin_write_head(nLen);							//��ִ��ɾ������������ݴ��ض���������		
		Clear_g_szInf();
		printf("ɾ�������ϵ��: \n");
		Show_information();
		Select_exit();
	}

	if (nNum == 2)											//��ʽ������
	{
		Bin_read_head();										//����ʼλ�ö�ȡ�ļ��������������
		printf("��ǰ������ϵ���Ѿ�ȫ����ʽ��!!\n");
		Select_exit();
	}

	if (nNum == 3) {											//�������˵�
		Main_start();
	}
	printf("�������\n");
	Select_exit();
}

void Information_modify()								//��ϵ����Ϣ�޸�ģ��
{
	int i = 0,j=0;
	int nLen = 0;																			//������¼�޸ĺ�����ݳ���
	int nIsTrue = 0;																		//��������ǲ�ѯ���޸ĵ�����
	int nNum = 0;																			//��¼�û�������Ϣ
	int nCount = 0;																		//����ͳ����ϵ�˱��
	char szName[300] = { 0 };
	char szNum[300] = { 0 };
	char szInf[300] = { 0 };
	int nszAddLen = 0;																	//��¼�û���������ݿ�ĳ���
	int nszLen = 0;																			//������¼ԭ�����ݿ鳤��		
	system("cls");
	printf("--------------------------------------------------\n");
	printf("\t    ��ӭ�����ַ����޸�ģʽ:\n");
	printf("--------------------------------------------------\n");
	printf("��ǰ�洢����ϵ��Ϣ������ʾ:\n");
	Show_information();
	Bin_read_end();																	//���ļ��н���������Ϣ��������
	printf("��������Ҫ�޸ĵ���ϵ�����ڱ�ţ�");
	scanf_s("%d", &nNum);
	for (i = 0; i < 1000; i++)														//���ȼ���һ��ԭ���ݿ鳤��
	{
		if ((g_szInf[i] == -1 && i == 0) || (g_szInf[i] == -1 && g_szInf[i - 1] == '\0'))			
		{																							//����һ����Ч��������ʱ��ʼ����ѭ��
			nCount++;
			if (nCount == nNum)													
			{
				while(1)
				{
					nszLen++;										
					i++;
					if (g_szInf[i] == '\0' && (g_szInf[i + 1] == -1 || g_szInf[i + 1] == -3|| g_szInf[i + 1]=='\0'))
					{																			//�ҵ�����Ϊ0�ĵ�ַ����ѭ���˳��ĳ���
						break;	
					}
				}
			}
		}
	}
	nCount=0;																		//��ʼ��������
	printf("��Ҫ�޸��������Ǻ��룿(����1��2��ѡ��)\n");
	printf("1.�޸�����");
	printf("2.�޸ĵ绰����");
	scanf_s("%d", &i);
	if (i == 1)
	{
		printf("������Ҫ�޸ĵ�����:\n");
		scanf_s("%s", szName, sizeof(szName));
		for (i = 0; i < 10000; i++)
		{
			if (g_szInf[i] == -1)
			{
				nCount++;
				if (nCount == nNum)
				{
					g_szInf[i] = -6;				                             //���ƥ�䵽Ҫ�޸ĵ��ַ�����ԭ�±���Ϊ-6,��Ϊ���޸ı��
					strcpy(szInf, szName);  
					nszAddLen = strlen(szName)+1 ;
				}
			}
			if (g_szInf[i] == -2)
			{
				if (nCount == nNum)
				{
					g_szInf[i] = -4;											 //�±���Ϊ��Ч����-4
					szNum[j] = -2;
					for (j=0; j<=20; j++,i++)
					{
						szNum[j+1] = g_szInf[i + 1];
						if (g_szInf[i] == '\0')
						{
							break;
						}
					}
					strcpy(szInf + nszAddLen, szNum);			//���޸ĺõ�ȫ����Ϣ����szInf�����ڡ�
					nszAddLen += strlen(szNum)+1;
				}
			}
		}
		if (nszLen<nszAddLen)									//��ԭ���ݳ���С���û�����ĳ��ȣ��治�£����¿��ٿռ�洢
		{
			for (j= 0; j < 1000;j++)
			{
				if (g_szInf[j] == -6)											//δ���ñ�ǣ���������޸ı��
				{
					g_szInf[j] = -3;												//�����Ϊ��Ч����
				}
				if (g_szInf[j] == '\0' && g_szInf[j + 1] == '\0' && g_szInf[j + 2] == '\0' && g_szInf[j + 3] == '\0')
				{																		//ѭ����������
					nLen = j;
					g_szInf[j + 1] = -1;																	//�洢����λ���ݲ����±�-1
					memcpy(&g_szInf[j + 2], szInf, nszAddLen);					    	//���޸ĺ���������ݿ������洢��Ϣ������
					//strcpy(&g_szInf[j + 2], szInf);
					nLen += nszAddLen + 2;
					break;
				}
			}	
		}

		if (nszLen >= nszAddLen)								//��ԭ���ݳ��ȴ����û�����ĳ��ȣ����Դ��£���ԭ�ռ�洢
		{
			for (j = 0; j < 1000; j++)
			{
				if (g_szInf[j] == -6 && j == 0)					//�ҵ����޸ı��-6���ڴ˴������޸�����
				{
					g_szInf[j] = -1;																		//����������Ϊ-1
					memcpy(&g_szInf[j + 1], szInf, nszAddLen);						//���޸ĺ���������ݿ������洢��Ϣ������
				}
				if (g_szInf[j] == '\0' && g_szInf[j + 1] == -6)									
				{
					nLen = j;
					g_szInf[j + 1] = -1;
					memcpy(&g_szInf[j + 2], szInf, nszAddLen);						
				}
				if (g_szInf[j] == '\0' && g_szInf[j + 1] == '\0' && g_szInf[j + 2] == '\0' && g_szInf[j + 3] == '\0')
				{																								//�ҵ�����Ϊ0�ĵ�ַ����ѭ���˳��ĳ���
					nLen = j+1;
					break;
				}
			}
		}
	}
	if (i == 2)
	{
		printf("������Ҫ�޸ĵĺ��룺\n");
		szNum[0] = -2;													//�洢�������к����������ò����±�-2
		scanf_s("%s", szNum+1, sizeof(szNum));
		for (i = 0; i < 10000; i++)
		{
			if (g_szInf[i] == -1)												//����������Ч����
			{
				nCount++;
				if (nCount == nNum)										//�����������Ŷ�Ӧ����Ч����ʱ
				{
					g_szInf[i] = -5;												//���ƥ�䵽Ҫ�޸ĵ��ַ�����ԭ��ͷ��Ϊ-5,��Ϊɾ������޸�
					szInf[j] = -1;													//���±�-1���������飬��ʾ��Ч��������
					nszAddLen++;
					for (j = 0; j <= 20; j++)
					{
						nszAddLen++;
						szInf[j + 1] = g_szInf[i + 1];						//�������д洢�������������µ�����szInf
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
			if (g_szInf[i] == -2)										//��������Ч����
			{
				if (nCount == nNum)
				{
					g_szInf[i] = -4;										//�����������޸ĵĺ������ݣ�����Ϊ��Ч����-4
					strcpy(szInf + nszAddLen, szNum);		//���޸ĺõ���Ϣ����szInf�����ڡ�
					nszAddLen += strlen(szNum);
					break;
				}
			}
		}

		if (nszLen < nszAddLen)									//��ԭ���ݳ���С���û�����ĳ��ȣ��治�£����¿��ٿռ�洢
		{
			for (j = 0; j < 1000; j++)
			{	
				if (g_szInf[j] == -5)									//��������
				{
					g_szInf[j] = -3;										//�����Ϊ��Ч����
				}
				if (g_szInf[j] == '\0' && g_szInf[j + 1] == '\0' && g_szInf[j + 2] == '\0' && g_szInf[j + 3] == '\0')
				{
					nLen = j;
	//				g_szInf[j + 1] = -1;												//��ԭ�±���Ϊ��Ч��������-1
					memcpy(&g_szInf[j + 1], szInf, nszAddLen);		//���������ݿ������洢��Ϣ������
					//strcpy(&g_szInf[j + 2], szInf);
					nLen += nszAddLen + 2;
					break;
				}
			}
		}
		if (nszLen >= nszAddLen)								//��ԭ���ݳ��ȴ����û�����ĳ��ȣ����Դ��£���ԭ�ռ�洢
		{
			for (j = 0; j < 1000; j++)
			{
				if (g_szInf[j] == -5 && j == 0)					//�����ҵ�-5���
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
				{																//�ҵ�����Ϊ0�ĵ�ַ����ѭ���˳��ĳ���
					nLen = j + 1;
					break;
				}
			}
		}
	}
	Bin_write_head(nLen);											//��ִ��ɾ������������ݴ��ض���������		
	Clear_g_szInf();														//ִ�������ʼ������
	printf("�޸ĺ�ĵ绰����ϢΪ��\n");
	Show_information();
	Select_exit();
}


void Information_query()													//��ϵ����Ϣ��ѯģ��
{
	int nNum=0;
	int nTemp = 0;
	int nCount= 0;
	int i = 0,j=0;
	char szName[100] = { 0 };
	char szNum[100] = { 0 };
	system("cls");
	printf("--------------------------------------------------\n");
	printf("\t    ��ӭ������Ϣ��ѯģʽ:\n");
	printf("--------------------------------------------------\n");
	printf("��ǰ������ϢΪ:\n");
	Show_information();
	Bin_read_end();																	//���ļ��н���������Ϣ��������
	printf("��ѡ���ѯģʽ:\n");
	printf("1.������������ѯ�ֻ���\n");
	printf("2.���������ֻ��Ų�ѯ����\n");
	printf("3.ģ�������������ֻ���\n");
	printf("4.ģ�������ֻ��Ų�����\n");
	scanf_s("%d", &nNum);
	if (nNum == 1)
	{
		printf("��������Ҫ��ѯ������:\n\n");
		nTemp = 0;
		scanf_s("%s", &szName,sizeof(szName));
		for (i = 0; i < 10000; i++)
		{
			if (g_szInf[i] == -1)														
			{
				nCount++;
				if ((strcmp(&g_szInf[i + 1], szName)) == 0)								//ƥ���ַ����Ƿ�һ��
				{
					nTemp = 1;
					printf("��ѯ������ϵ����Ϣ: ");
					printf("%d. ����:%s  ",nCount, &g_szInf[i + 1]);						//��ӡ����
					for (; i < 1000; i++)
					{
						if (g_szInf[i] == -2)
						{
							printf("�ֻ���:%s\r\n", &g_szInf[i + 1]);							//��ӡ�ֻ���
							break;
						}
					}
				}
			}
		}
	}
	if (nNum == 2)
	{
		printf("��������Ҫ��ѯ�ĺ���:\n\n");
		nTemp = 0;
		scanf_s("%s", &szNum, sizeof(szNum));
		for (i = 0; i < 10000; i++)													//�ڴ�������Ѱ��ƥ����ַ���
		{
			if (g_szInf[i] == -2)														
			{
				nCount++;
				if ((strcmp(&g_szInf[i + 1], szNum)) == 0)					//ƥ�������ַ����Ƿ�����ͬ
				{
					nTemp = 1;
					printf("���ҵ�����ϵ����Ϣ:");
					printf("%d. ", nCount);
					printf("���� ");
					printf("%s  ",&g_szInf[i + 1]);									
					for (j=i; j > 0; j--)														//����������ʱ�����ӡ��������
					{
						if (g_szInf[j] == -1)
						{
							printf(" ��Ӧ��ϵ���� : %s\r\n", &g_szInf[j + 1]);									
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
		printf("��������Ҫ��ѯ��������Ϣ:\n\n");
		scanf_s("%s", &szName, sizeof(szName));									 //�����û�Ҫ���ҵ�ģ���ֶ�
		for (i = 0; i < 10000; i++)
		{
			if (g_szInf[i] == -1)																	//�Ƚ���Ч�ַ����������Ƿ��м���������
			{
				nCount++;
				if (strstr(&g_szInf[i + 1], szName) != NULL)						//����strstr�������������ַ���ÿһ����Ч�����Ƿ����
				{
					nTemp = 1;
					printf("ģ��ƥ�䵽������:%d:%s  ", nCount, &g_szInf[i + 1]);
					for (; i < 1000; i++)
					{
						if (g_szInf[i] == -2)
						{
							printf("�ֻ���:%s\r\n", &g_szInf[i + 1]);							 
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
		printf("��������Ҫ��ѯ���ֻ���Ϣ:\n\n");
		scanf("%s", &szNum);																  //�����û�Ҫ���ҵ�ģ���ֶ�
		for (i = 0; i < 10000; i++)
		{
			if (g_szInf[i] == -2)																//�Ƚ���Ч�ַ����������Ƿ��м���������
			{
				nCount++;
				if (strstr(&g_szInf[i + 1], szNum) != NULL)						//����strstr�������������ַ���ÿһ����Ч�����Ƿ����
				{
					printf("ģ��ƥ�䵽���ֻ���:%d.%s ", nCount, &g_szInf[i + 1]);
					for (j=i; i > 0; j--)
					{
						if (g_szInf[j] == -1)
						{
							nTemp = 1;
							printf("����:%s\r\n", &g_szInf[j + 1]);									//��ӡ�ֻ���
							break;
						}
					}
				}
			}
		}
	}
	if (nTemp == 0)
	{
		printf("\n�Բ���û�в�ѯ�����������Ϣ\n");
	}
	Clear_g_szInf();																			//ִ�������ʼ������
	Select_exit();
}

void Information_count()															//��ϵ����Ϣͳ��ģ��
{
	int i = 0;
	int j = 0;
	float nCount = 0;																		//����������ϵ�˳����ܴ���
	float nIndex = 0;																		//����������ϵ���ظ����ִ���
	system("cls");
	printf("--------------------------------------------------\n");
	printf("\t    ��ǰΪ��ϵ����Ϣͳ��ģʽ:\n");
	printf("--------------------------------------------------\n");
	printf("��ǰ�洢������ϵ����ϢΪ:\n");
	Show_information();
	Bin_read_end();																			//���ļ��н���������Ϣ��������
	for (i = 0; i < sizeof(g_szInf); i++)												//���ȼ�����ϵ�˳����ܴ���
		if ((g_szInf[i] == -1 && i == 0) || (g_szInf[i] == -1 && g_szInf[i - 1] == '\0'))				
		{
			nCount++;																			//��¼�洢���ж��ٸ���ϵ��
		}
	printf("��ǰ������ϵ���ܸ�����:%.0f\n",nCount);
	printf("--------------------------------------------------\n");
	printf("��ǰÿ����ϵ�˳��ִ���������Ϊ:\n");
	printf("--------------------------------------------------\n");
	for (i = 0; i < 1000; i++)
	{
		nIndex = 1;
		if ((g_szInf[i] == -1 && i == 0) || (g_szInf[i] == -1 && g_szInf[i - 1] == '\0'))					//�������飬��ӡ����λ������'\0'���ͷΪ-3�����ݣ�����������������
		{
			for (j = i+strlen(&g_szInf[i+1]); j < 1000; j++)							//����Ѱ���Ƿ���ڶ�γ��ֵ���ϵ��
			{
				if ((strcmp(&g_szInf[i + 1], &g_szInf[j])) == 0)						//ƥ��֮����ֵ������Ƿ����һ�γ��ֵ�һ��
				{
					g_szInf[j-1] = -3;																	//��ƥ�䵽���ֳ������ε��������޸ĵ�һ�γ��ֺ�������±꣬ʹ��ֻ��ӡһ��
					nIndex++;
				}
			}
			printf("����: %s ", &g_szInf[i + 1]);
			printf("���ִ�����%.0f ", nIndex);
			float ratio = ((nIndex / nCount) * 100);										//����ת����float������ٷֱ�
			printf("���ֱ��� :%7.2f%%\n", ratio);
		}
	}
	printf("--------------------------------------------------\n");

	Clear_g_szInf();												//ִ�������ʼ������
	Select_exit();
}
void Show_store_information()						//�鿴��ϵ����Ϣ�洢�ֲ�ģ��
{
	int i = 0;
	int j = 0;
	system("cls");
	printf("--------------------------------------------------\n");
	printf("\t    ��ǰΪ��Դ�洢��Ϣ�鿴ģʽ:\n");
	printf("--------------------------------------------------\n");
	printf("��ǰ�洢����ϵ����ϢΪ:\n");
	Show_information();
	Bin_read_end();																			//���ļ��н���������Ϣ��������
	printf("��ǰ�ַ���ռ���ڴ�ռ�Ϊ(U��ʾ��ʹ��ռ�ݵ�����һ�ֽ� F��ʾ��Ч����):\n");
	for (i = 0; i < 1000; i++)
	{
		if (g_szInf[i] == -1 )																	//�жϵ�һ������Ƿ�Ϊ��Ч����
		{
			printf("U");
		}
		if (g_szInf[i] == -1 || g_szInf[i] == -2)										//�ҵ�ռ�õ�����
		{
			for (j = i+1 ; j <= strlen(&g_szInf[i + 1])+i; j++)
			{
				printf("U");																		//ռ�õ�������U��ʾ
				i++;
			}
		}
		if (g_szInf[j] == '\0' && (g_szInf[j + 1] == -2 || g_szInf[j + 1] == -1))
		{
			printf("U");																			//���ַ����׶η���Ϊռ������
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
	Clear_g_szInf();														//ִ�������ʼ������
	Select_exit();
}
void Information_store_clean()								//��Ƭ����ģ��
{
	FILE* fp = NULL;
	char* p = NULL;
	char szBuffer[5000] = { 0 };
	Bin_read_end();																   	//���ļ��н���������Ϣ��������
	int i = 0,j = 0;
	int nLen = 0;
	p = szBuffer;
	system("cls");
	printf("--------------------------------------------------\n");
	printf("\t    �ַ�����Ƭ��������ϣ���:\n");
	printf("--------------------------------------------------\n");
    for (i = 0; i < 10000; i++)								                    //�ҵ���Ч���ݷŵ���һ���������棬�ٰ�ԭ������0���ڰ���Ч����Ż�ȥ
    {
        if (g_szInf[i] == -1 || g_szInf[i] == -2 )						    	//�ҵ���Ч����
        {
            for (j = 0; j < 10000; j++)
            {
                if (szBuffer[j] == '\0' && szBuffer[j + 1] == '\0' && j == 0)
                {
                    strcpy(&szBuffer[j], &g_szInf[i]);							               //����Ч���ݷŵ�������ĵ�һ��λ��
					nLen += strlen(&szBuffer[j]) + 1;
                    break;
                }
                else if (szBuffer[j] == '\0' && szBuffer[j + 1] == '\0')
                {
                    strcpy(&szBuffer[j+1], &g_szInf[i]);								       //��ԭ��Ч�������������������ź�
					nLen += strlen(&szBuffer[j+1]) + 1;						         //��ֵ��Ч����
                    break;
                }
            }
        }
    } 
	if ((fp = fopen("MyData.bin", "w")) == NULL)					//�򿪶������ļ���w��ʽ
	{
		printf("���ļ�ʧ�ܣ�\n");
		exit(EXIT_SUCCESS);
	}
	fwrite(p, nLen, 1, fp);													 //д������������ļ�
	fclose(fp);
	for (i = 0; i < 5000; i++)
	{
		szBuffer[i]=0;
	}
	Clear_g_szInf();
	printf("��Ƭ��������Դ�ֲ�״̬:\n\n");
	Show_store_information();
}



void Select_exit()											//ÿ��ģ��������ѡ���˳�UI���洰��
{
	int nNum = 0;
	printf("\n1.����������\n");
	printf("2.�˳�����\n");
	scanf_s("%d", &nNum);
	if (nNum == 1) {												//����1�������˵�
		Main_start();								
	}
	else if (nNum == 2) {										//����2�˳�
		exit(0);	
	}
	else
	{
		printf("�����������������:\n");				//�����������ֱ�����������
		Select_exit();
	}
}

void Show_information()										//������ʾ��ϵ����Ϣ�ĺ���
{
	int nCount = 0;												//���������Ϣ���
	int i = 0;
	Bin_read_end();												//��ȡ�������ļ�д������
	printf("--------------------------------------------------\n");
	for (i = 0; i < sizeof(g_szInf); i++)
		if ( (g_szInf[i] == -1&&i==0) || (g_szInf[i] == -1 && g_szInf[i-1] =='\0'))					//�������飬��ӡ����λ������'\0'���ͷΪ-3�����ݣ�����������������
		{
			nCount++;																		//ÿ�δ�ӡ�ܸ������+1
			printf("��ϵ��%d:%s ", nCount, &g_szInf[i + 1]);					
		}
		else if (g_szInf[i] == -2&& g_szInf[i-1] == '\0')					//�������飬��ӡ����λ������'\0'���ͷΪ-2�����ݣ��������ֻ��ŵ�����
		{
			printf("����:%s\r\n",&g_szInf[i + 1]);						    	//��ӡ������Ч���ݣ����Ҹ���ÿ������һ�����			
		}					
	printf("--------------------------------------------------\n");
	Clear_g_szInf();							
}

void Bin_write_head(int nLen)												//�Զ������ļ����д���ʼλ��д��
{
	FILE* fp = NULL;																//�ļ�ָ��fp
	char* p = NULL;																//����һ��ָ�������洢������Ϣ
	p = g_szInf;																		//ָ�������׵�ַ
	if ((fp = fopen("MyData.bin", "w")) == NULL)					//������������ļ���w��ʽ
	{
		printf("���ļ�ʧ�ܣ�\n");
		exit(EXIT_SUCCESS);
	}
	fwrite(p, nLen , 1, fp);													  //����Ч���ݲ�������
	fclose(fp);
}

void Bin_write_end(int nLen)										    	//�Զ������ļ�����ĩβλ��д��(��������������)
{
	FILE* fp = NULL;
	char* p = NULL;
	p = g_szInf;
	if ((fp = fopen("MyData.bin", "a+")) == NULL)		    	//������������ļ���a+��ʽ
	{
		printf("���ļ�ʧ�ܣ�\n");
		exit(EXIT_SUCCESS);
	}
	fwrite(p, nLen, 1, fp);													   	//����Ч���ݲ�������
	fclose(fp);
}

void Bin_read_head()										//�Զ������ļ����д���ʼλ�ö�ȡ
{
	FILE* fp = NULL;  														
	char* p = NULL;																 
	p = g_szInf;
	if ((fp = fopen("MyData.bin", "w")) == NULL)						//�򿪶������ļ���w��ʽ
	{
		printf("���ļ�ʧ�ܣ�\n");
		exit(EXIT_SUCCESS);
	}
	fread(p, sizeof(g_szInf), 1, fp);												 //��ȡ����������ļ�
	fclose(fp);
}

void Bin_read_end()																	//�Զ������ļ����д�ĩβλ�ö�ȡ								
{
	FILE* fp = NULL;  															
	char* p = NULL;																 
	p = g_szInf;
	if ((fp = fopen("MyData.bin", "a+")) == NULL)					//�򿪶������ļ���a+��ʽ
	{
		printf("���ļ�ʧ�ܣ�\n");
		exit(EXIT_SUCCESS);
	}
	fread(p, sizeof(g_szInf), 1, fp);											  //��ȡ����������ļ�
	fclose(fp);
}

void Clear_g_szInf()																//��ʼ�����麯��
{
	for (int i = 0; i < 10000; i++)							
	{
		g_szInf[i] = 0;																//������飬����������������Ϊ0��
	}
}

