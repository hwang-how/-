# define _CRT_SECURE_NO_WARNINGS 1
# pragma warning(disable:6031)
# include <stdio.h>
# include <stdlib.h>

//��������
// 4 2   �ĸ����  2�����Ƚϵ�����
// 3 1 4 2   ԭʼ����������
// 3 4 1 2
// 3 2 4 1
//
//
// 2 1 
// 2 1
// 1 2
// 0

// �������
// YES
// NO
// NO

// ����˼·
// �Ƚ�һ�Ų��������ٱȽϺ��������Ƚ������ܷ�͸����Ǻ�

// �����
typedef struct Tnode* Tree;
struct Tnode {
	int data;
	Tree left, right;
	int flag;  //  flag���ڱ�ǵ�ǰ����Ƿ�ȽϹ��� 1��ʾ�ȽϹ��ˣ�0��ʾδ�Ƚϣ�
};
Tree CreatTree(int N);
Tree Insert(Tree T, int Data);
Tree NewNode(int Data);
int CompareTree(Tree T, int N);
int Check(Tree T, int Data);
void Reset(Tree T);
void FreeTree(Tree T);
//��������ܴ
int main()
{
	// step0:�������еĽڵ����ʹ��Ƚϵ����и���N��L
	int N, L;
	Tree T;
	scanf("%d", &N);
	// step1:������ʼ�Ķ��������
	// step2:���������������������洴�������Ƚ�
	while (N)
	{
		scanf("%d", &L);
		T=CreatTree(N);   //������ƣ������������ƵĽ�����������������������ÿ�����ļ�ֵ��ɴ���������������ָ��
		while (L--)
		{
			int judge = CompareTree(T,N);//compareTree�����Ƚ��Ѿ����õĲ�������֮������������Ƿ���ͬһ�����������Ƿ���1
			if (judge)
				printf("YES\n");
			else
				printf("NO\n");
			Reset(T);//���½�����flag��λ0��������һ�����еıȽ�
		}
		FreeTree(T);
		scanf("%d", &N);//�����ٴι����µ���
	}
	return 0;
}

//������
Tree CreatTree(int N)
{
	Tree T;
	int Data,i;
	scanf("%d", &Data);
	T = NewNode(Data);//�����������
	for (i = 1; i < N; i++)//ѭ������N-1�����
	{
		scanf("%d", &Data);
		T = Insert(T,Data);
	}
	return T;
}
//�ڵ���뺯��
Tree Insert(Tree T,int Data)
{
	if (!T)//��T��NULLʱ������һ���µĽ��
		T = NewNode(Data);
	else if (Data < T->data)//��ʱӦ�ò��뵽T�����
		T->left = Insert(T->left, Data);
	else if (Data > T->data)//��ʱӦ�ò��뵽T���ұ�
		T->right = Insert(T->right, Data);
	return T;
}
Tree NewNode(int Data)
{
	Tree T = (Tree)malloc(sizeof(struct Tnode));
	if (T)
	{
		T->data = Data;
		T->left = T->right = NULL;
		T->flag = 0;
	}
	return T;
}
//CompareTree������ʵ��
int CompareTree(Tree T, int N)
{
	int Data;
	int Flag = 0;//�������������Ƿ��Ѿ������˲�ͬ
	while (N--)
	{
		scanf("%d", &Data);
		/*int check = Check(T, Data);*///Check����������鵱ǰ����ļ�ֵ�Ͳ������Ƿ���ϣ��Ƿ���1
		if ((!Flag) && (!Check(T, Data)))
			Flag = 1;
		//if (!check)
		//{
		//	return 0;//������ֵ��������N������û����ȫ�����ȥ�ͽ���ѭ���ˣ������������Ҫ��
		//	break;
		//}
	}
	if (Flag)
		return 0;
	else
		return 1;
}

//Check������ʵ��
int Check(Tree T, int Data)
{
	if (T->flag)
	{
		if (Data < T->data)
			return Check(T->left, Data);
		else if (Data > T->data)
			return Check(T->right, Data);
		else
			return 0;//���˵���ֲ鵽�ظ��Ľ���ˣ����϶�����ͬ
	}
	else
	{
		if (Data = T->data)
		{
			T->flag = 1;
			return 1;
		}
		else
			return 0;
	}
}
//Reset����
void Reset(Tree T)
{
	if (T && T->flag == 1)
	{
		T->flag = 0;
		Reset(T->left);
		Reset(T->right);
	}
}
//�ͷ����ռ�
void FreeTree(Tree T)
{
	if (T->left)
		FreeTree(T->left);
	if (T->right)
		FreeTree(T->right);
	free(T);
}