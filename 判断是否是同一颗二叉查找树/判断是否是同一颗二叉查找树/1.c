# define _CRT_SECURE_NO_WARNINGS 1
# pragma warning(disable:6031)
# include <stdio.h>
# include <stdlib.h>

//输入样例
// 4 2   四个结点  2个待比较的序列
// 3 1 4 2   原始查找树序列
// 3 4 1 2
// 3 2 4 1
//
//
// 2 1 
// 2 1
// 1 2
// 0

// 输出样例
// YES
// NO
// NO

// 解题思路
// 先建一颗查找树，再比较后两个待比较序列能否和该树吻合

// 树结点
typedef struct Tnode* Tree;
struct Tnode {
	int data;
	Tree left, right;
	int flag;  //  flag用于标记当前结点是否比较过了 1表示比较过了，0表示未比较；
};
Tree CreatTree(int N);
Tree Insert(Tree T, int Data);
Tree NewNode(int Data);
int CompareTree(Tree T, int N);
int Check(Tree T, int Data);
void Reset(Tree T);
void FreeTree(Tree T);
//主函数框架搭建
int main()
{
	// step0:读入序列的节点数和待比较的序列个数N和L
	int N, L;
	Tree T;
	scanf("%d", &N);
	// step1:创建初始的二叉查找树
	// step2:输入后面的两个序列与上面创建的树比较
	while (N)
	{
		scanf("%d", &L);
		T=CreatTree(N);   //参数设计：根据树的限制的结点个数来创建，函数中输入每个结点的键值完成创建，并返回树根指针
		while (L--)
		{
			int judge = CompareTree(T,N);//compareTree用来比较已经建好的查找树和之后输入的序列是否是同一个查找树，是返回1
			if (judge)
				printf("YES\n");
			else
				printf("NO\n");
			Reset(T);//重新将树的flag置位0，方便下一个序列的比较
		}
		FreeTree(T);
		scanf("%d", &N);//重新再次构建新的树
	}
	return 0;
}

//创建树
Tree CreatTree(int N)
{
	Tree T;
	int Data,i;
	scanf("%d", &Data);
	T = NewNode(Data);//创建树根结点
	for (i = 1; i < N; i++)//循环插入N-1个结点
	{
		scanf("%d", &Data);
		T = Insert(T,Data);
	}
	return T;
}
//节点插入函数
Tree Insert(Tree T,int Data)
{
	if (!T)//当T是NULL时，创建一个新的结点
		T = NewNode(Data);
	else if (Data < T->data)//此时应该插入到T的左边
		T->left = Insert(T->left, Data);
	else if (Data > T->data)//此时应该插入到T的右边
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
//CompareTree函数的实现
int CompareTree(Tree T, int N)
{
	int Data;
	int Flag = 0;//这个标记用来看是否已经检测出了不同
	while (N--)
	{
		scanf("%d", &Data);
		/*int check = Check(T, Data);*///Check函数用来检查当前输入的键值和查找树是否符合，是返回1
		if ((!Flag) && (!Check(T, Data)))
			Flag = 1;
		//if (!check)
		//{
		//	return 0;//这里出现的问题就是N个数还没有完全输入进去就结束循环了，不符合输入的要求
		//	break;
		//}
	}
	if (Flag)
		return 0;
	else
		return 1;
}

//Check函数的实现
int Check(Tree T, int Data)
{
	if (T->flag)
	{
		if (Data < T->data)
			return Check(T->left, Data);
		else if (Data > T->data)
			return Check(T->right, Data);
		else
			return 0;//这就说明又查到重复的结点了，树肯定不相同
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
//Reset函数
void Reset(Tree T)
{
	if (T && T->flag == 1)
	{
		T->flag = 0;
		Reset(T->left);
		Reset(T->right);
	}
}
//释放树空间
void FreeTree(Tree T)
{
	if (T->left)
		FreeTree(T->left);
	if (T->right)
		FreeTree(T->right);
	free(T);
}